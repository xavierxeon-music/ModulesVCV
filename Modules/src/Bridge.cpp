#include "Bridge.h"

#include "Schweinesystem.h"

#include <iostream>

Bridge::Bridge()
   : Module()
{
   config(0, 8, 8, 0);

   for (uint8_t index = 0; index < 8; index++)
   {
      configInput(index, "");
      configOutput(index, "");
   }
}

Bridge::~Bridge()
{
}

void Bridge::process(const ProcessArgs& args)
{
   for (uint8_t index = 0; index < 8; index++)
   {
      const float voltage = inputs[index].getVoltage();
      outputs[index].setVoltage(voltage);
   }
}

BridgeWidget::BridgeWidget(Bridge* module)
   : ModuleWidget()
{
   setModule(module);
   std::string panelPath = asset::plugin(Schweinesystem::instance(), "res/Bridge.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   const float inX = 8.5;
   const float outX = 22.5;
   const float y[] = {16.5, 30.0, 43.5, 57.0, 71.5, 85.0, 98.5, 112.0};

   for (uint8_t index = 0; index < 8; index++)
   {
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(inX, y[index])), module, index));
      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(outX, y[index])), module, index));
   }
}
