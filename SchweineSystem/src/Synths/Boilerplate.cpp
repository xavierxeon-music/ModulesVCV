#include "Boilerplate.h"

Boilerplate::Boilerplate()
   : Svin::Module()
   , shapeSlider(this, Panel::Shape, Panel::RGB_Shape)
   , syncInput(this, Panel::Sync)
   , fmInput(this, Panel::FM)
   , fmAttenutate(this, Panel::FMAttenuate)
   , pitchInput(this, Panel::Pitch)
   , pitchKnob(this, Panel::Offset)
   , gateInput(this, Panel::Gate)
   , output(this, Panel::Out)
   , polyButton(this, Panel::Poly, Panel::RGB_Poly)
   , oscilator{}
   , table()
{
   setup();

   shapeSlider.setRange(0.0, 4.0);
   shapeSlider.enableSteps(true);
   shapeSlider.setDefaultColor(Color{255, 255, 0});
   shapeSlider.setOn();

   fmAttenutate.setRange(-1.0, 1.0, 0.0);
   pitchKnob.setRange(0.0, 5.0);

   polyButton.setDefaultColor(Color{0, 255, 0});
   polyButton.setOff();

   for (uint8_t voice = 0; voice < 16; voice++)
      oscilator[voice].init(&table, getSampleRate());
}

void Boilerplate::process(const ProcessArgs& args)
{
   const bool polyMode = polyButton.isLatched();
   polyButton.setActive(polyMode);

   const Standard::Waveform::Shape shape = static_cast<Standard::Waveform::Shape>(shapeSlider.getValue());
   table.setWaveform(shape);

   if (syncInput.isTriggered())
   {
      for (uint8_t voice = 0; voice < 16; voice++)
         oscilator[voice].reset();
   }

   float fmVoltage = fmInput.getVoltage() * fmAttenutate.getValue();

   const uint8_t noOfVoices = pitchInput.isConnected() ? pitchInput.getNumberOfChannels() : 1;
   if (polyMode)
      output.setNumberOfChannels(noOfVoices);
   else
      output.setNumberOfChannels(1);

   float sumValue = 0.0;
   for (uint8_t voice = 0; voice < noOfVoices; voice++)
   {
      const float pitchVoltage = pitchInput.getVoltage(voice) + pitchKnob.getValue();
      const float voltage = pitchVoltage + fmVoltage;

      const float frequency = Abstract::Oscilator::frequencyFromCV(voltage);
      oscilator[voice].setFrequency(frequency);

      float value = oscilator[voice].createSound();
      if (gateInput.isConnected() && gateInput.isOff(voice))
         value = 0.0;

      if (!polyMode)
         sumValue += value;
      else
         output.setVoltage(value * 10.0, voice);
   }
   if (!polyMode)
   {
      sumValue /= noOfVoices;
      output.setVoltage(sumValue * 10.0);
   }
}

void Boilerplate::load(const Svin::Json::Object& rootObject)
{
   shapeSlider.setValue(rootObject.get("shape").toReal());
   pitchKnob.setValue(rootObject.get("offset").toReal());
   fmAttenutate.setValue(rootObject.get("fmAttenuate").toReal());
   polyButton.setLatched(rootObject.get("poly").toBool());
}

void Boilerplate::save(Svin::Json::Object& rootObject)
{
   rootObject.set("shape", shapeSlider.getValue());
   rootObject.set("offset", pitchKnob.getValue());
   rootObject.set("fmAttenuate", fmAttenutate.getValue());
   rootObject.set("poly", polyButton.isLatched());
}

void Boilerplate::onSampleRateChange(const SampleRateChangeEvent& event)
{
   const float sampleRate = event.sampleRate;

   for (uint8_t voice = 0; voice < 16; voice++)
      oscilator[voice].init(&table, sampleRate);
}

// widget

BoilerplateWidget::BoilerplateWidget(Boilerplate* module)
: Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelBoilerplate = Svin::Origin::the()->addModule<Boilerplate, BoilerplateWidget>("Boilerplate");

