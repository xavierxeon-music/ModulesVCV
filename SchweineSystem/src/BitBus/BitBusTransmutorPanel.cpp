#include "BitBusTransmutor.h"
#include "BitBusTransmutorPanel.h"

#include <SvinOrigin.h>
#include <limits>

void BitBusTransmutor::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Down, "Down");
   configButton(Panel::Up, "Up");

   configSwitch(Panel::Mix, 0.0f, 1.0f, 0.0f, "Mix");

   configInput(Panel::Scan, "Scan");
}

void BitBusTransmutorWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/BitBus/BitBusTransmutor.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(45.44, 255.81), BitBusTransmutor::Panel::Down);
   makeButton(this, Vec(45.44, 210.30), BitBusTransmutor::Panel::Up);

   makeSlider(this, Vec(45.00, 138.86), BitBusTransmutor::Panel::Mix, BitBusTransmutor::Panel::RGB_Mix);

   makeInput(this, Vec(45.00, 320.30),  BitBusTransmutor::Panel::Scan, false);

   makeLED(this, Vec(9.92, 46.77), BitBusTransmutor::Panel::RGB_BusIn);
   makeLED(this, Vec(79.92, 46.77), BitBusTransmutor::Panel::RGB_BusOut);

   makeLCD(this, Vec(20.44, 220.55), 3, BitBusTransmutor::Panel::Text_Bank, 18);
}

