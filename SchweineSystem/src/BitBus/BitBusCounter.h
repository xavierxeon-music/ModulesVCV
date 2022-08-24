#ifndef BitBusCounterH
#define BitBusCounterH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SyExapnder.h>
#include <SyModule.h>
#include <SyModuleWidget.h>

#include <SyDisplayLCD.h>
#include <SyInput.h>
#include <SyLED.h>
#include <SyOutput.h>

class BitBusCounter : public Sy::Module, public Sy::Exapnder<BitBusMessage>
{
public:
   struct Panel;

public:
   BitBusCounter();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();

   void load(const Sy::Json::Object& rootObject) override;
   void save(Sy::Json::Object& rootObject) override;

private:
   dsp::BooleanTrigger upTrigger;
   dsp::BooleanTrigger downTrigger;

   uint8_t counter;
   Sy::DisplayLCD::Controller counterController;
   Sy::LED ::List bitIndicatorList;

   Sy::LED busOutIndicator;
};

// widget

class BitBusCounterWidget : public Sy::ModuleWidget
{
public:
   BitBusCounterWidget(BitBusCounter* module);

private:
   void setup();
};

#endif // NOT BitBusCounterH
