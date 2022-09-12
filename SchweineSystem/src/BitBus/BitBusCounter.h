#ifndef BitBusCounterH
#define BitBusCounterH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SvinExapnder.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinDisplayLCD.h>
#include <SvinInput.h>
#include <SvinLED.h>
#include <SvinOutput.h>
#include <SvinSlider.h>

class BitBusCounter : public Svin::Module, public Svin::Exapnder<BitBusMessage>
{
public:
   struct Panel;

public:
   BitBusCounter();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   Svin::Input upInput;
   Svin::Input downInput;
   Svin::Input resetInput;

   Svin::Slider thresholdSlider;

   uint8_t counter;
   Svin::DisplayLCD::Controller counterController;
   Svin::LED::List bitIndicatorList;

   Svin::LED busOutIndicator;
};

// widget

class BitBusCounterWidget : public Svin::ModuleWidget
{
public:
   BitBusCounterWidget(BitBusCounter* module);

private:
   void setup();
};

#endif // NOT BitBusCounterH
