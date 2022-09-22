#ifndef NosferatuAcolyteH
#define NosferatuAcolyteH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinKnob.h>
#include <SvinDisplayLCD.h>
#include <SvinButtonLED.h>
#include <SvinLED.h>
#include <SvinSlider.h>

namespace Nosferatu
{
   class Acolyte : public Svin::Module
   {
   public:
      struct Panel;

   public:
      Acolyte();
   
   public:
      void process(const ProcessArgs& args) override;

   private:
      inline void setup();
   };

   // widget

   class AcolyteWidget : public Svin::ModuleWidget
   {
   public:
      AcolyteWidget(Acolyte* module);

   private:
      inline void setup();
   };
}

#ifndef NosferatuAcolyteHPP
#include "NosferatuAcolyte.hpp"
#endif // NOT NosferatuAcolyteHPP

#endif // NOT NosferatuAcolyteH
