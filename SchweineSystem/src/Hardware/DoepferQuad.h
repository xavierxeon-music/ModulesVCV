#ifndef DoepferQuadH
#define DoepferQuadH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButtonLED.h>

class DoepferQuad : public Svin::Module, public Svin::MidiOutput
{
public:
   struct Panel;

public:
   DoepferQuad();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();
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
   inline void setup();
};

#ifndef DoepferQuadHPP
#include "DoepferQuad.hpp"
#endif // NOT DoepferQuadHPP

#endif // NOT DoepferQuadH
