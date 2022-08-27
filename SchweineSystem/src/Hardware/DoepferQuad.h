#ifndef DoepferQuadH
#define DoepferQuadH

#include <rack.hpp>
using namespace rack;

#include <SvinButtonLED.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include "MidiBusModule.h"

class DoepferQuad : public Svin::Module, public MidiBusModule
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
   Svin::ButtonLED connectionButton;
};

// widget

class DoepferQuadWidget : public Svin::ModuleWidget
{
public:
   DoepferQuadWidget(DoepferQuad* module);

private:
   void setup();
};

#endif // NOT DoepferQuadH
