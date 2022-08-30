#include "FlameCCSenderPanel.h"
#include "FlameCCSender.h"

#include <SvinOrigin.h>

void FlameCCSender::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configSwitch(Panel::Half, 0.0f, 1.0f, 0.0f, "Half");

   configButton(Panel::Connect, "Connect");

   configInput(Panel::Voltages, "Voltages");
}

void FlameCCSenderWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/Hardware/FlameCCSender.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeSwitch(this, Vec(37.78, 194.76), FlameCCSender::Panel::Half);

   makeLEDButton(this, Vec(30.00, 350.06), FlameCCSender::Panel::Connect, FlameCCSender::Panel::RGB_Connect);

   makeInput(this, Vec(30.00, 261.36), FlameCCSender::Panel::Voltages, true);
}
