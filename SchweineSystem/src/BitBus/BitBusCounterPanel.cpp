#include "BitBusCounter.h"
#include "BitBusCounterPanel.h"

#include <SvinMaster.h>
#include <limits>

void BitBusCounter::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configInput(Panel::Reset, "Reset");
   configInput(Panel::Down, "Down");
   configInput(Panel::Up, "Up");
}

void BitBusCounterWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Master::the()->instance(), "res/BitBus/BitBusCounter.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeInput(this, Vec(24.17, 299.21),  BitBusCounter::Panel::Reset, false);
   makeInput(this, Vec(24.17, 215.77),  BitBusCounter::Panel::Down, false);
   makeInput(this, Vec(24.17, 159.97),  BitBusCounter::Panel::Up, false);

   makeLED(this, Vec(65.77, 337.02), BitBusCounter::Panel::RGB_Bit8_Indicator);
   makeLED(this, Vec(65.77, 303.38), BitBusCounter::Panel::RGB_Bit7_Indicator);
   makeLED(this, Vec(65.77, 268.01), BitBusCounter::Panel::RGB_Bit6_Indicator);
   makeLED(this, Vec(65.77, 232.71), BitBusCounter::Panel::RGB_Bit5_Indicator);
   makeLED(this, Vec(65.77, 199.26), BitBusCounter::Panel::RGB_Bit4_Indicator);
   makeLED(this, Vec(65.77, 164.48), BitBusCounter::Panel::RGB_Bit3_Indicator);
   makeLED(this, Vec(65.77, 130.11), BitBusCounter::Panel::RGB_Bit2_Indicator);
   makeLED(this, Vec(65.77, 94.53), BitBusCounter::Panel::RGB_Bit1_Indicator);
   makeLED(this, Vec(79.92, 46.77), BitBusCounter::Panel::RGB_BusOut);

   makeLCD(this, Vec(20.00, 42.49), 3, BitBusCounter::Panel::Text_Number, 18);
}

