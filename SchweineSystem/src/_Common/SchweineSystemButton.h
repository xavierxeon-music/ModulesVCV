#ifndef SchweineSystemButtonH
#define SchweineSystemButtonH

#include <rack.hpp>

#include "SchweineSystemCommon.h"

namespace SchweineSystem
{
   class Module;

   class Button
   {
   public:
      class List;

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

   class Button::List
   {
   public:
      List(Module* module);

   public:
      void append(const std::vector<uint16_t>& paramIndexList);
      Button* operator[](const uint16_t& index);

   private:
      Module* module;
      std::vector<Button> instanceList;
   };

} // namespace SchweineSystem

#endif // NOT SchweineSystemButtonH
