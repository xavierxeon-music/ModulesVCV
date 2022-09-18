#ifndef BitBusBitOutHPP
#define BitBusBitOutHPP

#include "BitBusBitOut.h"

#include <SvinOrigin.h>

struct BitBusBitOut::Panel
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
      BitOut8 = 0,
      BitOut7 = 1,
      BitOut6 = 2,
      BitOut5 = 3,
      BitOut4 = 4,
      BitOut3 = 5,
      BitOut2 = 6,
      BitOut1 = 7,
      OUTPUTS_LEN = 8
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

void BitBusBitOut::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configOutput(Panel::BitOut8, "BitOut8");
   configOutput(Panel::BitOut7, "BitOut7");
   configOutput(Panel::BitOut6, "BitOut6");
   configOutput(Panel::BitOut5, "BitOut5");
   configOutput(Panel::BitOut4, "BitOut4");
   configOutput(Panel::BitOut3, "BitOut3");
   configOutput(Panel::BitOut2, "BitOut2");
   configOutput(Panel::BitOut1, "BitOut1");
}

void BitBusBitOutWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/BitBus/BitBusBitOut.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeOutput(this, Vec(30.00, 337.40), BitBusBitOut::Panel::BitOut8, true);
   makeOutput(this, Vec(30.00, 302.65), BitBusBitOut::Panel::BitOut7, true);
   makeOutput(this, Vec(30.00, 233.15), BitBusBitOut::Panel::BitOut6, true);
   makeOutput(this, Vec(30.00, 267.90), BitBusBitOut::Panel::BitOut5, true);
   makeOutput(this, Vec(30.00, 198.40), BitBusBitOut::Panel::BitOut4, true);
   makeOutput(this, Vec(30.00, 163.65), BitBusBitOut::Panel::BitOut3, true);
   makeOutput(this, Vec(30.00, 128.90), BitBusBitOut::Panel::BitOut2, true);
   makeOutput(this, Vec(30.00, 94.14), BitBusBitOut::Panel::BitOut1, true);

   makeLED(this, Vec(9.50, 46.77), BitBusBitOut::Panel::RGB_BusIn);
   makeLED(this, Vec(49.50, 46.77), BitBusBitOut::Panel::RGB_BusOut);
}

Model* modelBitBusBitOut = Svin::Origin::the()->addModule<BitBusBitOut, BitBusBitOutWidget>("BitBusBitOut");

#endif // NOT BitBusBitOutHPP