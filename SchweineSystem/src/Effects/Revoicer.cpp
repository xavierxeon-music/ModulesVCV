#include "Revoicer.h"
#include "RevoicerPanel.h"

#include <Tools/Variable.h>

#include <SchweineSystemJson.h>
#include <SchweineSystemMaster.h>

Revoicer::Revoicer()
   : SchweineSystem::Module()
   , numberOfVocices(16)
   , internal(numberOfVocices, Spectrum::Quality::Low)
   , upButton(this, Panel::Quality_Up)
   , downButton(this, Panel::Quality_Down)
   , controller(this, Panel::Text_Quality_Value, Panel::RGB_Quality_Value)
{
   setup();

   controller.setColor(SchweineSystem::Color{0, 255, 255});
   controller.setText(std::to_string(numberOfVocices));
}

void Revoicer::process(const ProcessArgs& args)
{
   static const std::vector<uint8_t> voiceValues = {0, 1, 2, 4, 8, 16, 32};

   Variable::Enum<uint8_t> var(numberOfVocices, voiceValues, true);
   if (upButton.isTriggered())
   {
      var.increment();
      internal.setNumberOfVoices(numberOfVocices);
      controller.setText(std::to_string(numberOfVocices));
   }
   else if (downButton.isTriggered())
   {
      var.decrement();
      internal.setNumberOfVoices(numberOfVocices);
      controller.setText(std::to_string(numberOfVocices));
   }

   const float inputValue = inputs[Panel::AudioInput].getVoltage();
   const float outputValue = internal.changeSound(inputValue);

   outputs[Panel::AudioOutput].setVoltage(outputValue);
}

void Revoicer::onSampleRateChange(const SampleRateChangeEvent& e)
{
   internal.setSampleRate(e.sampleRate);
}

json_t* Revoicer::dataToJson()
{
   using namespace SchweineSystem::Json;

   Object rootObject;
   rootObject.set("numberOfVocices", Value(numberOfVocices));

   return rootObject.toJson();
}

void Revoicer::dataFromJson(json_t* rootJson)
{
   using namespace SchweineSystem::Json;

   Object rootObject(rootJson);
   numberOfVocices = rootObject.get("numberOfVocices").toInt();

   internal.setNumberOfVoices(numberOfVocices);
   controller.setText(std::to_string(numberOfVocices));
}

// widget

RevoicerWidget::RevoicerWidget(Revoicer* module)
   : SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelRevoicer = SchweineSystem::Master::the()->addModule<Revoicer, RevoicerWidget>("Revoicer");
