#include "BitBusCVIn.h"
#include "BitBusCVInPanel.h"

#include <SchweineSystemMaster.h>

void BitBusCVIn::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configInput(Panel::CVIn, "CVIn");
}

void BitBusCVInWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/BitBusCVIn.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeInput(this, Vec(24.17, 169.98),  BitBusCVIn::Panel::CVIn);

   makeLED(this, Vec(45.35, 346.69), BitBusCVIn::Panel::RGB_BusOut);
}

