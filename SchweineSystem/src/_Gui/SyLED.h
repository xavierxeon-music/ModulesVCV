#ifndef SyLEDH
#define SyLEDH

#include <rack.hpp>

#include "SyCommon.h"

namespace Sy
{
   class Module;

   // wrapper for RGBLight
   class LED
   {
   public:
      class List;

   public:
      LED(Module* module, const uint16_t& rgbIndex = 0);

   public:
      void setColor(const Color& color);
      void setDefaultColor(const Color& color);
      void setOn(); // set to default color
      void setOff();
      void setActive(bool on);

   protected:
      Module* module;

   private:
      uint16_t redIndex;
      uint16_t greenIndex;
      uint16_t blueIndex;
      Color defaultColor;
   };

   class LED::List
   {
   public:
      List(Module* module);

   public:
      void append(const std::vector<uint16_t>& rgbIndexList);
      LED* operator[](const uint16_t& index);

   private:
      Module* module;
      std::vector<LED> instanceList;
   };
} // namespace Sy

inline void makeLED(rack::ModuleWidget* widget, rack::math::Vec pos, int rgbIndex)
{
   rack::Widget* childWidget = rack::createLightCentered<rack::MediumLight<rack::RedGreenBlueLight>>(pos, widget->getModule(), rgbIndex);
   widget->addChild(childWidget);
}

#endif // NOT SyLEDH
