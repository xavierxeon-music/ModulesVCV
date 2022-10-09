#include "HubConnect.h"

#include <SvinOrigin.h>

HubConnect::HubConnect()
   : Svin::Module()
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
{
   setup();
   connectionButton.setDefaultColor(Color::Predefined::Green);
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

// create module
Model* modelHubConnect = Svin::Origin::the()->addModule<HubConnect, HubConnectWidget>("HubConnect");

