#include "BitBusBitInPanel.h"
#include "BitBusBitIn.h"

#include <SvinMaster.h>

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
   std::string panelPath = asset::plugin(Svin::Master::the()->instance(), "res/BitBus/BitBusBitIn.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeInput(this, Vec(30.00, 291.61), BitBusBitIn::Panel::BitIn8);
   makeInput(this, Vec(30.00, 256.86), BitBusBitIn::Panel::BitIn7);
   makeInput(this, Vec(30.00, 187.36), BitBusBitIn::Panel::BitIn6);
   makeInput(this, Vec(30.00, 222.11), BitBusBitIn::Panel::BitIn5);
   makeInput(this, Vec(30.00, 152.61), BitBusBitIn::Panel::BitIn4);
   makeInput(this, Vec(30.00, 117.85), BitBusBitIn::Panel::BitIn3);
   makeInput(this, Vec(30.00, 83.10), BitBusBitIn::Panel::BitIn2);
   makeInput(this, Vec(30.00, 48.35), BitBusBitIn::Panel::BitIn1);

   makeLED(this, Vec(45.35, 346.69), BitBusBitIn::Panel::RGB_BusOut);
   makeLED(this, Vec(14.35, 346.69), BitBusBitIn::Panel::RGB_BusIn);
}
