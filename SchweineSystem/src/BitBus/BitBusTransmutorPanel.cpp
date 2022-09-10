#include "BitBusTransmutor.h"
#include "BitBusTransmutorPanel.h"

#include <SvinOrigin.h>
#include <limits>

void BitBusTransmutor::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Seed_Up, "Seed_Up");
   configButton(Panel::Seed_Down, "Seed_Down");
}

void BitBusTransmutorWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/BitBus/BitBusTransmutor.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(45.00, 167.75), BitBusTransmutor::Panel::Seed_Up);
   makeButton(this, Vec(45.00, 212.25), BitBusTransmutor::Panel::Seed_Down);

   makeLED(this, Vec(9.92, 46.77), BitBusTransmutor::Panel::RGB_BusIn);
   makeLED(this, Vec(79.92, 46.77), BitBusTransmutor::Panel::RGB_BusOut);

   makeLCD(this, Vec(20.00, 178.00), 3, BitBusTransmutor::Panel::Text_Seed_Number, 18);
}

