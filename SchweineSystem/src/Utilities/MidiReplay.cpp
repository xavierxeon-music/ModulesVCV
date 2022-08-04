#include "MidiReplay.h"
#include "MidiReplayPanel.h"

#include <osdialog.h>

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
{
   setup();
}
void MidiReplay::process(const ProcessArgs& args)
{
   // clock
   const bool isClock = clockTrigger.process(inputs[Panel::Clock].getVoltage() > 3.0);
   const bool isReset = resetTrigger.process(inputs[Panel::Reset].getVoltage() > 3.0);

   if (isReset)
      tempo.clockReset();
   else if (isClock)
      tempo.clockTick();
   else
      tempo.advance(args.sampleRate);

   // screen mode
   if (displayButton.isTriggered())
   {
      static const std::vector<DisplayMode> order = {DisplayMode::Overview, DisplayMode::Current};
      Variable::Enum<DisplayMode> variable(displayMode, order, true);
      variable.increment();
   }
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

      displayController.writeText(1, 115, "tracks:", SchweineSystem::DisplayOLED::Font::Normal);
      displayController.writeText(50, 128, std::to_string(info.numberOfTracks), SchweineSystem::DisplayOLED::Font::Huge, SchweineSystem::DisplayOLED::Alignment::Center);
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

   midiReplay.load(data);
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
