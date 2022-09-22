#ifndef BitBusCVInH
#define BitBusCVInH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <Tools/Range.h>

#include <SvinCommon.h>
#include <SvinInput.h>
#include <SvinLED.h>

namespace BitBus
{
   class CVIn : public Svin::Module
   {
   public:
      struct Panel;

   public:
      CVIn();
      ~CVIn();

   public:
      void process(const ProcessArgs& args) override;

   private:
      inline void setup();

   private:
      Svin::Input cvInput;
      Range::Mapper inputMapper;

      Svin::LED busOutIndicator;
   };

   // widget

   class CVInWidget : public Svin::ModuleWidget
   {
   public:
      CVInWidget(CVIn* module);

   private:
      inline void setup();
   };
} // namespace BitBus

#ifndef BitBusCVInHPP
#include "BitBusCVIn.hpp"
#endif // NOT BitBusCVInHPP

#endif // BitBusCVInH
