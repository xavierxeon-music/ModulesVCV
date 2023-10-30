#include "MidiReplay.h"

#include <Midi/MidiFile.h>
#include <Music/Note.h>
#include <Tools/File.h>
#include <Tools/Variable.h>

#include <SvinJson.h>
#include <SvinMasterClock.h>
#include <SvinOrigin.h>

MidiReplay::MidiReplay()
   : Svin::Module()
   , Svin::MasterClock::Client()
   , fileName()
   , midiReplay()
   , info{}
   // display
   , displayMode(DisplayMode::Overview)
   , pageButton(this, Panel::Page)
   , displayController(this, Panel::Pixels_Display)
   // manual
   , playInput(this, Panel::Play)
   , manualResetInput(this, Panel::Reset)
   , endOutput(this, Panel::End)
   // cycle
   , loopButton(this, Panel::Loop, Panel::RGB_Loop)
   , isLooping(false)
   , atEnd(false)
   , endPulse()
   // current
   , duration(0)
   , currentTick(0)
   , lastTick(0)
{
   setup();
   registerAsBusModule<Svin::MidiBus>();

   displayController.onPressedOpenFileFunction(this, &MidiReplay::loadMidiFile, "MIDI:mid");

   loopButton.setDefaultColor(Color::Predefined::Green);
}

void MidiReplay::process(const ProcessArgs& args)
{
   // clock
   const bool isPlay = playInput.isConnected() ? (playInput.getVoltage() > 3.0) : true;
   atEnd = (lastTick > info.maxTick);

   // screen mode
   if (pageButton.isTriggered())
   {
      static const std::vector<DisplayMode> order = {DisplayMode::Overview, DisplayMode::Tracks};
      Variable::Enum<DisplayMode> variable(displayMode, order, true);
      variable.increment();
   }

   // loop

   if (loopButton.isTriggered())
   {
      isLooping ^= true;
      if (atEnd && isLooping)
         atEnd = false;
   }
   loopButton.setActive(isLooping);

   if (atEnd)
      endPulse.trigger();

   if (endPulse.process(args.sampleTime))
      endOutput.setVoltage(5.0);
   else
      endOutput.setVoltage(0.0);

   if (atEnd && isLooping)
   {
      duration = 0;
      currentTick = 0;
      lastTick = 0;
   }

   // clock

   if (hasReset() || manualResetInput.isTriggered())
   {
      duration = 0;
      currentTick = 0;
      lastTick = 0;
   }
   else
   {
      bool isFirstTick = false;
      while (hasTick(&isFirstTick))
      {
         if (!isFirstTick && isPlay && !atEnd)
            duration++;
      }
   }

   Svin::MidiBus busMessage;
   const Tempo tempo = getTempo();
   busMessage.runState = tempo.getRunState();
   if (!tempo.isRunningOrFirstTick())
   {
      sendBusData<Svin::MidiBus>(Side::Right, busMessage);
      return;
   }

   // play
   currentTick = midiReplay.toTick(duration, tempo.getPercentage());

   const uint64_t noOfSequencerChannels = midiReplay.getTrackList().size();
   const uint8_t noOfChannels = (noOfSequencerChannels > 16) ? 16 : noOfSequencerChannels;
   busMessage.noOfChannels = noOfChannels;

   if (lastTick <= currentTick)
   {
      for (uint8_t index = 0; index < noOfChannels; index++)
      {
         Svin::MidiBus::Channel& busChannel = busMessage.channels[index];
         busChannel.hasEvents = false;

         const Midi::Sequence::Track& track = midiReplay.getTrackList().at(index);
         for (Midi::Sequence::Tick tick = lastTick; tick <= currentTick; tick++)
         {
            if (track.messageMap.find(tick) != track.messageMap.end())
            {
               const Midi::MessageList messageList = track.messageMap.at(tick);
               mergeVectors(busChannel.messageList, messageList);
               busChannel.hasEvents = true;
            }
         }
      }

      lastTick = currentTick;
   }
   sendBusData<Svin::MidiBus>(Side::Right, busMessage);
}

