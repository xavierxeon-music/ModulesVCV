#include "Bridge.h"

#include "Schweinesystem.h"

#include <dlfcn.h>
#include <filesystem>
#include <iostream>

Bridge::Bridge()
   : Module()
{
   config(0, INPUTS_LEN, OUTPUTS_LEN, 0);

   configInput(INPUT_1, "");
   configInput(INPUT_2, "");
   configInput(INPUT_3, "");
   configInput(INPUT_4, "");

   configInput(INPUT_5, "");
   configInput(INPUT_6, "");
   configInput(INPUT_7, "");
   configInput(INPUT_8, "");

   configOutput(OUTPUT_1, "");
   configOutput(OUTPUT_2, "");
   configOutput(OUTPUT_3, "");
   configOutput(OUTPUT_4, "");

   configOutput(OUTPUT_5, "");
   configOutput(OUTPUT_6, "");
   configOutput(OUTPUT_7, "");
   configOutput(OUTPUT_8, "");

#if defined(__APPLE__)
   std::string libPath = std::string(getenv("HOME")) + "/tmp/LibChain/bin/libWidget.dylib";
#else
   std::string libPath = std::string(getenv("HOME")) + "/libWidget.so";
#endif
   std::cout << libPath << std::endl;

   handle = dlopen(libPath.c_str(), RTLD_LAZY);
   if (!handle)
   {
      std::cout << dlerror() << std::endl;
      return;
   }

   InitFunction initFunction = reinterpret_cast<InitFunction>(dlsym(handle, "init"));
   LoopFunction loopFunction = reinterpret_cast<LoopFunction>(dlsym(handle, "loop"));
   TerminateFunction terminateFunction = reinterpret_cast<TerminateFunction>(dlsym(handle, "terminate"));

   if (initFunction && loopFunction && terminateFunction)
   {
      static char* appName = "VCV Rack2 Bridge";
      initFunction(1, &appName);
   }
   else
   {
      std::cout << dlerror() << std::endl;
   }
}

Bridge::~Bridge()
{
   if (terminateFunction)
      terminateFunction();
}

void Bridge::process(const ProcessArgs& args)
{
   if (loopFunction)
      loopFunction(0);

   //outputs[RANDOM_OUTPUT].setVoltage(5.f * sine);
}

BridgeWidget::BridgeWidget(Bridge* module)
   : ModuleWidget()
{
   setModule(module);
   setPanel(createPanel(asset::plugin(Schweinesystem::instance(), "res/Bridge.svg")));

   // screws
   addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
   addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
   addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
   addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

   const float y[] = {16.5, 30.0, 43.5, 57.0, 71.5, 85.0, 98.5, 112.0};
   // inputs
   const float inX = 8.5;
   addInput(createInputCentered<PJ301MPort>(mm2px(Vec(inX, y[0])), module, Bridge::INPUT_1));
   addInput(createInputCentered<PJ301MPort>(mm2px(Vec(inX, y[1])), module, Bridge::INPUT_2));
   addInput(createInputCentered<PJ301MPort>(mm2px(Vec(inX, y[2])), module, Bridge::INPUT_3));
   addInput(createInputCentered<PJ301MPort>(mm2px(Vec(inX, y[3])), module, Bridge::INPUT_4));
   addInput(createInputCentered<PJ301MPort>(mm2px(Vec(inX, y[4])), module, Bridge::INPUT_5));
   addInput(createInputCentered<PJ301MPort>(mm2px(Vec(inX, y[5])), module, Bridge::INPUT_6));
   addInput(createInputCentered<PJ301MPort>(mm2px(Vec(inX, y[6])), module, Bridge::INPUT_7));
   addInput(createInputCentered<PJ301MPort>(mm2px(Vec(inX, y[7])), module, Bridge::INPUT_8));

   // outputs
   const float outX = 22.5;
   addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(outX, y[0])), module, Bridge::OUTPUT_1));
   addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(outX, y[1])), module, Bridge::OUTPUT_2));
   addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(outX, y[2])), module, Bridge::OUTPUT_3));
   addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(outX, y[3])), module, Bridge::OUTPUT_4));
   addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(outX, y[4])), module, Bridge::OUTPUT_5));
   addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(outX, y[5])), module, Bridge::OUTPUT_6));
   addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(outX, y[6])), module, Bridge::OUTPUT_7));
   addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(outX, y[7])), module, Bridge::OUTPUT_8));
}
