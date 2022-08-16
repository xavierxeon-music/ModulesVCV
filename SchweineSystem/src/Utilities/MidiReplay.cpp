#include "MidiReplay.h"
#include "MidiReplayPanel.h"

#include <osdialog.h>

#include <Music/Note.h>
#include <Tools/File.h>
#include <Tools/Variable.h>

#include <SchweineSystemJson.h>
#include <SchweineSystemMaster.h>

MidiReplay::MidiReplay()
   : SchweineSystem::Module()
   , SchweineSystem::Exapnder<SchweineSystem::BusMidi>(this)
   , fileName()
   , midiReplay()
   , info{}
   // display
   , displayMode(DisplayMode::Overview)
   , pageButton(this, Panel::Page)
   , editUpButton(this, Panel::Edit_Up)
   , editDownButton(this, Panel::Edit_Down)
   , editLeftButton(this, Panel::Edit_Left)
   , editRightButton(this, Panel::Edit_Right)
   , displayController(this, Panel::Pixels_Display)
   // clock
   , clockTrigger()
   , resetTrigger()
   , tempo()
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
   allowExpanderOnRight();

   loopButton.setDefaultColor(SchweineSystem::Color{0, 255, 0});
}
void MidiReplay::process(const ProcessArgs& args)
{
   // clock
   const bool isClock = clockTrigger.process(inputs[Panel::Clock].getVoltage() > 3.0);
   const bool isReset = resetTrigger.process(inputs[Panel::Reset].getVoltage() > 3.0);
   const bool isPlay = inputs[Panel::Play].isConnected() ? (inputs[Panel::Play].getVoltage() > 3.0) : true;
   atEnd = (lastTick > info.maxTick);

   // screen mode
   if (pageButton.isTriggered())
   {
      static const std::vector<DisplayMode> order = {DisplayMode::Overview, DisplayMode::Tracks, DisplayMode::Current};
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
      outputs[Panel::End].setVoltage(5.0);
   else
      outputs[Panel::End].setVoltage(0.0);

   if (atEnd && isLooping)
   {
      duration = 0;
      currentTick = 0;
      lastTick = 0;
   }

   // clock
   if (isReset)
   {
      duration = 0;
      currentTick = 0;
      lastTick = 0;

      tempo.clockReset();
   }
   else if (isClock)
   {
      if (isPlay && !atEnd)
         duration++;
      tempo.clockTick();
   }
   else
   {
      tempo.advance(args.sampleRate);
   }

   // play
   currentTick = midiReplay.toTick(duration, tempo.getPercentage(Tempo::Sixteenth));

   if (lastTick >= currentTick)
      return;

   const uint64_t noOfSequencerChannels = midiReplay.getTrackList().size();
   const uint8_t noOfChannels = (noOfSequencerChannels > 16) ? 16 : noOfSequencerChannels;

   SchweineSystem::BusMidi busMessage;
   busMessage.noOfChannels = noOfChannels;
   busMessage.startTick = lastTick;
   busMessage.endTick = currentTick;

   for (uint8_t index = 0; index < noOfChannels; index++)
   {
      SchweineSystem::BusMidi::Channel& busChannel = busMessage.channels[index];
      const Sequencer::Track& track = midiReplay.getTrackList().at(index);
      busChannel.isMonophoic = track.isMonophonic;

      for (Sequencer::Tick tick = lastTick; tick <= currentTick; tick++)
      {
         if (track.noteOffEventMap.find(tick) != track.noteOffEventMap.end())
         {
            const Sequencer::Track::NoteEvent::List& eventList = track.noteOffEventMap.at(tick);
            busChannel.noteOffEventMap[tick] = eventList;
         }
         if (track.noteOnEventMap.find(tick) != track.noteOnEventMap.end())
         {
            const Sequencer::Track::NoteEvent::List& eventList = track.noteOnEventMap.at(tick);
            busChannel.noteOnEventMap[tick] = eventList;
         }
      }
   }

   lastTick = currentTick;
   sendToRight(busMessage);
}

void MidiReplay::updateDisplays()
{
   displayController.fill();

   if (DisplayMode::Overview == displayMode)
   {
      displayController.setColor(SchweineSystem::Color{255, 255, 255});
      displayController.drawRect(0, 0, 99, 10, true);
      displayController.drawRect(0, 34, 99, 43, true);
      displayController.drawRect(0, 84, 99, 93, true);

      displayController.setColor(SchweineSystem::Color{0, 0, 0});
      const std::size_t posSlash = fileName.rfind("/");
      const std::string fileNameEnd = fileName.substr(1 + posSlash);
      displayController.writeText(1, 1, fileNameEnd, SchweineSystem::DisplayOLED::Font::Normal);

      displayController.writeText(1, 35, " b a r s", SchweineSystem::DisplayOLED::Font::Normal);
      displayController.writeText(1, 85, " t i m e", SchweineSystem::DisplayOLED::Font::Normal);

      displayController.setColor(SchweineSystem::Color{255, 255, 255});

      const uint8_t bpm = tempo.getBeatsPerMinute();
      displayController.writeText(1, 15, " " + std::to_string(bpm) + " bpm", SchweineSystem::DisplayOLED::Font::Small);

      const uint64_t noOfSequencerChannels = midiReplay.getTrackList().size();
      const uint8_t noOfChannels = (noOfSequencerChannels > 16) ? 16 : noOfSequencerChannels;
      displayController.writeText(1, 25, " " + std::to_string(noOfChannels) + " tracks", SchweineSystem::DisplayOLED::Font::Small);

      const TimeCode timeCodeReplay(duration);
      displayController.writeText(50, 45, std::to_string(timeCodeReplay.bar), SchweineSystem::DisplayOLED::Font::Large, SchweineSystem::DisplayOLED::Alignment::Right);
      const std::string replayRest = "." + std::to_string(timeCodeReplay.quarter) + "." + std::to_string(timeCodeReplay.tick);
      displayController.writeText(50, 45 + 8, replayRest, SchweineSystem::DisplayOLED::Font::Normal, SchweineSystem::DisplayOLED::Alignment::Left);

      const TimeCode::Duration durationSequence = midiReplay.fromTick(info.maxTick);
      const TimeCode timeCodeSequence(durationSequence);
      displayController.writeText(50, 65, std::to_string(timeCodeSequence.bar), SchweineSystem::DisplayOLED::Font::Large, SchweineSystem::DisplayOLED::Alignment::Right);
      const std::string sequyenceRest = "." + std::to_string(timeCodeSequence.quarter) + "." + std::to_string(timeCodeSequence.tick);
      displayController.writeText(50, 65 + 8, sequyenceRest, SchweineSystem::DisplayOLED::Font::Normal, SchweineSystem::DisplayOLED::Alignment::Left);

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

      displayController.writeText(50, 95, timeDisplay(duration), SchweineSystem::DisplayOLED::Font::Large, SchweineSystem::DisplayOLED::Alignment::Center);
      displayController.writeText(50, 115, timeDisplay(durationSequence), SchweineSystem::DisplayOLED::Font::Large, SchweineSystem::DisplayOLED::Alignment::Center);
   }
   else if (DisplayMode::Tracks == displayMode)
   {
      displayController.setColor(SchweineSystem::Color{255, 255, 255});
      displayController.drawRect(0, 0, 99, 10, true);

      displayController.setColor(SchweineSystem::Color{0, 0, 0});
      displayController.writeText(1, 1, "Tracks", SchweineSystem::DisplayOLED::Font::Normal);

      displayController.setColor(SchweineSystem::Color{255, 255, 255});

      const uint64_t noOfSequencerChannels = midiReplay.getTrackList().size();
      for (uint8_t index = 0; index < noOfSequencerChannels; index++)
      {
         const Sequencer::Track& track = midiReplay.getTrackList().at(index);
         const uint8_t y = 10 + index * 10;
         const std::string polyMarker = track.isMonophonic ? "o" : "+";
         displayController.writeText(1, y, polyMarker + ' ' + track.name, SchweineSystem::DisplayOLED::Font::Normal);
      }
   }
   else if (DisplayMode::Current == displayMode)
   {
      displayController.setColor(SchweineSystem::Color{255, 255, 255});
      displayController.drawRect(0, 0, 99, 10, true);

      displayController.setColor(SchweineSystem::Color{0, 0, 0});
      displayController.writeText(1, 1, "Current", SchweineSystem::DisplayOLED::Font::Normal);

      displayController.setColor(SchweineSystem::Color{255, 255, 255});
   }
}

void MidiReplay::loadMidiFile(const std::string& newFileName)
{
   fileName = newFileName;

   const Bytes data = File::load(fileName);
   if (data.empty())
      return;

   std::cout << fileName << std::endl;

   midiReplay = Midi::File::load(data);
   info = midiReplay.compileInfo();
}

void MidiReplay::load(const SchweineSystem::Json::Object& rootObject)
{
   const std::string newFileName = rootObject.get("fileName").toString();
   loadMidiFile(newFileName);

   isLooping = rootObject.get("loop").toBool();

   displayMode = static_cast<DisplayMode>(rootObject.get("displayMode").toInt());
}

void MidiReplay::save(SchweineSystem::Json::Object& rootObject)
{
   rootObject.set("fileName", fileName);
   rootObject.set("loop", isLooping);
   rootObject.set("displayMode", static_cast<uint8_t>(displayMode));
}

// widget

MidiReplayWidget::MidiReplayWidget(MidiReplay* module)
: SchweineSystem::ModuleWidget(module)
{
   setup();

   using OLEDWidget = SchweineSystem::DisplayOLED::Widget;

   OLEDWidget* oled = OLEDWidget::find(module, MidiReplay::Panel::Pixels_Display);
   if (oled)
      oled->onClicked(this, &MidiReplayWidget::displayClicked);
}

void MidiReplayWidget::displayClicked(const float& x, const float& y)
{
   (void)x;
   (void)y;

   MidiReplay* myModule = dynamic_cast<MidiReplay*>(getSchweineModule());
   if (!myModule)
      return;

   const char* path = osdialog_file(OSDIALOG_OPEN, nullptr, NULL, osdialog_filters_parse("MIDI:mid"));
   if (path)
      myModule->loadMidiFile(std::string(path));
}

Model* modelMidiReplay = SchweineSystem::Master::the()->addModule<MidiReplay, MidiReplayWidget>("MidiReplay");
