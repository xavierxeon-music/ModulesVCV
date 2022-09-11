#include "HubConnect.h"
#include "HubConnectPanel.h"

#include <SvinOrigin.h>

void HubConnect::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");
}

void HubConnectWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/Utilities/HubConnect.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeLEDButton(this, Vec(30.00, 350.06), HubConnect::Panel::Connect, HubConnect::Panel::RGB_Connect);
}

