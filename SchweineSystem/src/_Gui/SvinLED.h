#ifndef SvinLEDH
#define SvinLEDH

#include <rack.hpp>

#include <SvinCommon.h>

namespace Svin
{
   class Module;

   // wrapper for RGBLight
   class LED
   {
   public:
      using List = ElementList<LED>;

   public:
      LED(Module* module, const uint16_t& rgbIndex);

   public:
      // set color directly
      void setColor(const Color& color);
      // use default color
      void setDefaultColor(const Color& color);
      void setOn();
      void setOff();
      void setActive(bool on);
      void setBrightness(const float newBrightness);

   protected:
      Module* module;

   private:
      const uint16_t rgbIndex;
      Color defaultColor;
      float brightness;
   };

} // namespace Svin

inline void makeLED(rack::ModuleWidget* widget, rack::math::Vec pos, int rgbIndex)
{
   rack::Widget* childWidget = rack::createLightCentered<rack::MediumLight<rack::RedGreenBlueLight>>(pos, widget->getModule(), rgbIndex);
   widget->addChild(childWidget);
}

#endif // NOT SvinLEDH
