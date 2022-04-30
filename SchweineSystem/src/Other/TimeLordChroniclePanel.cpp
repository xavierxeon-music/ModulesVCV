#include "TimeLordChronicle.h"
#include "TimeLordChroniclePanel.h"

#include <SchweineSystemMaster.h>
#include <limits>

void TimeLordChronicle::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configInput(Panel::Channel8_Input, "Channel8_Input");
   configInput(Panel::Channel7_Input, "Channel7_Input");
   configInput(Panel::Channel6_Input, "Channel6_Input");
   configInput(Panel::Channel5_Input, "Channel5_Input");
   configInput(Panel::Channel4_Input, "Channel4_Input");
   configInput(Panel::Channel3_Input, "Channel3_Input");
   configInput(Panel::Channel2_Input, "Channel2_Input");
   configInput(Panel::Channel1_Input, "Channel1_Input");

   configDisplay(Panel::Text_Channel8_Display, "Channel8_Display");
   configDisplay(Panel::Text_Channel7_Display, "Channel7_Display");
   configDisplay(Panel::Text_Channel6_Display, "Channel6_Display");
   configDisplay(Panel::Text_Channel5_Display, "Channel5_Display");
   configDisplay(Panel::Text_Channel4_Display, "Channel4_Display");
   configDisplay(Panel::Text_Channel3_Display, "Channel3_Display");
   configDisplay(Panel::Text_Channel2_Display, "Channel2_Display");
   configDisplay(Panel::Text_Channel1_Display, "Channel1_Display");

   configMeter(Panel::Value_Channel8_Strip, "Channel8_Strip");
   configMeter(Panel::Value_Channel7_Strip, "Channel7_Strip");
   configMeter(Panel::Value_Channel6_Strip, "Channel6_Strip");
   configMeter(Panel::Value_Channel5_Strip, "Channel5_Strip");
   configMeter(Panel::Value_Channel4_Strip, "Channel4_Strip");
   configMeter(Panel::Value_Channel3_Strip, "Channel3_Strip");
   configMeter(Panel::Value_Channel2_Strip, "Channel2_Strip");
   configMeter(Panel::Value_Channel1_Strip, "Channel1_Strip");
}

void TimeLordChronicleWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/TimeLordChronicle.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeInput(this, Vec(35.08, 328.37),  TimeLordChronicle::Panel::Channel8_Input);
   makeInput(this, Vec(35.08, 291.89),  TimeLordChronicle::Panel::Channel7_Input);
   makeInput(this, Vec(35.08, 255.41),  TimeLordChronicle::Panel::Channel6_Input);
   makeInput(this, Vec(35.08, 218.93),  TimeLordChronicle::Panel::Channel5_Input);
   makeInput(this, Vec(35.08, 182.46),  TimeLordChronicle::Panel::Channel4_Input);
   makeInput(this, Vec(35.08, 145.98),  TimeLordChronicle::Panel::Channel3_Input);
   makeInput(this, Vec(35.08, 109.50),  TimeLordChronicle::Panel::Channel2_Input);
   makeInput(this, Vec(35.08, 73.03),  TimeLordChronicle::Panel::Channel1_Input);

   makeDisplay(this, Vec(60.00, 316.37), 3, TimeLordChronicle::Panel::Text_Channel8_Display, TimeLordChronicle::Panel::RGB_Channel8_Display);
   makeDisplay(this, Vec(60.00, 279.89), 3, TimeLordChronicle::Panel::Text_Channel7_Display, TimeLordChronicle::Panel::RGB_Channel7_Display);
   makeDisplay(this, Vec(60.00, 243.41), 3, TimeLordChronicle::Panel::Text_Channel6_Display, TimeLordChronicle::Panel::RGB_Channel6_Display);
   makeDisplay(this, Vec(60.00, 206.94), 3, TimeLordChronicle::Panel::Text_Channel5_Display, TimeLordChronicle::Panel::RGB_Channel5_Display);
   makeDisplay(this, Vec(60.00, 170.46), 3, TimeLordChronicle::Panel::Text_Channel4_Display, TimeLordChronicle::Panel::RGB_Channel4_Display);
   makeDisplay(this, Vec(60.00, 133.98), 3, TimeLordChronicle::Panel::Text_Channel3_Display, TimeLordChronicle::Panel::RGB_Channel3_Display);
   makeDisplay(this, Vec(60.00, 97.50), 3, TimeLordChronicle::Panel::Text_Channel2_Display, TimeLordChronicle::Panel::RGB_Channel2_Display);
   makeDisplay(this, Vec(60.00, 61.03), 3, TimeLordChronicle::Panel::Text_Channel1_Display, TimeLordChronicle::Panel::RGB_Channel1_Display);

   makeMeter(this, Vec(51.31, 315.37), 5, TimeLordChronicle::Panel::Value_Channel8_Strip);
   makeMeter(this, Vec(51.31, 278.89), 5, TimeLordChronicle::Panel::Value_Channel7_Strip);
   makeMeter(this, Vec(51.31, 242.41), 5, TimeLordChronicle::Panel::Value_Channel6_Strip);
   makeMeter(this, Vec(51.31, 205.93), 5, TimeLordChronicle::Panel::Value_Channel5_Strip);
   makeMeter(this, Vec(51.31, 169.46), 5, TimeLordChronicle::Panel::Value_Channel4_Strip);
   makeMeter(this, Vec(51.31, 132.98), 5, TimeLordChronicle::Panel::Value_Channel3_Strip);
   makeMeter(this, Vec(51.31, 96.50), 5, TimeLordChronicle::Panel::Value_Channel2_Strip);
   makeMeter(this, Vec(51.31, 60.03), 5, TimeLordChronicle::Panel::Value_Channel1_Strip);
}

