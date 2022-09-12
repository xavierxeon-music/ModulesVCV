#include "HubConnect.h"
#include "HubConnectPanel.h"

#include <SvinOrigin.h>

HubConnect::HubConnect()
   : Svin::Module()
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
{
   setup();
   connectionButton.setDefaultColor(Svin::Color{0, 255, 0});
}

void HubConnect::process(const ProcessArgs& args)
{
   if (connectionButton.isTriggered())
      connectToHub();

   connectionButton.setActive(hubConnected());
}

// widget

HubConnectWidget::HubConnectWidget(HubConnect* module)
: Svin::ModuleWidget(module)
{
   setup();
}

Model* modelHubConnect = Svin::Origin::the()->addModule<HubConnect, HubConnectWidget>("HubConnect");