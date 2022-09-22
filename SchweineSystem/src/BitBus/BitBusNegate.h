#ifndef BitBusNegateH
#define BitBusNegateH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SvinButtonLED.h>
#include <SvinCommon.h>
#include <SvinInput.h>
#include <SvinLED.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

namespace BitBus
{
   class Negate : public Svin::Module
   {
   public:
      struct Panel;

   public:
      Negate();
      ~Negate();

   public:
      void process(const ProcessArgs& args) override;

   private:
      inline void setup();

      void load(const Svin::Json::Object& rootObject) override;
      void save(Svin::Json::Object& rootObject) override;

   private:
      Svin::ButtonLED::List latchList;
      Svin::Input::List gateList;

      Svin::LED busInIndicator;
      Svin::LED busOutIndicator;
   };

   // widget

   class NegateWidget : public Svin::ModuleWidget
   {
   public:
      NegateWidget(Negate* module);

   private:
      inline void setup();
   };
} // namespace BitBus

#ifndef BitBusNegateHPP
#include "BitBusNegate.hpp"
#endif // NOT BitBusNegateHPP

#endif // NOT BitBusNegateH
