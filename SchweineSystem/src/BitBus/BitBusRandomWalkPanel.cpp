#include "BitBusRandomWalk.h"
#include "BitBusRandomWalkPanel.h"

#include <SvinOrigin.h>
#include <limits>

void BitBusRandomWalk::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Down, "Down");
   configButton(Panel::Up, "Up");

   configSwitch(Panel::Mix, 0.0f, 1.0f, 0.0f, "Mix");

   configInput(Panel::Scan, "Scan");
}

void BitBusRandomWalkWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/BitBus/BitBusRandomWalk.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(45.44, 255.81), BitBusRandomWalk::Panel::Down);
   makeButton(this, Vec(45.44, 210.30), BitBusRandomWalk::Panel::Up);

   makeSlider(this, Vec(45.00, 138.86), BitBusRandomWalk::Panel::Mix, BitBusRandomWalk::Panel::RGB_Mix);

   makeInput(this, Vec(45.00, 320.30),  BitBusRandomWalk::Panel::Scan, false);

   makeLED(this, Vec(9.92, 46.77), BitBusRandomWalk::Panel::RGB_BusIn);
   makeLED(this, Vec(79.92, 46.77), BitBusRandomWalk::Panel::RGB_BusOut);

   makeLCD(this, Vec(20.44, 220.55), 3, BitBusRandomWalk::Panel::Text_Bank, 18);
}

