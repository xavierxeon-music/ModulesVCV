#ifndef BitBusCVInHPP
#define BitBusCVInHPP

#include "BitBusCVIn.h"

#include <SvinOrigin.h>

struct BitBusCVIn::Panel
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
      CVIn = 0,
      INPUTS_LEN = 1
   };

   enum OutputId
   {
      OUTPUTS_LEN = 0
   };

   enum LightId
   {
      // leds
      RGB_BusOut = 0,
      // ledbuttons
      // sliders
      LIGHTS_LEN = 3
   };

};

void BitBusCVIn::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configInput(Panel::CVIn, "CVIn");
}

void BitBusCVInWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/BitBus/BitBusCVIn.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeInput(this, Vec(24.17, 215.77),  BitBusCVIn::Panel::CVIn, true);

   makeLED(this, Vec(49.50, 46.77), BitBusCVIn::Panel::RGB_BusOut);
}

Model* modelBitBusCVIn = Svin::Origin::the()->addModule<BitBusCVIn, BitBusCVInWidget>("BitBusCVIn");

#endif // NOT BitBusCVInHPP