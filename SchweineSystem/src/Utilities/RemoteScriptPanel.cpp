#include "RemoteScript.h"
#include "RemoteScriptPanel.h"

#include <SvinOrigin.h>

void RemoteScript::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Kill, "Kill");
   configButton(Panel::Restart, "Restart");
}

void RemoteScriptWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/Utilities/RemoteScript.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(29.50, 227.25), RemoteScript::Panel::Kill);
   makeButton(this, Vec(30.00, 170.36), RemoteScript::Panel::Restart);

   makeLED(this, Vec(30.00, 352.32), RemoteScript::Panel::RGB_Connected);

   makeOLED(this, Vec(9.00, 62.34), RemoteScript::Panel::Pixels_Display, 40, 40);
}

