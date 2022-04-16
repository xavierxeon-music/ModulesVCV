#ifndef SchweineSystemLightH
#define SchweineSystemLightH

#include <rack.hpp>

#include "SchweineSystemCommon.h"

namespace SchweineSystem
{
   // wrapper for RGBLight
   class Light
   {
   public:
      class List;

   public:
      Light(std::vector<rack::engine::Light>& fullList);

   public:
      void assign(const uint16_t& redIndex);
      void setDefaultColor(const Color& color);

      void setColor(const Color& color);
      void setOn(); // set to default color
      void setOff();

   private:
      std::vector<rack::engine::Light>& fullList;
      uint16_t redIndex;
      uint16_t greenIndex;
      uint16_t blueIndex;
      Color defaultColor;
   };

   class Light::List
   {
   public:
      List(std::vector<rack::engine::Light>& fullList);

   public:
      void append(std::vector<uint16_t> redIndexList);
      Light* operator[](const uint16_t& index);

   private:
      std::vector<rack::engine::Light>& fullList;
      std::vector<Light> instanceList;
   };
} // namespace SchweineSystem

#endif // NOT SchweineSystemLightH
