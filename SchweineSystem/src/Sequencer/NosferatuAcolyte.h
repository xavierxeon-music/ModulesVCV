#ifndef NosferatuAcolyteH
#define NosferatuAcolyteH

#include <rack.hpp>
using namespace rack;

#include <SvinMessagePublisher.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButtonLED.h>
#include <SvinDisplayLCD.h>
#include <SvinKnob.h>
#include <SvinLED.h>
#include <SvinSlider.h>

#include "NosferatuVampyre.h"

namespace Nosferatu
{
   class Acolyte : public Svin::Module, public Svin::Message<Bank>::Publisher
   {
   public:
      struct Panel;

   public:
      Acolyte();

   public:
      void process(const ProcessArgs& args) override;
      void updateDisplays() override;

   private:
      inline void setup();
      void bankChange();

      void load(const Svin::Json::Object& rootObject) override;
      void save(Svin::Json::Object& rootObject) override;

   private:
      // operation
      Bank banks[16];
      uint8_t bankIndex;
      int16_t currentSegmentIndex;
      // display
      Svin::DisplayLCD::Controller display;
      // segments
      Svin::LED::List currentLightList;
      Svin::Slider::List pitchSliderList;
      Svin::Slider::List tickSliderList;
      Svin::Knob::List lengthKnobList;
      Svin::Knob::List chanceKnobList;
      Svin::ButtonLED::List activeButtonList;
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
