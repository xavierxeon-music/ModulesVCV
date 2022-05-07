#include "BitBusBitOut.h"
#include "BitBusBitOutPanel.h"

#include <SchweineSystemMaster.h>

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
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/BitBusBitOut.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeOutput(this, Vec(30.00, 291.61), BitBusBitOut::Panel::BitOut8);
   makeOutput(this, Vec(30.00, 256.86), BitBusBitOut::Panel::BitOut7);
   makeOutput(this, Vec(30.00, 187.36), BitBusBitOut::Panel::BitOut6);
   makeOutput(this, Vec(30.00, 222.11), BitBusBitOut::Panel::BitOut5);
   makeOutput(this, Vec(30.00, 152.61), BitBusBitOut::Panel::BitOut4);
   makeOutput(this, Vec(30.00, 117.85), BitBusBitOut::Panel::BitOut3);
   makeOutput(this, Vec(30.00, 83.10), BitBusBitOut::Panel::BitOut2);
   makeOutput(this, Vec(30.00, 48.35), BitBusBitOut::Panel::BitOut1);

   makeLED(this, Vec(14.35, 346.69), BitBusBitOut::Panel::RGB_BusIn);
   makeLED(this, Vec(46.35, 346.69), BitBusBitOut::Panel::RGB_BusOut);
}

