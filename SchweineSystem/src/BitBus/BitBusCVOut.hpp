#ifndef BitBusCVOutHPP
#define BitBusCVOutHPP

#include "BitBusCVOut.h"

#include <SvinOrigin.h>

struct BitBusCVOut::Panel
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
      CVOut = 0,
      OUTPUTS_LEN = 1
   };

   enum LightId
   {
      // leds
      RGB_BusIn = 0,
      // ledbuttons
      // sliders
      LIGHTS_LEN = 3
   };

};

void BitBusCVOut::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configOutput(Panel::CVOut, "CVOut");
}

void BitBusCVOutWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/BitBus/BitBusCVOut.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeOutput(this, Vec(35.83, 215.77), BitBusCVOut::Panel::CVOut, true);

   makeLED(this, Vec(9.50, 46.77), BitBusCVOut::Panel::RGB_BusIn);
}

#endif // NOT BitBusCVOutHPP
