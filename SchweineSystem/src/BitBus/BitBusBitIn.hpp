#ifndef BitBusBitInHPP
#define BitBusBitInHPP

#include "BitBusBitIn.h"

#include <SvinOrigin.h>

struct BitBusBitIn::Panel
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
      BitIn8 = 0,
      BitIn7 = 1,
      BitIn6 = 2,
      BitIn5 = 3,
      BitIn4 = 4,
      BitIn3 = 5,
      BitIn2 = 6,
      BitIn1 = 7,
      INPUTS_LEN = 8
   };

   enum OutputId
   {
      OUTPUTS_LEN = 0
   };

   enum LightId
   {
      // leds
      RGB_BusIn = 0,
      RGB_BusOut = 3,
      // ledbuttons
      // sliders
      LIGHTS_LEN = 6
   };

};

void BitBusBitIn::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configInput(Panel::BitIn8, "BitIn8");
   configInput(Panel::BitIn7, "BitIn7");
   configInput(Panel::BitIn6, "BitIn6");
   configInput(Panel::BitIn5, "BitIn5");
   configInput(Panel::BitIn4, "BitIn4");
   configInput(Panel::BitIn3, "BitIn3");
   configInput(Panel::BitIn2, "BitIn2");
   configInput(Panel::BitIn1, "BitIn1");
}

void BitBusBitInWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/BitBus/BitBusBitIn.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeInput(this, Vec(30.00, 337.40),  BitBusBitIn::Panel::BitIn8, true);
   makeInput(this, Vec(30.00, 302.65),  BitBusBitIn::Panel::BitIn7, true);
   makeInput(this, Vec(30.00, 233.15),  BitBusBitIn::Panel::BitIn6, true);
   makeInput(this, Vec(30.00, 267.90),  BitBusBitIn::Panel::BitIn5, true);
   makeInput(this, Vec(30.00, 198.40),  BitBusBitIn::Panel::BitIn4, true);
   makeInput(this, Vec(30.00, 163.65),  BitBusBitIn::Panel::BitIn3, true);
   makeInput(this, Vec(30.00, 128.90),  BitBusBitIn::Panel::BitIn2, true);
   makeInput(this, Vec(30.00, 94.14),  BitBusBitIn::Panel::BitIn1, true);

   makeLED(this, Vec(10.50, 46.77), BitBusBitIn::Panel::RGB_BusIn);
   makeLED(this, Vec(50.00, 46.77), BitBusBitIn::Panel::RGB_BusOut);
}

Model* modelBitBusBitIn = Svin::Origin::the()->addModule<BitBusBitIn, BitBusBitInWidget>("BitBusBitIn");

#endif // NOT BitBusBitInHPP
