#ifndef HubConnectHPP
#define HubConnectHPP

#include "HubConnect.h"

#include <SvinOrigin.h>

struct HubConnect::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      Connect = 0,
      // knobs
      // sliders
      PARAMS_LEN = 1
   };

   enum DisplayId
   {
      // lcd
      // oled
      DISPLAYS_LEN = 0
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      INPUTS_LEN = 0
   };

   enum OutputId
   {
      OUTPUTS_LEN = 0
   };

   enum LightId
   {
      // leds
      // ledbuttons
      RGB_Connect = 0,
      // sliders
      LIGHTS_LEN = 3
   };

};

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

Model* modelHubConnect = Svin::Origin::the()->addModule<HubConnect, HubConnectWidget>("HubConnect");

#endif // NOT HubConnectHPP
