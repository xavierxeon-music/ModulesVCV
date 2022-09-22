#ifndef NosferatuAcolyteH
#define NosferatuAcolyteH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButtonLED.h>
#include <SvinDisplayLCD.h>
#include <SvinKnob.h>
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

   private:
      Svin::DisplayLCD::Controller display;
   };

   // widget

   class AcolyteWidget : public Svin::ModuleWidget
   {
   public:
      AcolyteWidget(Acolyte* module);

   private:
      inline void setup();
   };
} // namespace Nosferatu

#ifndef NosferatuAcolyteHPP
#include "NosferatuAcolyte.hpp"
#endif // NOT NosferatuAcolyteHPP

#endif // NOT NosferatuAcolyteH
