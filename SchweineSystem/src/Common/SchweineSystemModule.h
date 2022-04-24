#ifndef SchweineSystemModuleH
#define SchweineSystemModuleH

#include <rack.hpp>

namespace SchweineSystem
{
   class Module : public rack::Module
   {
   public:
      using TextMap = std::map<uint16_t, std::string>;
      using ValueMap = std::map<uint16_t, float>;

   public:
      Module();

   public:
      TextMap texts;
      ValueMap values;

   protected:
      void configDisplay(const uint16_t& textId, std::string name = "");
      void configMeter(const uint16_t& valueId, std::string name = "");
   };
} // namespace SchweineSystem

#endif // NOT SchweineSystemModuleH
