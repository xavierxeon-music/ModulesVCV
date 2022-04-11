#include "Bridge.h"

#include "Schweinesystem.h"

#include <dlfcn.h>
#include <filesystem>
#include <fstream>
#include <iostream>

Bridge::Bridge()
   : Module()
   , libHandle(nullptr)
   , createFunction(nullptr)
   , initFunction(nullptr)
   , processFunction(nullptr)
   , terminateFunction(nullptr)
{
   config(0, 8, 8, 0);

   for (uint8_t index = 0; index < 8; index++)
   {
      configInput(index, "");
      configOutput(index, "");
   }

// TODO read brdige lib path from file
#if defined(__APPLE__)
   std::string libPath = std::string(getenv("HOME")) + "/Documents/Rack2/plugins/Schweinesystem/libVCVRackBridge.dylib";
#else
   std::string libPath = std::string(getenv("HOME")) + "/libWidget.so";
#endif
   std::cout << libPath << std::endl;

   libHandle = dlopen(libPath.c_str(), RTLD_LAZY);
   if (!libHandle)
   {
      std::cout << dlerror() << std::endl;
      return;
   }

   createFunction = reinterpret_cast<CreateFunction>(dlsym(libHandle, "create"));
   initFunction = reinterpret_cast<InitFunction>(dlsym(libHandle, "init"));
   processFunction = reinterpret_cast<ProcessFunction>(dlsym(libHandle, "process"));
   terminateFunction = reinterpret_cast<TerminateFunction>(dlsym(libHandle, "terminate"));

   if (createFunction && initFunction && processFunction && terminateFunction)
   {
      createFunction();
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
   if (!processFunction)
      return;

   static bool doneOnce = false;
   if (!doneOnce)
   {
      if (initFunction)
         initFunction(args.sampleRate);
      doneOnce = true;
   }

   Buffer input;
   Buffer output;
   for (uint8_t index = 0; index < 8; index++)
   {
      input[index] = inputs[index].getVoltage();
      output[index] = 0.0;
   }

   processFunction(input, output);

   for (uint8_t index = 0; index < 8; index++)
   {
      const float voltage = output[index];
      outputs[index].setVoltage(voltage);
   }
}

BridgeWidget::BridgeWidget(Bridge* module)
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
