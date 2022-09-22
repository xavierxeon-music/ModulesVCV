#ifndef BitBusBitInH
#define BitBusBitInH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SvinCommon.h>
#include <SvinInput.h>
#include <SvinLED.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

namespace BitBus
{
   class BitIn : public Svin::Module
   {
   public:
      struct Panel;

   public:
      BitIn();
      ~BitIn();

   public:
      void process(const ProcessArgs& args) override;

   private:
      inline void setup();

   private:
      Svin::Input::List inputList;

      Svin::LED busInIndicator;
      Svin::LED busOutIndicator;
   };

   class BitInWidget : public Svin::ModuleWidget
   {
   public:
      BitInWidget(BitIn* module);

   private:
      inline void setup();
   };
} // namespace BitBus

#ifndef BitBusBitInHPP
#include "BitBusBitIn.hpp"
#endif // NOT BitBusBitInHPP

#endif // BitBusBitInH
