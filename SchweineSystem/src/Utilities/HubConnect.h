#ifndef HubConnectH
#define HubConnectH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButtonLED.h>

class HubConnect : public Svin::Module
{
public:
   struct Panel;

public:
   HubConnect();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();

private:
   Svin::ButtonLED connectionButton;
};

// widget

class HubConnectWidget : public Svin::ModuleWidget
{
public:
   HubConnectWidget(HubConnect* module);

private:
   void setup();
};

#endif // NOT HubConnectH
