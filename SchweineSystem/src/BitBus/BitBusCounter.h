#ifndef BitBusCounterH
#define BitBusCounterH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinDisplayLCD.h>
#include <SvinInput.h>
#include <SvinLED.h>
#include <SvinOutput.h>
#include <SvinSlider.h>

namespace BitBus
{
   class Counter : public Svin::Module
   {
   public:
      struct Panel;

   public:
      Counter();

   public:
      void process(const ProcessArgs& args) override;

   private:
      inline void setup();

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

   class CounterWidget : public Svin::ModuleWidget
   {
   public:
      CounterWidget(Counter* module);

   private:
      inline void setup();
   };
} // namespace BitBus

#ifndef BitBusCounterHPP
#include "BitBusCounter.hpp"
#endif // NOT BitBusCounterHPP

#endif // NOT BitBusCounterH
