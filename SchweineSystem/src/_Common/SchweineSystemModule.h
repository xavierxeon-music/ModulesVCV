#ifndef SchweineSystemModuleH
#define SchweineSystemModuleH

#include <rack.hpp>

#include <SchweineSystemCommon.h>

namespace SchweineSystem
{
   class Module : public rack::Module
   {
   public:
      using TextMap = std::map<uint16_t, std::string>;
      using ValueMap = std::map<uint16_t, float>;
      using PixelMap = std::map<uint16_t, Color*>;

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
      void configPixels(const uint16_t& valueId, const uint8_t& width, const uint8_t& height, std::string name = "");
   };
} // namespace SchweineSystem

#endif // NOT SchweineSystemModuleH
