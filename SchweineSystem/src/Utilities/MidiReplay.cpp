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
   , fileName()
   , midiReplay()
   , info{}
   // display
   , displayMode(DisplayMode::Overview)
   , displayButton(this, Panel::Display)
   , displayController(this, Panel::Pixels_Display, 100, 170)
   // clock
   , clockTrigger()
   , resetTrigger()
   , tempo()
   , duration(0)
   , currentTick(0)
   , lastTick(0)
{
   setup();
}
void MidiReplay::process(const ProcessArgs& args)
{
   // clock
   const bool isClock = clockTrigger.process(inputs[Panel::Clock].getVoltage() > 3.0);
   const bool isReset = resetTrigger.process(inputs[Panel::Reset].getVoltage() > 3.0);

   if (lastTick >= info.maxTick || isReset)
   {
      duration = 0;
      currentTick = 0;
      lastTick = 0;
      tempo.clockReset();
   }
   else if (isClock)
   {
      duration++;
      tempo.clockTick();
   }
   else
   {
      tempo.advance(args.sampleRate);
   }

   // screen mode
   if (displayButton.isTriggered())
   {
      static const std::vector<DisplayMode> order = {DisplayMode::Overview, DisplayMode::Tempo, DisplayMode::Current};
      Variable::Enum<DisplayMode> variable(displayMode, order, true);
      variable.increment();
   }

   currentTick = midiReplay.toTick(duration, tempo.getPercentage(Tempo::Sixteenth));

   if (lastTick >= currentTick)
      return;

   const uint64_t noOfSequencerChannels = info.monophonicTrackIndexList.size();
   const uint8_t noOfChannels = (noOfSequencerChannels > 16) ? 16 : noOfSequencerChannels;

   if (outputs[Panel::Pitch].getChannels() != noOfChannels)
      outputs[Panel::Pitch].setChannels(noOfChannels);

   if (outputs[Panel::Gate].getChannels() != noOfChannels)
      outputs[Panel::Gate].setChannels(noOfChannels);

   if (outputs[Panel::Velocity].getChannels() != noOfChannels)
      outputs[Panel::Velocity].setChannels(noOfChannels);

   for (uint8_t index = 0; index < noOfChannels; index++)
   {
      if (index >= info.monophonicTrackIndexList.size())
         continue;

      const uint32_t trackIndex = info.monophonicTrackIndexList.at(index);
      const Sequencer::Track& track = midiReplay.getTrackList().at(trackIndex);

      Sequencer::Track::NoteEvent lastEvent;
      bool foundEvent = false;
      for (Sequencer::Tick tick = lastTick; tick <= currentTick; tick++)
      {
         if (track.noteOffEventMap.find(tick) != track.noteOffEventMap.end())
         {
            const Sequencer::Track::NoteEvent::List& eventList = track.noteOffEventMap.at(tick);
            lastEvent = eventList.at(0);
            foundEvent = true;
         }
         if (track.noteOnEventMap.find(tick) != track.noteOnEventMap.end())
         {
            const Sequencer::Track::NoteEvent::List& eventList = track.noteOnEventMap.at(tick);
            lastEvent = eventList.at(0);
            foundEvent = true;
         }
      }

      if (!foundEvent)
         continue;

      if (lastEvent.on)
      {
         const float voltage = Note::fromMidi(lastEvent.key).voltage;
         outputs[Panel::Pitch].setVoltage(voltage, index);

         outputs[Panel::Gate].setVoltage(5.0, index);

         const float velocity = 5.0;
         outputs[Panel::Velocity].setVoltage(velocity, index);
      }
      else
      {
         outputs[Panel::Pitch].setVoltage(0.0, index);
         outputs[Panel::Gate].setVoltage(0.0, index);
         outputs[Panel::Velocity].setVoltage(0.0, index);
      }
   }

   lastTick = currentTick;
}

