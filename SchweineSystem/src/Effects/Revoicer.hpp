#ifndef RevoicerHPP
#define RevoicerHPP

#include "Revoicer.h"

#include <SvinOrigin.h>

struct Revoicer::Panel
{
   enum ParamId
   {
      // buttons
      Quality_Down = 0,
      Quality_Up = 1,
      // switches
      // ledbuttons
      // knobs
      // sliders
      PARAMS_LEN = 2
   };

   enum DisplayId
   {
      // lcd
      Text_Quality_Value = 0,
      // oled
      DISPLAYS_LEN = 1
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      AudioInput = 0,
      INPUTS_LEN = 1
   };

   enum OutputId
   {
      AudioOutput = 0,
      OUTPUTS_LEN = 1
   };

   enum LightId
   {
      // leds
      // ledbuttons
      // sliders
      LIGHTS_LEN = 0
   };

};

void Revoicer::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Quality_Down, "Quality_Down");
   configButton(Panel::Quality_Up, "Quality_Up");

   configInput(Panel::AudioInput, "AudioInput");

   configOutput(Panel::AudioOutput, "AudioOutput");
}

void RevoicerWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/Effects/Revoicer.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(30.33, 183.71), Revoicer::Panel::Quality_Down);
   makeButton(this, Vec(30.33, 134.83), Revoicer::Panel::Quality_Up);

   makeInput(this, Vec(30.00, 300.34),  Revoicer::Panel::AudioInput, false);

   makeOutput(this, Vec(30.68, 344.57), Revoicer::Panel::AudioOutput, false);

   makeLCD(this, Vec(11.00, 147.27), 2, Revoicer::Panel::Text_Quality_Value, 18);
}

#endif // NOT RevoicerHPP
