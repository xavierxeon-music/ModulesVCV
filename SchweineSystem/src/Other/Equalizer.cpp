#include "Equalizer.h"
#include "EqualizerPanel.h"

#include <Music/Note.h>
#include <SchweineSystemMaster.h>

Equalizer::Equalizer()
   : SchweineSystem::Module()
   , asNote(false)
   , quantiseTrigger()
   , quantiseLight(lights)
   , frequencyDisplay(this, Panel::Text_Frequency_Display, Panel::RGB_Frequency_Display)
{
   setup();

   configParam(Panel::Knob_Frequency_Knob, 20.0, 20000.0, 440.0, "");
   quantiseLight.assign(Panel::RGB_Frequency_Quantize);
   quantiseLight.setDefaultColor(SchweineSystem::Color{255, 255, 0});
   frequencyDisplay.setColor(SchweineSystem::Color{0, 255, 0});
}

void Equalizer::process(const ProcessArgs& args)
{
   float frequency = params[Panel::Knob_Frequency_Knob].getValue();

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
}

EqualizerWidget::EqualizerWidget(Equalizer* module)
: SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelEqualizer = SchweineSystem::Master::the()->addModule<Equalizer, EqualizerWidget>("Equalizer");
