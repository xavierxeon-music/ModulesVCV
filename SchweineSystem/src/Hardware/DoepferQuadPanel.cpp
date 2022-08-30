#include "DoepferQuadPanel.h"
#include "DoepferQuad.h"

#include <SvinOrigin.h>

void DoepferQuad::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");
}

void DoepferQuadWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/Hardware/DoepferQuad.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeLEDButton(this, Vec(30.00, 340.14), DoepferQuad::Panel::Connect, DoepferQuad::Panel::RGB_Connect);
}
