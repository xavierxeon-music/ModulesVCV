#include "BitBusBitOut.h"
#include "BitBusBitOutPanel.h"

#include <SvinOrigin.h>

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

