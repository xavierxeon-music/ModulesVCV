#include "BitBusCVOutPanel.h"
#include "BitBusCVOut.h"

#include <SvinMaster.h>

void BitBusCVOut::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configOutput(Panel::CVOut, "CVOut");
}

void BitBusCVOutWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Master::the()->instance(), "res/BitBus/BitBusCVOut.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeOutput(this, Vec(35.83, 169.98), BitBusCVOut::Panel::CVOut);

   makeLED(this, Vec(14.35, 346.69), BitBusCVOut::Panel::RGB_BusIn);
}
