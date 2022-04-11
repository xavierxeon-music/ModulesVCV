#include "Bridge.h"

#include "Schweinesystem.h"

#include <dlfcn.h>
#include <filesystem>
#include <fstream>
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

   initFunction = reinterpret_cast<InitFunction>(dlsym(handle, "init"));
   loopFunction = reinterpret_cast<LoopFunction>(dlsym(handle, "loop"));
   terminateFunction = reinterpret_cast<TerminateFunction>(dlsym(handle, "terminate"));

   if (initFunction && loopFunction && terminateFunction)
   {
      static char *appName = "VCV Rack2 Bridge";
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

void Bridge::process(const ProcessArgs &args)
{
   if (!loopFunction)
      return;

   for (uint8_t index = 0; index < 8; index++)
   {
      const float voltage = inputs[index].geVoltage();
   }

   loopFunction();

   for (uint8_t index = 0; index < 8; index++)
   {
      const float voltage = 0.0;
      outputs[index].seetVoltage(voltage);
   }
}

BridgeWidget::BridgeWidget(Bridge *module)
    : ModuleWidget()
{
   setModule(module);
   setPanel(createPanel(asset::plugin(Schweinesystem::instance(), "res/Bridge.svg")));

   const float inX = 8.5;
   const float outX = 22.5;
   const float y[] = {16.5, 30.0, 43.5, 57.0, 71.5, 85.0, 98.5, 112.0};

   for (uint8_t index = 0; index < 8; index++)
   {
      addInput(createInputCentered<PJ301MPort>(mm2px(Vec(inX, y[index])), module, index));
      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(outX, y[index])), module, index));
   }
}
