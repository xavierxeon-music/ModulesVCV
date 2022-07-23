#ifndef SchweineSystemSwitchH
#define SchweineSystemSwitchH

#include "SchweineSystemCommon.h"

namespace SchweineSystem
{
   class Switch
   {
   public:
      using List = ElementList<Switch>;

   public:
      Switch(Module* module, const uint16_t& paramIndex = 0);

   public:
      void assign(const uint16_t& paramIndex);
      void setState(bool on);
      bool isOn();

   private:
      Module* module;
      uint16_t paramIndex;
   };
} // namespace SchweineSystem

#endif // NOT SchweineSystemSwitchH
