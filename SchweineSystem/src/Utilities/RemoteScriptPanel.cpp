#include "RemoteScript.h"
#include "RemoteScriptPanel.h"

#include <SchweineSystemMaster.h>

void RemoteScript::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");

   configPixels(Panel::Pixels_Display, 40, 40, "Display");
}

void RemoteScriptWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "/Users/waspe/GitHub/MusicProjects/ModulesVCV/SchweineSystem/res/Utilities/RemoteScript.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeLEDButton(this, Vec(30.00, 355.83), RemoteScript::Panel::Connect, RemoteScript::Panel::RGB_Connect);

   makeOLED(this, Vec(9.00, 56.34), RemoteScript::Panel::Pixels_Display, 40, 40);
}

