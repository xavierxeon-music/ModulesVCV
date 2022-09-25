#ifndef NosferatuVampyreH
#define NosferatuVampyreH

#include <rack.hpp>
using namespace rack;

#include <SvinMasterClock.h>
#include <SvinMessageSubscriber.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <Music/Note.h>
#include <Tools/FastRandom.h>

#include <SvinButton.h>
#include <SvinButtonLED.h>
#include <SvinDisplayLCD.h>
#include <SvinInput.h>
#include <SvinKnob.h>
#include <SvinLED.h>
#include <SvinOutput.h>
#include <SvinSlider.h>
#include <SvinSwitch.h>

namespace Nosferatu
{
   struct Segment
   {
      uint8_t pitch = 0;  // 0 - 24 (2 octaves)
      uint8_t ticks = 2;  // 1 - 16
      float length = 0.5; // 0.0 - 1.0
      float chance = 1.0; // 0.0 - 1.0
      bool play = true;
   };

   struct Bank
   {
      Segment segments[8];
      uint8_t maxActive = 8; // 1 - 16
      uint8_t offset = 0;    // 0-11
   };

   struct Bus
   {
      uint8_t bankIndex = 0;
      uint16_t currentSegmentIndex = 0;
      uint8_t offset = 0;
   };

   //

   class Vampyre : public Svin::Module, public Svin::MasterClock::Client
   {
   public:
      struct Panel;

   public:
      Vampyre();

   public:
      void process(const ProcessArgs& args) override;
      void updateDisplays() override;

   private:

      enum class DisplayType : uint8_t
      {
         Bank,
         Pitch,
         Ticks,
         Offset,
      };


   private:
      inline void setup();
      const Bank& updateBank();
      void bankChange();
      void setDisplay(const DisplayType newType, const uint8_t value);
      void updateSegment();

      void load(const Svin::Json::Object& rootObject) override;
      void save(Svin::Json::Object& rootObject) override;

   private:
      // operation
      Bank banks[16];
      uint8_t bankIndex;
      uint16_t currentSegmentIndex;
      uint8_t tickCounter;
      FastRandom noiseGenerator;
      // display
      DisplayType displayType;
      uint8_t displayValue;
      dsp::PulseGenerator displayOverride;
      // segments
      Svin::LED::List currentLightList;
      Svin::Slider::List pitchSliderList;
      Svin::Slider::List tickSliderList;
      Svin::Knob::List lengthKnobList;
      Svin::Knob::List chanceKnobList;
      Svin::ButtonLED::List activeButtonList;
      // bank
      Svin::Input bankInput;
      Svin::Button bankDownButton;
      Svin::Button bankUpButton;
      // info
      Svin::DisplayLCD::Controller displayController;
      Svin::Knob offsetKnob;
      // outputs
      Svin::Output firstOutput;
      Svin::Output pitchOutput;
      Svin::Output gateOutput;
   };

   // widget

   class VampyreWidget : public Svin::ModuleWidget
   {
   public:
      VampyreWidget(Vampyre* module);

   private:
      inline void setup();
   };

} // namespace Nosferatu

#ifndef NosferatuVampyreHPP
#include "NosferatuVampyre.hpp"
#endif // NOT NosferatuVampyreHPP

#endif // NOT NosferatuVampyreH
