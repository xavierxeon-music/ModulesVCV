#include "Equalizer.h"
#include "EqualizerPanel.h"

#include <Music/Note.h>
#include <SchweineSystemMaster.h>

Equalizer::Equalizer()
   : SchweineSystem::Module()
   , filter()
   , asNote(false)
   , quantiseTrigger()
   , quantiseLight(this)
   , frequencyDisplay(this, Panel::Text_Frequency_Display, Panel::RGB_Frequency_Display)

{
   setup();

   configParam(Panel::Knob_Frequency_Value, 20.0, 20000.0, 440.0, "");
   configParam(Panel::Knob_Smooth_Value, 0.0, 1.0f, 0.f, "");

   quantiseLight.assign(Panel::RGB_Frequency_Quantize);
   quantiseLight.setDefaultColor(SchweineSystem::Color{255, 255, 0});
   frequencyDisplay.setColor(SchweineSystem::Color{0, 255, 0});
}

void Equalizer::process(const ProcessArgs& args)
{
   if (quantiseTrigger.process(params[Panel::Frequency_Quantize].getValue()))
   {
      asNote ^= true;
      if (asNote)
      {
         frequencyDisplay.setColor(SchweineSystem::Color{255, 255, 0});
         quantiseLight.setOn();
      }
      else
      {
         frequencyDisplay.setColor(SchweineSystem::Color{0, 255, 0});
         quantiseLight.setOff();
      }
   }

   float frequency = params[Panel::Knob_Frequency_Value].getValue();
   if (asNote)
   {
      Note note = Note::fromFrequency(frequency);
      frequency = note.frequency;

      frequencyDisplay.setText(note.name);
   }
   else
   {
      const uint16_t iFrequency = static_cast<uint16_t>(frequency);
      frequencyDisplay.setText(std::to_string(iFrequency));
   }
   filter.setFrequency(frequency);

   float amount = params[Panel::Knob_Amount_Value].getValue();
   bool cut = true;
   if (amount > 0.0)
   {
      cut = false;
   }
   else
   {
      amount = amount + 1.0;
   }
   filter.setResonance(amount);

   float smooth = params[Panel::Knob_Smooth_Value].getValue();
   filter.setDrive(smooth);

   const float inputValue = inputs[Panel::AudioInput].getVoltage();
   filter.changeSound(0.1 * inputValue);
   const float outputValue = cut ? filter.notch() : filter.peak();
   outputs[Panel::AudioOutput].setVoltage(outputValue);
}

void Equalizer::onSampleRateChange(const SampleRateChangeEvent& e)
{
   filter.init(e.sampleRate);
}

EqualizerWidget::EqualizerWidget(Equalizer* module)
: SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelEqualizer = SchweineSystem::Master::the()->addModule<Equalizer, EqualizerWidget>("Equalizer");
