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
      void append(const std::vector<uint16_t>& redIndexList);
      Light* operator[](const uint16_t& index);

   private:
      std::vector<rack::engine::Light>& fullList;
      std::vector<Light> instanceList;
   };
} // namespace SchweineSystem

inline void makeLight(rack::ModuleWidget* widget, rack::math::Vec pos, int firstLightId)
{
   rack::Widget* childWidget = rack::createLightCentered<rack::MediumLight<rack::RedGreenBlueLight>>(pos, widget->getModule(), firstLightId);
   widget->addChild(childWidget);
}

#endif // NOT SchweineSystemLightH
