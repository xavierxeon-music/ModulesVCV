#ifndef VCMCReceiverH
#define VCMCReceiverH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

class VCMCReceiver : public Svin::Module
{
public:
   struct Panel;

public:
   VCMCReceiver();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
};

// widget

class VCMCReceiverWidget : public Svin::ModuleWidget
{
public:
   VCMCReceiverWidget(VCMCReceiver* module);

private:
   void setup();
};

#endif // NOT VCMCReceiverH
