#include "WavPlayer.h"
#include "WavPlayerPanel.h"

#include <Tools/Convert.h>

#include <SvinJson.h>
#include <SvinOrigin.h>

WavPlayer::WavPlayer()
   : Svin::Module()
   , displayController(this, Panel::Pixels_Display)
   , oscilator(true)
   , sampleRate(getSampleRate())
   , fileName()
   , play(false)
   , playButton(this, Panel::Play, Panel::RGB_Play)
   , resetButton(this, Panel::ManualReset)
   , loop(false)
   , loopButton(this, Panel::Loop, Panel::RGB_Loop)
{
   setup();
   displayController.onClicked(this, &WavPlayer::displayClicked);

   playButton.setDefaultColor(Svin::Color{0, 0, 255});
   loopButton.setDefaultColor(Svin::Color{0, 0, 255});
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

   displayController.setColor(Svin::Color{255, 255, 255});
   const std::size_t posSlash = fileName.rfind("/");
   const std::string fileNameEnd = fileName.substr(1 + posSlash);
   displayController.writeText(1, 1, fileNameEnd, Svin::DisplayOLED::Font::Small);

   displayController.setColor(Svin::Color{0, 0, 0});
   std::string message = std::to_string(oscilator.getMeta().noOfChannels) + " ch";
   message += " @ " + Convert::text(oscilator.getMeta().sampleRate / 1000.0, 1);
   displayController.writeText(1, 11, message, Svin::DisplayOLED::Font::Small);

   displayController.setColor(Svin::Color{255, 255, 255});

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

   displayController.writeText(75, 26, timeDisplay(oscilator.getSamplePlayhead()), Svin::DisplayOLED::Font::Large, Svin::DisplayOLED::Alignment::Right);

   displayController.writeText(1, 51, "x" + Convert::text(oscilator.getPlaybackSpeed(), 2), Svin::DisplayOLED::Font::Small);
   displayController.writeText(80, 50, timeDisplay(oscilator.getMeta().numberOfSamples), Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Right);
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

void WavPlayer::load(const Svin::Json::Object& rootObject)
{
   fileName = rootObject.get("fileName").toString();

   play = rootObject.get("play").toBool();
   playButton.setActive(play);

   loop = rootObject.get("loop").toBool();
   loopButton.setActive(loop);

   load();
}

void WavPlayer::save(Svin::Json::Object& rootObject)
{
   rootObject.set("fileName", fileName);
   rootObject.set("play", play);
   rootObject.set("loop", loop);
}

void WavPlayer::onSampleRateChange(const SampleRateChangeEvent& event)
{
   sampleRate = event.sampleRate;
   load();
}

void WavPlayer::displayClicked(const float& x, const float& y)
{
   (void)x;
   (void)y;

   setWavFileName(getOpenFileName("Wav:wav"));
}

// widget

WavPlayerWidget::WavPlayerWidget(WavPlayer* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

Model* modelWavPlayer = Svin::Origin::the()->addModule<WavPlayer, WavPlayerWidget>("WavPlayer");
