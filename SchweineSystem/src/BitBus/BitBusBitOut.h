#ifndef BitBusBitOutH
#define BitBusBitOutH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SvinCommon.h>
#include <SvinLED.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>
#include <SvinOutput.h>

namespace BitBus
{
   class BitOut : public Svin::Module
   {
   public:
      struct Panel;

   public:
      BitOut();
      ~BitOut();

   public:
      void process(const ProcessArgs& args) override;

   private:
      inline void setup();

   private:
      Svin::Output::List outputList;

      Svin::LED busInIndicator;
      Svin::LED busOutIndicator;
   };

   // widget

   class BitOutWidget : public Svin::ModuleWidget
   {
   public:
      BitOutWidget(BitOut* module);

   private:
      inline void setup();
   };
} // namespace BitBus

#ifndef BitBusBitOutHPP
#include "BitBusBitOut.hpp"
#endif // NOT BitBusBitOutHPP

#endif // BitBusBitOutH
