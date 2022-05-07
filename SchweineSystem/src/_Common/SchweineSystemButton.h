#ifndef SchweineSystemButtonH
#define SchweineSystemButtonH

#include <rack.hpp>

#include "SchweineSystemCommon.h"

namespace SchweineSystem
{
   class Button
   {
   public:
      using List = ElementList<Button>;

   public:
      Button(Module* module, const uint16_t& paramIndex = 0);

   public:
      void assign(const uint16_t& paramIndex);

      bool isTriggered();

   private:
      Module* module;
      uint16_t paramIndex;
      rack::dsp::BooleanTrigger trigger;
   };
} // namespace SchweineSystem

#endif // NOT SchweineSystemButtonH
