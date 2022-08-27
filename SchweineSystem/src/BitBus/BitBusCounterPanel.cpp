#include "BitBusCounterPanel.h"
#include "BitBusCounter.h"

#include <SvinMaster.h>
#include <limits>

void BitBusCounter::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configInput(Panel::Reset, "Reset");
   configInput(Panel::Down, "Down");
   configInput(Panel::Up, "Up");

   configText(Panel::Text_Number, "Number");
}

void BitBusCounterWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Master::the()->instance(), "res/BitBus/BitBusCounter.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeInput(this, Vec(24.17, 253.42), BitBusCounter::Panel::Reset);
   makeInput(this, Vec(24.17, 169.98), BitBusCounter::Panel::Down);
   makeInput(this, Vec(24.17, 114.18), BitBusCounter::Panel::Up);

   makeLED(this, Vec(75.35, 346.69), BitBusCounter::Panel::RGB_BusOut);
   makeLED(this, Vec(65.77, 291.23), BitBusCounter::Panel::RGB_Bit8_Indicator);
   makeLED(this, Vec(65.77, 257.59), BitBusCounter::Panel::RGB_Bit7_Indicator);
   makeLED(this, Vec(65.77, 222.22), BitBusCounter::Panel::RGB_Bit6_Indicator);
   makeLED(this, Vec(65.77, 186.91), BitBusCounter::Panel::RGB_Bit5_Indicator);
   makeLED(this, Vec(65.77, 153.47), BitBusCounter::Panel::RGB_Bit4_Indicator);
   makeLED(this, Vec(65.77, 118.69), BitBusCounter::Panel::RGB_Bit3_Indicator);
   makeLED(this, Vec(65.77, 84.32), BitBusCounter::Panel::RGB_Bit2_Indicator);
   makeLED(this, Vec(65.77, 48.73), BitBusCounter::Panel::RGB_Bit1_Indicator);

   makeLCD(this, Vec(11.00, 320.77), 3, BitBusCounter::Panel::Text_Number, BitBusCounter::Panel::RGB_Number);
}
