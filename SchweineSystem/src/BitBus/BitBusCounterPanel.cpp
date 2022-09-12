#include "BitBusCounter.h"
#include "BitBusCounterPanel.h"

#include <SvinOrigin.h>
#include <limits>

void BitBusCounter::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configSwitch(Panel::Threshold, 0.0f, 1.0f, 0.0f, "Threshold");

   configInput(Panel::Reset, "Reset");
   configInput(Panel::Down, "Down");
   configInput(Panel::Up, "Up");
}

void BitBusCounterWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/BitBus/BitBusCounter.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeSlider(this, Vec(23.72, 130.24), BitBusCounter::Panel::Threshold, BitBusCounter::Panel::RGB_Threshold);

   makeInput(this, Vec(23.72, 344.87),  BitBusCounter::Panel::Reset, false);
   makeInput(this, Vec(23.72, 261.44),  BitBusCounter::Panel::Down, false);
   makeInput(this, Vec(23.72, 205.64),  BitBusCounter::Panel::Up, false);

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

