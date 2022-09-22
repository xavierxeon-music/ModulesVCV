#ifndef BitBusMeterAndFreezeH
#define BitBusMeterAndFreezeH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <Tools/BoolField.h>
#include <Tools/RingBuffer.h>

#include <SvinButtonLED.h>
#include <SvinCommon.h>
#include <SvinInput.h>
#include <SvinLED.h>

namespace BitBus
{
   static constexpr uint16_t AverageBufferSize = 4800;

   class MeterAndFreeze : public Svin::Module
   {
   public:
      struct Panel;

   public:
      MeterAndFreeze();
      ~MeterAndFreeze();

   public:
      void process(const ProcessArgs& args) override;

   private:
      inline void setup();

      void load(const Svin::Json::Object& rootObject) override;
      void save(Svin::Json::Object& rootObject) override;

   private:
      Svin::LED::List lightList;

      Svin::ButtonLED freezeButton;
      Svin::Input freezeInput;
      BoolField8 freezeBuffer[16];

      Svin::ButtonLED sampleButton;
      Svin::Input sampleInput;

      Svin::LED busInIndicator;
      Svin::LED busOutIndicator;
   };

   class MeterAndFreezeWidget : public Svin::ModuleWidget
   {
   public:
      MeterAndFreezeWidget(MeterAndFreeze* module);

   private:
      inline void setup();
   };
} // namespace BitBus

#ifndef BitBusMeterAndFreezeHPP
#include "BitBusMeterAndFreeze.hpp"
#endif // NOT BitBusMeterAndFreezeHPP

#endif // NOT BitBusMeterAndFreezeH
