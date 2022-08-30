#include "BitBusTransmutorPanel.h"
#include "BitBusTransmutor.h"

#include <SvinOrigin.h>

void BitBusTransmutor::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Display, "Display");
}

void BitBusTransmutorWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/BitBus/BitBusTransmutor.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(59.84, 242.50), BitBusTransmutor::Panel::Display);

   makeLED(this, Vec(9.92, 46.77), BitBusTransmutor::Panel::RGB_BusIn);
   makeLED(this, Vec(79.92, 46.77), BitBusTransmutor::Panel::RGB_BusOut);

   makeOLED(this, Vec(14.42, 105.53), BitBusTransmutor::Panel::Pixels_Display, 60, 120);
}
