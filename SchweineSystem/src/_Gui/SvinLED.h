#ifndef SvinLEDH
#define SvinLEDH

#include <rack.hpp>

#include <Tools/Colour.h>

namespace Svin
{
   class Module;

   // wrapper for RGBLight
   class LED
   {
   public:
      class List;

   public:
      LED(Module* module, const uint16_t& rgbIndex);

   public:
      // set color directly
      void setColor(const Colour& color);
      // use default color
      void setDefaultColor(const Colour& color);
      void setOn();
      void setOff();
      void setActive(bool on);
      void setBrightness(const float newBrightness);

   protected:
      Module* module;

   private:
      const uint16_t rgbIndex;
      Colour defaultColor;
      float brightness;
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
} // namespace Svin

inline void makeLED(rack::ModuleWidget* widget, rack::math::Vec pos, int rgbIndex)
{
   rack::Widget* childWidget = rack::createLightCentered<rack::MediumLight<rack::RedGreenBlueLight>>(pos, widget->getModule(), rgbIndex);
   widget->addChild(childWidget);
}

#endif // NOT SvinLEDH
