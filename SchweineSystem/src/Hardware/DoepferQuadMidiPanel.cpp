#include "DoepferQuadMidi.h"
#include "DoepferQuadMidiPanel.h"

#include <SchweineSystemMaster.h>

void DoepferQuadMidi::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");
}

void DoepferQuadMidiWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/Hardware/DoepferQuadMidi.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeLEDButton(this, Vec(29.95, 340.14), DoepferQuadMidi::Panel::Connect, DoepferQuadMidi::Panel::RGB_Connect);
}

