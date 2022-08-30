#include "BitBusBitInPanel.h"
#include "BitBusBitIn.h"

#include <SvinOrigin.h>

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

   makeInput(this, Vec(30.00, 337.40), BitBusBitIn::Panel::BitIn8, false);
   makeInput(this, Vec(30.00, 302.65), BitBusBitIn::Panel::BitIn7, false);
   makeInput(this, Vec(30.00, 233.15), BitBusBitIn::Panel::BitIn6, false);
   makeInput(this, Vec(30.00, 267.90), BitBusBitIn::Panel::BitIn5, false);
   makeInput(this, Vec(30.00, 198.40), BitBusBitIn::Panel::BitIn4, false);
   makeInput(this, Vec(30.00, 163.65), BitBusBitIn::Panel::BitIn3, false);
   makeInput(this, Vec(30.00, 128.90), BitBusBitIn::Panel::BitIn2, false);
   makeInput(this, Vec(30.00, 94.14), BitBusBitIn::Panel::BitIn1, false);

   makeLED(this, Vec(10.50, 46.77), BitBusBitIn::Panel::RGB_BusIn);
   makeLED(this, Vec(50.00, 46.77), BitBusBitIn::Panel::RGB_BusOut);
}
