#include "WavPlayer.h"
#include "WavPlayerPanel.h"

#include <osdialog.h>

#include <Tools/Convert.h>

#include <SchweineSystemJson.h>
#include <SchweineSystemMaster.h>

WavPlayer::WavPlayer()
   : SchweineSystem::Module()
   , displayController(this, Panel::Pixels_Display, 83, 90)
   , fileName()
   , meta()
   , audio()
   , playhead(0)
{
   setup();
}

void WavPlayer::process(const ProcessArgs& args)
{
   if (0 == meta.numberOfSamples)
   {
      inputs[Panel::Left].setVoltage(0.0);
      inputs[Panel::Right].setVoltage(0.0);
      return;
   }

   // playback
   auto advancePlayHead = [&]()
   {
      playhead++;
      if (playhead >= meta.numberOfSamples)
         playhead = 0;
   };

   // left
   const float valueLeft = audio.at(playhead);
   outputs[Panel::Left].setVoltage(valueLeft);
   advancePlayHead();

   // right
   if (meta.stereo)
   {
      const float valueRight = audio.at(playhead);
      outputs[Panel::Right].setVoltage(valueRight);
      advancePlayHead();
   }
   else
   {
      const float valueRight = valueLeft;
      outputs[Panel::Right].setVoltage(valueRight);
   }
}

void WavPlayer::updateDisplays()
{
   displayController.fill();

   displayController.drawRect(0, 10, 82, 18, true);

   displayController.setColor(SchweineSystem::Color{255, 255, 255});
   const std::size_t posSlash = fileName.rfind("/");
   const std::string fileNameEnd = fileName.substr(1 + posSlash);
   displayController.writeText(1, 1, fileNameEnd, SchweineSystem::DisplayOLED::Font::Small);

   displayController.setColor(SchweineSystem::Color{0, 0, 0});
   std::string message = meta.stereo ? "2 ch" : "1 ch";
   message += " @ " + Convert::text(meta.sampleRate / 1000.0, 1);
   displayController.writeText(1, 11, message, SchweineSystem::DisplayOLED::Font::Small);

   displayController.setColor(SchweineSystem::Color{255, 255, 255});

   auto timeDisplay = [&](const size_t value)
   {
      const size_t position = meta.stereo ? value / 2 : value;
      const size_t totalSeconds = position / meta.sampleRate;

      const uint8_t seconds = totalSeconds % 60;
      const size_t minutes = (totalSeconds - seconds) / 60;

      const std::string secondsText = std::to_string(seconds);

      if (1 == secondsText.length())
         return std::to_string(minutes) + ":0" + secondsText;

      return std::to_string(minutes) + ":" + secondsText;
   };

   displayController.writeText(80, 21, timeDisplay(playhead), SchweineSystem::DisplayOLED::Font::Small, SchweineSystem::DisplayOLED::Alignment::Right);
   displayController.writeText(80, 31, timeDisplay(meta.numberOfSamples), SchweineSystem::DisplayOLED::Font::Small, SchweineSystem::DisplayOLED::Alignment::Right);
}

void WavPlayer::setWavFileName(const std::string& newFileName)
{
   fileName = newFileName;
   load();
}

void WavPlayer::load()
{
   playhead = 0;
   audio = Sample::load(fileName, &meta);
}

json_t* WavPlayer::dataToJson()
{
   using namespace SchweineSystem::Json;

   Object rootObject;
   rootObject.set("fileName", Value(fileName));

   return rootObject.toJson();
}

void WavPlayer::dataFromJson(json_t* rootJson)
{
   using namespace SchweineSystem::Json;

   Object rootObject(rootJson);
   fileName = rootObject.get("fileName").toString();
   load();
}

// widget

WavPlayerWidget::WavPlayerWidget(WavPlayer* module)
   : SchweineSystem::ModuleWidget(module)
{
   setup();

   using OLEDWidget = SchweineSystem::DisplayOLED::Widget;

   OLEDWidget* oled = OLEDWidget::find(this, WavPlayer::Panel::Pixels_Display);
   if (oled)
      oled->onClicked(this, &WavPlayerWidget::displayClicked);
}

void WavPlayerWidget::displayClicked(const float& x, const float& y)
{
   (void)x;
   (void)y;

   WavPlayer* myModule = dynamic_cast<WavPlayer*>(getSchweineModule());
   if (!myModule)
      return;

   char* path = osdialog_file(OSDIALOG_OPEN, nullptr, NULL, osdialog_filters_parse("Wav:wav"));
   myModule->setWavFileName(std::string(path));
}

Model* modelWavPlayer = SchweineSystem::Master::the()->addModule<WavPlayer, WavPlayerWidget>("WavPlayer");
