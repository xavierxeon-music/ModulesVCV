#include "BitBusTransmutor.h"
#include "BitBusTransmutorPanel.h"

#include <SyMaster.h>

void BitBusTransmutor::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Display, "Display");

   configPixels(Panel::Pixels_Display, 60, 120, "Display");
}

void BitBusTransmutorWidget::setup()
{
   std::string panelPath = asset::plugin(Sy::Master::the()->instance(), "res/BitBus/BitBusTransmutor.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(59.42, 196.72), BitBusTransmutor::Panel::Display);

   makeLED(this, Vec(14.35, 346.69), BitBusTransmutor::Panel::RGB_BusIn);
   makeLED(this, Vec(75.35, 346.69), BitBusTransmutor::Panel::RGB_BusOut);

   makeOLED(this, Vec(14.00, 59.75), BitBusTransmutor::Panel::Pixels_Display, 60, 120);
}

