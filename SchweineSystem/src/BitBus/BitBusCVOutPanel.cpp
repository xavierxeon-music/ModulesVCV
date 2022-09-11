#include "BitBusCVOut.h"
#include "BitBusCVOutPanel.h"

#include <SvinOrigin.h>

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

