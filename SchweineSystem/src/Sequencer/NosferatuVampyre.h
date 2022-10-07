#ifndef NosferatuVampyreH
#define NosferatuVampyreH

#include <rack.hpp>
using namespace rack;

#include <SvinMasterClock.h>
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
   };

   struct Bank
   {
      Segment segments[8];
      uint8_t pitchOffset = 0; // 0 - 11, not used by expander

      using List = std::vector<Bank>;
   };

   struct State // to be pushed to expanders
   {
      uint8_t bankIndex = 0;            // the current bank index 0 - 15
      uint8_t maxActive = 8;            // 8 for base + 8 for each expander
      uint16_t currentSegmentIndex = 0; // including expander
      bool playCurrentSegment = true;   // if chances allows it
      uint8_t pitchOffset = 0;          // copied from from base bank
      bool needsExpanderBanks = false;  // expander should send current bank
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

      using ActiveMap = std::map<uint8_t, uint8_t>; // bankCount vs maxActive

   private:
      inline void setup();
      const Bank& updateCurrentBank();
      void bankChange();
      void setDisplay(const DisplayType newType, const uint8_t value);
      void updateCurrentSegmentPlayChances();

      void load(const Svin::Json::Object& rootObject) override;
      void save(Svin::Json::Object& rootObject) override;

   private:
      // operation
      Bank banks[16];
      State state;
      Bank::List playBanks; // the banks currently available (including exapnders)
      uint8_t bankCount;
      ActiveMap activeMap;
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
