#ifndef MultifilterH
#define MultifilterH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinKnob.h>
#include <SvinButtonLED.h>
#include <SvinSlider.h>
#include <SvinInput.h>
#include <SvinOutput.h>

class Multifilter : public Svin::Module
{
public:
   struct Panel;

public:
   Multifilter();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
};

// widget

class MultifilterWidget : public Svin::ModuleWidget
{
public:
   MultifilterWidget(Multifilter* module);

private:
   void setup();
};

#endif // NOT MultifilterH
