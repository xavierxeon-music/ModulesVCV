#ifndef MeshStackH
#define MeshStackH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinInput.h>
#include <SvinKnob.h>
#include <SvinLED.h>
#include <SvinOutput.h>
#include <SvinSlider.h>

class MeshStack : public Svin::Module
{
public:
   struct Panel;

public:
   MeshStack();

public:
   void process(const ProcessArgs& args) override;
   void updateDisplays() override;

private:
   inline void setup();

private:
   Svin::Knob knob;
   Svin::Slider::List colorSliders;
   Svin::LED colorLED;
};

// widget

class MeshStackWidget : public Svin::ModuleWidget
{
public:
   MeshStackWidget(MeshStack* module);

private:
   inline void setup();
};

#ifndef MeshStackHPP
#include "MeshStack.hpp"
#endif // NOT MeshStackHPP

#endif // NOT MeshStackH
