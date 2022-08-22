#ifndef DoepferQuadH
#define DoepferQuadH

#include <rack.hpp>
using namespace rack;

#include <SyButtonLED.h>
#include <SyModule.h>
#include <SyModuleWidget.h>

#include "MidiBusModule.h"

class DoepferQuad : public Sy::Module, public MidiBusModule
{
public:
   struct Panel;

public:
   DoepferQuad();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
   void connectToMidiDevice();

private:
   Sy::ButtonLED connectionButton;
};

// widget

class DoepferQuadWidget : public Sy::ModuleWidget
{
public:
   DoepferQuadWidget(DoepferQuad* module);

private:
   void setup();
};

#endif // NOT DoepferQuadH
