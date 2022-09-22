#ifndef BitBusRandomWalkH
#define BitBusRandomWalkH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButton.h>
#include <SvinDisplayLCD.h>
#include <SvinInput.h>
#include <SvinLED.h>
#include <SvinSlider.h>

#include <Tools/Range.h>

namespace BitBus
{
   class RandomWalk : public Svin::Module
   {
   public:
      struct Panel;

   public:
      RandomWalk();

   public:
      void process(const ProcessArgs& args) override;

   private:
      static constexpr uint16_t seedCount = 256;

   private:
      inline void setup();

      void load(const Svin::Json::Object& rootObject) override;
      void save(Svin::Json::Object& rootObject) override;

   private:
      Svin::LED busInIndicator;
      Svin::LED busOutIndicator;

      Svin::Slider mixSlider;
      Svin::Button upButton;
      Svin::Button downButton;
      Svin::DisplayLCD::Controller displayController;
      Svin::Input scanInput;
      Range::Mapper scanMapper;

      float mix;
      uint8_t seed;
      uint8_t tables[seedCount][256]; // seed, index
   };

   // widget

   class RandomWalkWidget : public Svin::ModuleWidget
   {
   public:
      RandomWalkWidget(RandomWalk* module);

   private:
      inline void setup();
   };
} // namespace BitBus

#ifndef BitBusRandomWalkHPP
#include "BitBusRandomWalk.hpp"
#endif // NOT BitBusRandomWalkHPP

#endif // NOT BitBusRandomWalkH
