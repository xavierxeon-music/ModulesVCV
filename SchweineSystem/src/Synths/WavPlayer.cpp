#include "WavPlayer.h"

#include <Tools/Text.h>

#include <SvinJson.h>
#include <SvinOrigin.h>

WavPlayer::WavPlayer()
   : Svin::Module()
   , displayController(this, Panel::Pixels_Display)
   , oscilator(true)
   , sampleRate(getSampleRate())
   , fileName()
   , playButton(this, Panel::Play, Panel::RGB_Play)
   , playInput(this, Panel::PlayOverride)
   , resetButton(this, Panel::ManualReset)
   , resetInput(this, Panel::Reset)
   , loopButton(this, Panel::Loop, Panel::RGB_Loop)
   , loopInput(this, Panel::LoopOverride)
   , pitchInput(this, Panel::Pitch)
   , polyOutput(this, Panel::Left)
   , rightOutput(this, Panel::Right)
{
   setup();
   displayController.onClicked(this, &WavPlayer::displayClicked);

   playButton.setDefaultColor(Svin::Color{0, 0, 255});
   playButton.setLatchBuddy(&playInput);

   loopButton.setDefaultColor(Svin::Color{0, 0, 255});
   loopButton.setLatchBuddy(&loopInput);
}

void WavPlayer::process(const ProcessArgs& args)
{
   if (pitchInput.isConnected())
   {
      const float pitch = pitchInput.getVoltage();
      const float frequency = Abstract::Oscilator::frequencyFromCV(pitch);
      oscilator.setFrequency(frequency);
   }
   else
   {
      oscilator.setFrequency(oscilator.defaultFrequency);
   }

   const bool play = playButton.isLatched();
   playButton.setActive(play);
   if (play)
      oscilator.start();
   else
      oscilator.pause();

   const bool loop = loopButton.isLatched();
   loopButton.setActive(loop);
   oscilator.setLooping(loop);

   if (resetInput.isConnected() && resetInput.isTriggered())
      oscilator.reset();
   else if (resetButton.isTriggered())
      oscilator.reset();

   uint8_t channelCount = oscilator.getMeta().noOfChannels;
   if (channelCount > 16)
      channelCount = 16;

   polyOutput.setNumberOfChannels(channelCount);

   oscilator.createSound();

   for (uint8_t channel = 0; channel < channelCount; channel++)
      polyOutput.setVoltage(8.0 * oscilator.getSound(channel), channel);

   rightOutput.setVoltage(8.0 * oscilator.getSound());
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
   message += " @ " + Text::convert(oscilator.getMeta().sampleRate / 1000.0, 1);
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

   displayController.writeText(1, 51, "x" + Text::convert(oscilator.getPlaybackSpeed(), 2), Svin::DisplayOLED::Font::Small);
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
}

void WavPlayer::load(const Svin::Json::Object& rootObject)
{
   fileName = rootObject.get("fileName").toString();

   const bool play = rootObject.get("play").toBool();
   playButton.setLatched(play);

   const bool loop = rootObject.get("loop").toBool();
   loopButton.setLatched(loop);

   load();
}

void WavPlayer::save(Svin::Json::Object& rootObject)
{
   rootObject.set("fileName", fileName);
   rootObject.set("play", playButton.isLatched(false));
   rootObject.set("loop", loopButton.isLatched(false));
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
// creete module
Model* modelWavPlayer = Svin::Origin::the()->addModule<WavPlayer, WavPlayerWidget>("WavPlayer");

