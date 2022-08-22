#include "Revoicer.h"
#include "RevoicerPanel.h"

#include <Tools/Variable.h>

#include <SyJson.h>
#include <SyMaster.h>

Revoicer::Revoicer()
   : Sy::Module()
   , numberOfVoices(16)
   , internal(numberOfVoices, Spectrum::Quality::Low)
   , upButton(this, Panel::Quality_Up)
   , downButton(this, Panel::Quality_Down)
   , controller(this, Panel::Text_Quality_Value, Panel::RGB_Quality_Value)
{
   setup();

   controller.setColor(Sy::Color{0, 255, 255});
   controller.setText(std::to_string(numberOfVoices));
}

void Revoicer::process(const ProcessArgs& args)
{
   static const std::vector<uint8_t> voiceValues = {0, 1, 2, 4, 8, 16, 32};

   Variable::Enum<uint8_t> var(numberOfVoices, voiceValues, true);
   if (upButton.isTriggered())
   {
      var.increment();
      internal.setNumberOfVoices(numberOfVoices);
      controller.setText(std::to_string(numberOfVoices));
   }
   else if (downButton.isTriggered())
   {
      var.decrement();
      internal.setNumberOfVoices(numberOfVoices);
      controller.setText(std::to_string(numberOfVoices));
   }

   const float inputValue = inputs[Panel::AudioInput].getVoltage();
   const float outputValue = internal.changeSound(inputValue);

   outputs[Panel::AudioOutput].setVoltage(outputValue);
}

void Revoicer::onSampleRateChange(const SampleRateChangeEvent& e)
{
   internal.setSampleRate(e.sampleRate);
}

void Revoicer::load(const Sy::Json::Object& rootObject)
{
   numberOfVoices = rootObject.get("numberOfVoices").toInt();

   internal.setNumberOfVoices(numberOfVoices);
   controller.setText(std::to_string(numberOfVoices));
}

void Revoicer::save(Sy::Json::Object& rootObject)
{
   rootObject.set("numberOfVoices", numberOfVoices);
}

// widget

RevoicerWidget::RevoicerWidget(Revoicer* module)
   : Sy::ModuleWidget(module)
{
   setup();
}

Model* modelRevoicer = Sy::Master::the()->addModule<Revoicer, RevoicerWidget>("Revoicer");
