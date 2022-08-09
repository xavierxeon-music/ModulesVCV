#include "WavPlayer.h"
#include "WavPlayerPanel.h"

#include <osdialog.h>

#include <Tools/Convert.h>

#include <SchweineSystemJson.h>
#include <SchweineSystemMaster.h>

WavPlayer::WavPlayer()
   : SchweineSystem::Module()
   , displayController(this, Panel::Pixels_Display, 83, 60)
   , oscilator(true)
   , sampleRate(APP->engine->getSampleRate())
   , fileName()
   , play(false)
   , playButton(this, Panel::Play, Panel::RGB_Play)
   , resetButton(this, Panel::ManualReset)
   , loop(false)
   , loopButton(this, Panel::Loop, Panel::RGB_Loop)
{
   setup();

   playButton.setDefaultColor(SchweineSystem::Color{0, 0, 255});
   loopButton.setDefaultColor(SchweineSystem::Color{0, 0, 255});
}

void WavPlayer::process(const ProcessArgs& args)
{
   if (inputs[Panel::Pitch].isConnected())
   {
      const float pitch = inputs[Panel::Pitch].getVoltage();
      const float frequency = Abstract::Oscilator::frequencyFromCV(pitch);
      oscilator.setFrequency(frequency);
   }
   else
   {
      oscilator.setFrequency(oscilator.defaultFrequency);
   }

   if (playButton.isTriggered())
   {
      play ^= true;
      playButton.setActive(play);
      if (play)
         oscilator.start();
      else
         oscilator.pause();
   }

   if (loopButton.isTriggered())
   {
      loop ^= true;
      loopButton.setActive(loop);
      oscilator.setLooping(loop);
   }

   if (resetButton.isTriggered())
   {
      oscilator.reset();
   }

   const float valueLeft = oscilator.createSound();
   outputs[Panel::Left].setVoltage(valueLeft);

   const float valueRight = oscilator.getSound();
   outputs[Panel::Right].setVoltage(valueRight);
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
   std::string message = std::to_string(oscilator.getMeta().noOfChannels) + " ch";
   message += " @ " + Convert::text(oscilator.getMeta().sampleRate / 1000.0, 1);
   displayController.writeText(1, 11, message, SchweineSystem::DisplayOLED::Font::Small);

   displayController.setColor(SchweineSystem::Color{255, 255, 255});

   auto timeDisplay = [&](const size_t value)
   {
      const size_t position = value / oscilator.getMeta().noOfChannels;
      const size_t totalSeconds = position / oscilator.getMeta().sampleRate;

      const uint8_t seconds = totalSeconds % 60;
      const size_t minutes = (totalSeconds - seconds) / 60;

      const std::string secondsText = std::to_string(seconds);

      if (1 == secondsText.length())
         return std::to_string(minutes) + ":0" + secondsText;

      return std::to_string(minutes) + ":" + secondsText;
   };

   displayController.writeText(75, 26, timeDisplay(oscilator.getSamplePlayhead()), SchweineSystem::DisplayOLED::Font::Large, SchweineSystem::DisplayOLED::Alignment::Right);

   displayController.writeText(1, 51, "x" + Convert::text(oscilator.getPlaybackSpeed(), 2), SchweineSystem::DisplayOLED::Font::Small);
   displayController.writeText(80, 50, timeDisplay(oscilator.getMeta().numberOfSamples), SchweineSystem::DisplayOLED::Font::Normal, SchweineSystem::DisplayOLED::Alignment::Right);
}

void WavPlayer::setWavFileName(const std::string& newFileName)
{
   fileName = newFileName;
   load();
}

void WavPlayer::load()
{
   oscilator.init(fileName, sampleRate);

   if (play)
      oscilator.start();
   else
      oscilator.pause();

   oscilator.setLooping(loop);
}

json_t* WavPlayer::dataToJson()
{
   using namespace SchweineSystem::Json;

   Object rootObject;
   rootObject.set("fileName", Value(fileName));
   rootObject.set("play", Value(play));
   rootObject.set("loop", Value(loop));

   return rootObject.toJson();
}

void WavPlayer::dataFromJson(json_t* rootJson)
{
   using namespace SchweineSystem::Json;

   Object rootObject(rootJson);

   fileName = rootObject.get("fileName").toString();

   play = rootObject.get("play").toBool();
   playButton.setActive(play);

   loop = rootObject.get("loop").toBool();
   loopButton.setActive(loop);

   load();
}

void WavPlayer::onSampleRateChange(const SampleRateChangeEvent& event)
{
   sampleRate = event.sampleRate;
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

   const char* path = osdialog_file(OSDIALOG_OPEN, nullptr, NULL, osdialog_filters_parse("Wav:wav"));
   if (path)
      myModule->setWavFileName(std::string(path));
}

Model* modelWavPlayer = SchweineSystem::Master::the()->addModule<WavPlayer, WavPlayerWidget>("WavPlayer");
