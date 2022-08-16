#include "DoepferQuadCV.h"
#include "DoepferQuadCVPanel.h"

#include <SchweineSystemMaster.h>

void DoepferQuadCV::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");

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

void DoepferQuadCVWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/Hardware/DoepferQuadCV.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeLEDButton(this, Vec(57.77, 359.49), DoepferQuadCV::Panel::Connect, DoepferQuadCV::Panel::RGB_Connect);

   makeInput(this, Vec(65.83, 328.13),  DoepferQuadCV::Panel::Channel4_In3);
   makeInput(this, Vec(65.83, 295.74),  DoepferQuadCV::Panel::Channel4_In2);
   makeInput(this, Vec(65.83, 263.34),  DoepferQuadCV::Panel::Channel4_In1);
   makeInput(this, Vec(24.17, 328.07),  DoepferQuadCV::Panel::Channel3_In3);
   makeInput(this, Vec(24.17, 295.68),  DoepferQuadCV::Panel::Channel3_In2);
   makeInput(this, Vec(24.17, 263.28),  DoepferQuadCV::Panel::Channel3_In1);
   makeInput(this, Vec(65.83, 217.61),  DoepferQuadCV::Panel::Channel2_In3);
   makeInput(this, Vec(65.83, 185.22),  DoepferQuadCV::Panel::Channel2_In2);
   makeInput(this, Vec(65.83, 152.82),  DoepferQuadCV::Panel::Channel2_In1);
   makeInput(this, Vec(24.17, 217.55),  DoepferQuadCV::Panel::Channel1_In3);
   makeInput(this, Vec(24.17, 185.16),  DoepferQuadCV::Panel::Channel1_In2);
   makeInput(this, Vec(24.17, 152.76),  DoepferQuadCV::Panel::Channel1_In1);
}

