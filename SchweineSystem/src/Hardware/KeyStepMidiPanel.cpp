#include "KeyStepMidi.h"
#include "KeyStepMidiPanel.h"

#include <SchweineSystemMaster.h>

void KeyStepMidi::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");
}

void KeyStepMidiWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/Hardware/KeyStepMidi.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeLEDButton(this, Vec(29.95, 340.14), KeyStepMidi::Panel::Connect, KeyStepMidi::Panel::RGB_Connect);
}

