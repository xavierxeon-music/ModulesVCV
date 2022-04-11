#include "VCVRackBridge.h"

VCVRackBridge::VCVRackBridge()
   : app(nullptr)
   , mainWidget(nullptr)
   , sampleRate(0.0)
   , maxRefreshCounter(100)
   , guiRefreshCounter(0)
{
   static int argc = 1;
   static const char* argv = "VCV Rack2 Bridge Loader";
   app = new QApplication(argc, const_cast<char**>(&argv));

   mainWidget = new MainWidget();
   mainWidget->show();
}

VCVRackBridge::~VCVRackBridge()
{
   delete app;
   app = nullptr;
}

void VCVRackBridge::init(const float& sampleRate)
{
   this->sampleRate = sampleRate;
   maxRefreshCounter = sampleRate / 100; // every 10 ms
}

void VCVRackBridge::process(const Buffer& input, Buffer& output)
{
   for (uint8_t index = 0; index < 8; index++)
   {
      output[index] = input[index];
   }

   guiRefreshCounter++;
   if (maxRefreshCounter == guiRefreshCounter)
   {
      app->processEvents();
      guiRefreshCounter = 0;
   }
}

static VCVRackBridge* bridge = nullptr;

// interface

extern "C"
{
   CREATE_FUNCTION
   {
      bridge = new VCVRackBridge;
   }

   INIT_FUNCTION
   {
      bridge->init(sampleRate);
   }

   PROCESS_FUNCTION
   {
      bridge->process(input, output);
   }

   TERMINATE_FUNCTION
   {
      delete bridge;
   }
}
