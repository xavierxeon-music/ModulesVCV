#ifndef VCVRackBridgeH
#define VCVRackBridgeH

#include <QApplication>

#include <Tools/Counter.h>

#include "Interface.h"
#include "MainWidget.h"

class VCVRackBridge
{
public:
   VCVRackBridge();
   ~VCVRackBridge();

public:
   void init(const float& sampleRate);
   void process(const Buffer& input, Buffer& output);

private:
   QApplication* app;
   MainWidget* mainWidget;

   float sampleRate;
   Counter guiRefreshCounter;
};

#endif // NOT VCVRackBridgeH