void MidiReplay::updateDisplays()
{
   displayController.fill();

   if (DisplayMode::Overview == displayMode)
   {
      displayController.setColor(Color::Predefined::White);
      displayController.drawRect(0, 0, 99, 10, true);
      displayController.drawRect(0, 34, 99, 44, true);
      displayController.drawRect(0, 84, 99, 94, true);

      displayController.setColor(Color::Predefined::Black);
      std::size_t posSlash = fileName.rfind("/");
      const std::string fileNameEnd = fileName.substr(1 + posSlash);
      const std::string fileNameText = fileNameEnd.size() > 15 ? fileNameEnd.substr(0, 15) : fileNameEnd;
      displayController.writeText(1, 1, fileNameText, Svin::DisplayOLED::Font::Normal);

      displayController.writeText(1, 35, "bars", Svin::DisplayOLED::Font::Normal);
      displayController.writeText(1, 85, "time", Svin::DisplayOLED::Font::Normal);

      displayController.setColor(Color::Predefined::White);

      const Tempo tempo = getTempo();
      const uint8_t bpm = tempo.getBeatsPerMinute();
      displayController.writeText(1, 15, " " + std::to_string(bpm) + " bpm", Svin::DisplayOLED::Font::Small);

      const uint64_t noOfSequencerChannels = midiReplay.getTrackList().size();
      const uint8_t noOfChannels = (noOfSequencerChannels > 16) ? 16 : noOfSequencerChannels;
      displayController.writeText(1, 25, " " + std::to_string(noOfChannels) + " tracks", Svin::DisplayOLED::Font::Small);

      const TimeCode timeCodeReplay(duration);
      displayController.writeText(50, 45, std::to_string(timeCodeReplay.bar), Svin::DisplayOLED::Font::Large, Svin::DisplayOLED::Alignment::Right);
      const std::string replayRest = "." + std::to_string(timeCodeReplay.quarter) + "." + std::to_string(timeCodeReplay.tick);
      displayController.writeText(55, 45 + 7, replayRest, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Left);

      const TimeCode::Duration durationSequence = midiReplay.fromTick(info.maxTick);
      const TimeCode timeCodeSequence(durationSequence);
      displayController.writeText(50, 65, std::to_string(timeCodeSequence.bar), Svin::DisplayOLED::Font::Large, Svin::DisplayOLED::Alignment::Right);
      const std::string sequyenceRest = "." + std::to_string(timeCodeSequence.quarter) + "." + std::to_string(timeCodeSequence.tick);
      displayController.writeText(55, 65 + 7, sequyenceRest, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Left);

      auto timeDisplay = [&](const TimeCode::Duration duration)
      {
         // time
         const float secondsPerTick = 60.0 / (4.0 * bpm);
         const uint32_t totalSeconds = static_cast<uint32_t>(duration * secondsPerTick);
         const uint8_t seconds = totalSeconds % 60;
         const uint32_t minutes = (totalSeconds - seconds) / 60;

         const std::string secondsText = std::to_string(seconds);

         if (1 == secondsText.length())
            return std::to_string(minutes) + ":0" + secondsText;

         return std::to_string(minutes) + ":" + secondsText;
      };

      displayController.writeText(50, 96, timeDisplay(duration), Svin::DisplayOLED::Font::Large, Svin::DisplayOLED::Alignment::Center);
      displayController.writeText(50, 117, timeDisplay(durationSequence), Svin::DisplayOLED::Font::Large, Svin::DisplayOLED::Alignment::Center);
   }
   else if (DisplayMode::Tracks == displayMode)
   {
      displayController.setColor(Color::Predefined::White);
      displayController.drawRect(0, 0, 99, 10, true);

      displayController.setColor(Color::Predefined::Black);
      displayController.writeText(1, 1, "Track Names", Svin::DisplayOLED::Font::Normal);

      displayController.setColor(Color::Predefined::White);

      const uint64_t noOfSequencerChannels = midiReplay.getTrackList().size();
      for (uint8_t index = 0; index < noOfSequencerChannels; index++)
      {
         const Midi::Sequence::Track& track = midiReplay.getTrackList().at(index);
         const uint8_t y = 10 + index * 10;
         const std::string polyMarker = track.isMonophonic ? "o" : "+";
         displayController.writeText(1, y, polyMarker + ' ' + track.name, Svin::DisplayOLED::Font::Normal);
      }
   }
}

void MidiReplay::loadMidiFile(const std::string& newFileName)
{
   fileName = newFileName;

   const Bytes data = File::load(fileName);
   if (data.empty())
      return;

   std::cout << fileName << std::endl;

   midiReplay = Midi::File::Reader(data);
   info = midiReplay.compileInfo();
}

void MidiReplay::load(const Svin::Json::Object& rootObject)
{
   const std::string newFileName = rootObject.get("fileName").toString();
   loadMidiFile(newFileName);

   isLooping = rootObject.get("loop").toBool();

   displayMode = static_cast<DisplayMode>(rootObject.get("displayMode").toInt());
}

void MidiReplay::save(Svin::Json::Object& rootObject)
{
   rootObject.set("fileName", fileName);
   rootObject.set("loop", isLooping);
   rootObject.set("displayMode", static_cast<uint8_t>(displayMode));
}

// widget

MidiReplayWidget::MidiReplayWidget(MidiReplay* module)
   : Svin::ModuleWidget(module)
{
   setup();
}
// create module
Model* modelMidiReplay = Svin::Origin::the()->addModule<MidiReplay, MidiReplayWidget>("MidiReplay");
