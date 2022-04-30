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
      using PixelMap = std::map<uint16_t, uint8_t*>;

   public:
      Module();

   public:
      virtual void updateDisplays();

   public:
      TextMap texts;
      ValueMap values;
      PixelMap pixels;

   protected:
      void configDisplay(const uint16_t& textId, std::string name = "");
      void configMeter(const uint16_t& valueId, std::string name = "");
      void configPixels(const uint16_t& valueId, std::string name = "", const uint16_t& size = 128 * 64);
   };
} // namespace SchweineSystem

#endif // NOT SchweineSystemModuleH
