#ifndef BitBusCVOutHPP
#define BitBusCVOutHPP

#include "BitBusCVOut.h"

#include <SvinOrigin.h>

namespace BitBus
{
   struct CVOut::Panel
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
         INPUTS_LEN = 0
      };

      enum OutputId
      {
         CVOut = 0,
         OUTPUTS_LEN = 1
      };

      enum LightId
      {
         // leds
         RGB_BusIn = 0,
         // ledbuttons
         // sliders
         LIGHTS_LEN = 3
      };

   };

   void CVOut::setup()
   {
      config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

      configOutput(Panel::CVOut, "CVOut");
   }

   void CVOutWidget::setup()
   {
      makePanel("res/BitBus/BitBusCVOut.svg");

      makeOutput(this, Vec(35.83, 215.77), CVOut::Panel::CVOut, true);

      makeLED(this, Vec(9.50, 46.77), CVOut::Panel::RGB_BusIn);
   }
}

#endif // NOT BitBusCVOutHPP
