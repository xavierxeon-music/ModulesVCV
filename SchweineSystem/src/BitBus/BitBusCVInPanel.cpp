#include "BitBusCVIn.h"
#include "BitBusCVInPanel.h"

#include <SvinOrigin.h>

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

