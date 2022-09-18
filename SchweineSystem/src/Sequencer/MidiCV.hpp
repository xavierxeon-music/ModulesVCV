#ifndef MidiCVHPP
#define MidiCVHPP

#include "MidiCV.h"

#include <SvinOrigin.h>

struct MidiCV::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      // knobs
      // sliders
      PARAMS_LEN = 0
   };

   enum DisplayId
   {
      // lcd
      // oled
      DISPLAYS_LEN = 0
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      INPUTS_LEN = 0
   };

   enum OutputId
   {
      Velocity = 0,
      Gate = 1,
      Pitch = 2,
      OUTPUTS_LEN = 3
   };

   enum LightId
   {
      // leds
      // ledbuttons
      // sliders
      LIGHTS_LEN = 0
   };

};

void MidiCV::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configOutput(Panel::Velocity, "Velocity");
   configOutput(Panel::Gate, "Gate");
   configOutput(Panel::Pitch, "Pitch");
}

void MidiCVWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/Sequencer/MidiCV.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeOutput(this, Vec(30.00, 309.00), MidiCV::Panel::Velocity, true);
   makeOutput(this, Vec(30.00, 262.18), MidiCV::Panel::Gate, true);
   makeOutput(this, Vec(30.00, 215.52), MidiCV::Panel::Pitch, true);
}

#endif // NOT MidiCVHPP
