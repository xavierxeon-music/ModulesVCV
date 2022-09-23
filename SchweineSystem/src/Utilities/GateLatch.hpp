#ifndef GateLatchHPP
#define GateLatchHPP

#include "GateLatch.h"

#include <SvinOrigin.h>

struct GateLatch::Panel
{
   enum ParamId
   {
      // buttons
      Reset_Button = 0,
      // switches
      // ledbuttons
      // knobs
      // sliders
      PARAMS_LEN = 1
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
      Reset_Input = 0,
      Row8_In = 1,
      Row7_In = 2,
      Row6_In = 3,
      Row5_In = 4,
      Row4_In = 5,
      Row3_In = 6,
      Row2_In = 7,
      Row1_In = 8,
      INPUTS_LEN = 9
   };

   enum OutputId
   {
      Row8_Out = 0,
      Row7_Out = 1,
      Row6_Out = 2,
      Row5_Out = 3,
      Row4_Out = 4,
      Row3_Out = 5,
      Row2_Out = 6,
      Row1_Out = 7,
      OUTPUTS_LEN = 8
   };

   enum LightId
   {
      // leds
      RGB_Row8_Status = 0,
      RGB_Row7_Status = 3,
      RGB_Row6_Status = 6,
      RGB_Row5_Status = 9,
      RGB_Row4_Status = 12,
      RGB_Row3_Status = 15,
      RGB_Row2_Status = 18,
      RGB_Row1_Status = 21,
      // ledbuttons
      // sliders
      LIGHTS_LEN = 24
   };

};

void GateLatch::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Reset_Button, "Reset_Button");

   configInput(Panel::Reset_Input, "Reset_Input");
   configInput(Panel::Row8_In, "Row8_In");
   configInput(Panel::Row7_In, "Row7_In");
   configInput(Panel::Row6_In, "Row6_In");
   configInput(Panel::Row5_In, "Row5_In");
   configInput(Panel::Row4_In, "Row4_In");
   configInput(Panel::Row3_In, "Row3_In");
   configInput(Panel::Row2_In, "Row2_In");
   configInput(Panel::Row1_In, "Row1_In");

   configOutput(Panel::Row8_Out, "Row8_Out");
   configOutput(Panel::Row7_Out, "Row7_Out");
   configOutput(Panel::Row6_Out, "Row6_Out");
   configOutput(Panel::Row5_Out, "Row5_Out");
   configOutput(Panel::Row4_Out, "Row4_Out");
   configOutput(Panel::Row3_Out, "Row3_Out");
   configOutput(Panel::Row2_Out, "Row2_Out");
   configOutput(Panel::Row1_Out, "Row1_Out");
}

void GateLatchWidget::setup()
{
   makePanel("res/Utilities/GateLatch.svg");

   makeButton(this, Vec(65.84, 355.83), GateLatch::Panel::Reset_Button);

   makeInput(this, Vec(24.00, 355.83),  GateLatch::Panel::Reset_Input, false);
   makeInput(this, Vec(24.17, 311.85),  GateLatch::Panel::Row8_In, false);
   makeInput(this, Vec(24.17, 276.41),  GateLatch::Panel::Row7_In, false);
   makeInput(this, Vec(24.17, 240.98),  GateLatch::Panel::Row6_In, false);
   makeInput(this, Vec(24.17, 205.55),  GateLatch::Panel::Row5_In, false);
   makeInput(this, Vec(24.17, 170.11),  GateLatch::Panel::Row4_In, false);
   makeInput(this, Vec(24.17, 134.68),  GateLatch::Panel::Row3_In, false);
   makeInput(this, Vec(24.17, 99.24),  GateLatch::Panel::Row2_In, false);
   makeInput(this, Vec(24.17, 63.81),  GateLatch::Panel::Row1_In, false);

   makeOutput(this, Vec(65.83, 311.85), GateLatch::Panel::Row8_Out, false);
   makeOutput(this, Vec(65.83, 276.41), GateLatch::Panel::Row7_Out, false);
   makeOutput(this, Vec(65.83, 240.98), GateLatch::Panel::Row6_Out, false);
   makeOutput(this, Vec(65.83, 205.55), GateLatch::Panel::Row5_Out, false);
   makeOutput(this, Vec(65.83, 170.11), GateLatch::Panel::Row4_Out, false);
   makeOutput(this, Vec(65.83, 134.68), GateLatch::Panel::Row3_Out, false);
   makeOutput(this, Vec(65.83, 99.24), GateLatch::Panel::Row2_Out, false);
   makeOutput(this, Vec(65.83, 63.81), GateLatch::Panel::Row1_Out, false);

   makeLED(this, Vec(45.00, 311.85), GateLatch::Panel::RGB_Row8_Status);
   makeLED(this, Vec(45.00, 276.41), GateLatch::Panel::RGB_Row7_Status);
   makeLED(this, Vec(45.00, 240.98), GateLatch::Panel::RGB_Row6_Status);
   makeLED(this, Vec(45.00, 205.55), GateLatch::Panel::RGB_Row5_Status);
   makeLED(this, Vec(45.00, 170.11), GateLatch::Panel::RGB_Row4_Status);
   makeLED(this, Vec(45.00, 134.68), GateLatch::Panel::RGB_Row3_Status);
   makeLED(this, Vec(45.00, 99.24), GateLatch::Panel::RGB_Row2_Status);
   makeLED(this, Vec(45.00, 63.81), GateLatch::Panel::RGB_Row1_Status);
}

#endif // NOT GateLatchHPP
