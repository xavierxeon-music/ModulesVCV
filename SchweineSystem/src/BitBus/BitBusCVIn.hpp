#ifndef BitBusCVInHPP
#define BitBusCVInHPP

#include "BitBusCVIn.h"

#include <SvinOrigin.h>

namespace BitBus
{
   struct CVIn::Panel
   {
      enum ParamId
      {
         // buttons
         // switches
         // ledbuttons
         // knobs
         // sliders
         PARAMS_LEN = 0
      };

      enum DisplayId
      {
         // lcd
         // oled
         DISPLAYS_LEN = 0
      };

      enum MeterId
      {
         METERS_LEN = 0
      };

      enum InputId
      {
         CVIn = 0,
         INPUTS_LEN = 1
      };

      enum OutputId
      {
         OUTPUTS_LEN = 0
      };

      enum LightId
      {
         // leds
         RGB_BusOut = 0,
         // ledbuttons
         // sliders
         LIGHTS_LEN = 3
      };

   };

   void CVIn::setup()
   {
      config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

      configInput(Panel::CVIn, "CVIn");
   }

   void CVInWidget::setup()
   {
      makePanel("res/BitBus/BitBusCVIn.svg");

      makeInput(this, Vec(24.17, 215.77),  CVIn::Panel::CVIn, true);

      makeLED(this, Vec(49.50, 46.77), CVIn::Panel::RGB_BusOut);
   }
}

#endif // NOT BitBusCVInHPP
