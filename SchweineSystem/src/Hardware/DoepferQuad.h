#ifndef DoepferQuadH
#define DoepferQuadH

#include <rack.hpp>
using namespace rack;

#include <SchweineSystemButtonLED.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

#include "MidiBusModule.h"

class DoepferQuad : public SchweineSystem::Module, public MidiBusModule
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
   SchweineSystem::ButtonLED connectionButton;
};

// widget

class DoepferQuadWidget : public SchweineSystem::ModuleWidget
{
public:
   DoepferQuadWidget(DoepferQuad* module);

private:
   void setup();
};

#endif // NOT DoepferQuadH
