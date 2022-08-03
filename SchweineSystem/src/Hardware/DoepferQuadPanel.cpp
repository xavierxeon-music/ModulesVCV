#include "DoepferQuad.h"
#include "DoepferQuadPanel.h"

#include <SchweineSystemButtonLED.h>
#include <SchweineSystemMaster.h>

void DoepferQuad::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configInput(Panel::Channel4_In3, "Channel4_In3");
   configInput(Panel::Channel4_In2, "Channel4_In2");
   configInput(Panel::Channel4_In1, "Channel4_In1");
   configInput(Panel::Channel3_In3, "Channel3_In3");
   configInput(Panel::Channel3_In2, "Channel3_In2");
   configInput(Panel::Channel3_In1, "Channel3_In1");
   configInput(Panel::Channel2_In3, "Channel2_In3");
   configInput(Panel::Channel2_In2, "Channel2_In2");
   configInput(Panel::Channel2_In1, "Channel2_In1");
   configInput(Panel::Channel1_In3, "Channel1_In3");
   configInput(Panel::Channel1_In2, "Channel1_In2");
   configInput(Panel::Channel1_In1, "Channel1_In1");
}

void DoepferQuadWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/Hardware/DoepferQuad.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeLEDButton(this, Vec(57.77, 359.49), DoepferQuad::Panel::Connect, DoepferQuad::Panel::RGB_Connect);

   makeInput(this, Vec(65.83, 328.13),  DoepferQuad::Panel::Channel4_In3);
   makeInput(this, Vec(65.83, 295.74),  DoepferQuad::Panel::Channel4_In2);
   makeInput(this, Vec(65.83, 263.34),  DoepferQuad::Panel::Channel4_In1);
   makeInput(this, Vec(24.17, 328.07),  DoepferQuad::Panel::Channel3_In3);
   makeInput(this, Vec(24.17, 295.68),  DoepferQuad::Panel::Channel3_In2);
   makeInput(this, Vec(24.17, 263.28),  DoepferQuad::Panel::Channel3_In1);
   makeInput(this, Vec(65.83, 217.61),  DoepferQuad::Panel::Channel2_In3);
   makeInput(this, Vec(65.83, 185.22),  DoepferQuad::Panel::Channel2_In2);
   makeInput(this, Vec(65.83, 152.82),  DoepferQuad::Panel::Channel2_In1);
   makeInput(this, Vec(24.17, 217.55),  DoepferQuad::Panel::Channel1_In3);
   makeInput(this, Vec(24.17, 185.16),  DoepferQuad::Panel::Channel1_In2);
   makeInput(this, Vec(24.17, 152.76),  DoepferQuad::Panel::Channel1_In1);
}