void MidiReplay::updateDisplays()
{
   displayController.fill();

   if (DisplayMode::Overview == displayMode)
   {
      displayController.setColor(SchweineSystem::Color{255, 255, 255});
      displayController.drawRect(0, 0, 99, 10, true);

      displayController.setColor(SchweineSystem::Color{0, 0, 0});
      const std::size_t posSlash = fileName.rfind("/");
      const std::string fileNameEnd = fileName.substr(1 + posSlash);
      displayController.writeText(1, 1, fileNameEnd, SchweineSystem::DisplayOLED::Font::Normal);

      displayController.setColor(SchweineSystem::Color{255, 255, 255});

      displayController.writeText(1, 15, "bpm: ", SchweineSystem::DisplayOLED::Font::Normal);
      displayController.writeText(50, 25, std::to_string(info.bpm), SchweineSystem::DisplayOLED::Font::Large, SchweineSystem::DisplayOLED::Alignment::Center);

      displayController.writeText(1, 45, "bars: ", SchweineSystem::DisplayOLED::Font::Normal);
      displayController.writeText(50, 55, std::to_string(info.barCounter), SchweineSystem::DisplayOLED::Font::Large, SchweineSystem::DisplayOLED::Alignment::Center);

      displayController.writeText(1, 75, "length:", SchweineSystem::DisplayOLED::Font::Normal);

      auto timeDisplay = [&]()
      {
         const std::string secondsText = std::to_string(info.seconds);

         if (1 == secondsText.length())
            return std::to_string(info.minutes) + ":0" + secondsText;

         return std::to_string(info.minutes) + ":" + secondsText;
      };
      displayController.writeText(50, 88, timeDisplay(), SchweineSystem::DisplayOLED::Font::Huge, SchweineSystem::DisplayOLED::Alignment::Center);

      displayController.writeText(1, 115, "mono tracks:", SchweineSystem::DisplayOLED::Font::Normal);
      displayController.writeText(50, 128, std::to_string(info.monophonicTrackIndexList.size()), SchweineSystem::DisplayOLED::Font::Huge, SchweineSystem::DisplayOLED::Alignment::Center);
   }
   else if (DisplayMode::Tempo == displayMode)
   {
      displayController.drawRect(0, 0, 82, 10, true);
      displayController.drawRect(0, 95, 82, 105, true);
      displayController.drawRect(0, 135, 82, 145, true);

      displayController.setColor(SchweineSystem::Color{0, 0, 0});
      displayController.writeText(1, 1, "counter", SchweineSystem::DisplayOLED::Font::Normal);
      displayController.writeText(1, 96, "tempo", SchweineSystem::DisplayOLED::Font::Normal);
      displayController.writeText(1, 136, "time", SchweineSystem::DisplayOLED::Font::Normal);

      displayController.setColor(SchweineSystem::Color{255, 255, 255});

      TimeCode timeCode(duration);

      // counter
      displayController.writeText(1, 15, "bar", SchweineSystem::DisplayOLED::Font::Normal);
      if (timeCode.bar < 1000)
         displayController.writeText(41, 30, std::to_string(timeCode.bar), SchweineSystem::DisplayOLED::Font::Huge, SchweineSystem::DisplayOLED::Alignment::Center);
      else
         displayController.writeText(41, 30, "big", SchweineSystem::DisplayOLED::Font::Huge, SchweineSystem::DisplayOLED::Alignment::Center);

      displayController.writeText(1, 65, "rest", SchweineSystem::DisplayOLED::Font::Small);
      const std::string rest = std::to_string(timeCode.quarter) + '.' + std::to_string(timeCode.tick);
      displayController.writeText(41, 75, rest, SchweineSystem::DisplayOLED::Font::Normal, SchweineSystem::DisplayOLED::Alignment::Center);

      // tempo
      const uint8_t bpm = tempo.getBeatsPerMinute();
      displayController.writeText(41, 110, std::to_string(bpm), SchweineSystem::DisplayOLED::Font::Large, SchweineSystem::DisplayOLED::Alignment::Center);

      // time
      const float secondsPerTick = 60.0 / (4.0 * bpm);
      const uint32_t totalSeconds = static_cast<uint32_t>(duration * secondsPerTick);
      const uint8_t seconds = totalSeconds % 60;
      const uint32_t minutes = (totalSeconds - seconds) / 60;

      std::string secondText = std::to_string(seconds);
      if (seconds < 10)
         secondText = "0" + secondText;

      const std::string timeText = std::to_string(minutes) + ":" + secondText;
      displayController.writeText(41, 150, timeText, SchweineSystem::DisplayOLED::Font::Large, SchweineSystem::DisplayOLED::Alignment::Center);
   }
   else if (DisplayMode::Current == displayMode)
   {
      displayController.setColor(SchweineSystem::Color{255, 255, 255});
      displayController.writeText(1, 1, "Current", SchweineSystem::DisplayOLED::Font::Normal);
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

json_t* MidiReplay::dataToJson()
{
   using namespace SchweineSystem::Json;

   Object rootObject;
   rootObject.set("fileName", fileName);

   return rootObject.toJson();
}

void MidiReplay::dataFromJson(json_t* rootJson)
{
   using namespace SchweineSystem::Json;

   Object rootObject(rootJson);
   const std::string newFileName = rootObject.get("fileName").toString();
   loadMidiFile(newFileName);
}

// widget

MidiReplayWidget::MidiReplayWidget(MidiReplay* module)
: SchweineSystem::ModuleWidget(module)
{
   setup();

   using OLEDWidget = SchweineSystem::DisplayOLED::Widget;

   OLEDWidget* oled = OLEDWidget::find(this, MidiReplay::Panel::Pixels_Display);
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
