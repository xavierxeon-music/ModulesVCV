#ifndef DoepferQuadHPP
#define DoepferQuadHPP

#include "DoepferQuad.h"

#include <SvinOrigin.h>

struct DoepferQuad::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      Connect = 0,
      // knobs
      // sliders
      PARAMS_LEN = 1
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
      OUTPUTS_LEN = 0
   };

   enum LightId
   {
      // leds
      // ledbuttons
      RGB_Connect = 0,
      // sliders
      LIGHTS_LEN = 3
   };

};

void DoepferQuad::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");
}

void DoepferQuadWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/Hardware/DoepferQuad.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeLEDButton(this, Vec(30.00, 340.14), DoepferQuad::Panel::Connect, DoepferQuad::Panel::RGB_Connect);
}

#endif // NOT DoepferQuadHPP
