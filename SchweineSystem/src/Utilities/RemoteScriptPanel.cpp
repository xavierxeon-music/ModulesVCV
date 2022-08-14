#include "RemoteScript.h"
#include "RemoteScriptPanel.h"

#include <SchweineSystemMaster.h>

void RemoteScript::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Kill, "Kill");
   configButton(Panel::Restart, "Restart");

   configButton(Panel::Connect, "Connect");

   configPixels(Panel::Pixels_Display, 40, 40, "Display");
}

void RemoteScriptWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/Utilities/RemoteScript.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(29.50, 227.25), RemoteScript::Panel::Kill);
   makeButton(this, Vec(30.00, 170.36), RemoteScript::Panel::Restart);

   makeLEDButton(this, Vec(30.00, 355.83), RemoteScript::Panel::Connect, RemoteScript::Panel::RGB_Connect);

   makeOLED(this, Vec(9.00, 56.34), RemoteScript::Panel::Pixels_Display, 40, 40);
}

