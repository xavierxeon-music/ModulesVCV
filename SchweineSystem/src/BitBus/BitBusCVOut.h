#ifndef BitBusCVOutH
#define BitBusCVOutH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SvinCommon.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <Tools/Range.h>

#include <SvinCommon.h>
#include <SvinLED.h>
#include <SvinOutput.h>

namespace BitBus
{
   class CVOut : public Svin::Module
   {
   public:
      struct Panel;

   public:
      CVOut();
      ~CVOut();

   public:
      void process(const ProcessArgs& args) override;

   private:
      inline void setup();

   private:
      Svin::Output cvOutput;
      Range::Mapper outputMapper;

      Svin::LED busInIndicator;
   };

   class CVOutWidget : public Svin::ModuleWidget
   {
   public:
      CVOutWidget(CVOut* module);

   private:
      inline void setup();
   };
} // namespace BitBus

#ifndef BitBusCVOutHPP
#include "BitBusCVOut.hpp"
#endif // NOT BitBusCVOutHPP

#endif // BitBusCVOutH
