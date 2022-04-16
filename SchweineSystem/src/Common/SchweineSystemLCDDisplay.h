#ifndef SchweineSystemLCDDisplayH
#define SchweineSystemLCDDisplayH

#include <rack.hpp>

#include "SchweineSystemCommon.h"

namespace SchweineSystem
{
   class LCDDisplay : public rack::TransparentWidget
   {
   public:
      LCDDisplay();

   public:
      void setup(uint16_t* value, const uint8_t& numberOfDigits);
      void setPosition(uint16_t x, uint16_t y);
      void setDigitColor(const Color& color);

   private:
      void drawLayer(const DrawArgs& args, int layer) override;

   private:
      std::shared_ptr<rack::Font> font;
      std::string fontPath;

      NVGcolor digitColor;
      uint8_t numberOfDigits;
      uint16_t* value;
   };
} // namespace SchweineSystem

#endif // NOT SchweineSystemLCDDisplayH
