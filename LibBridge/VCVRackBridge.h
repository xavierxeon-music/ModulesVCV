#ifndef VCVRackBridgeH
#define VCVRackBridgeH

#include <QApplication>

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

   uint16_t maxRefreshCounter;
   uint16_t guiRefreshCounter;
};

#endif // NOT VCVRackBridgeH
