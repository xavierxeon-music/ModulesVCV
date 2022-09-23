#ifndef MapperHPP
#define MapperHPP

#include "Mapper.h"

#include <SvinOrigin.h>

struct Mapper::Panel
{
   enum ParamId
   {
      // buttons
      Output_Max = 0,
      Input_Max = 1,
      // switches
      Output_Range = 2,
      Input_Range = 3,
      // ledbuttons
      // knobs
      // sliders
      PARAMS_LEN = 4
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
      Input_In = 0,
      INPUTS_LEN = 1
   };

   enum OutputId
   {
      Output_Out = 0,
      OUTPUTS_LEN = 1
   };

   enum LightId
   {
      // leds
      RGB_Output_10V = 0,
      RGB_Output_8V = 3,
      RGB_Output_5V = 6,
      RGB_Input_10V = 9,
      RGB_Input_8V = 12,
      RGB_Input_5V = 15,
      // ledbuttons
      // sliders
      LIGHTS_LEN = 18
   };

};

void Mapper::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Output_Max, "Output_Max");
   configButton(Panel::Input_Max, "Input_Max");

   configSwitch(Panel::Output_Range, 0.0f, 1.0f, 0.0f, "Output_Range");
   configSwitch(Panel::Input_Range, 0.0f, 1.0f, 0.0f, "Input_Range");

   configInput(Panel::Input_In, "Input_In");

   configOutput(Panel::Output_Out, "Output_Out");
}

void MapperWidget::setup()
{
   makePanel("res/Utilities/Mapper.svg");

   makeButton(this, Vec(30.00, 228.71), Mapper::Panel::Output_Max);
   makeButton(this, Vec(30.00, 73.62), Mapper::Panel::Input_Max);

   makeSwitch(this, Vec(30.00, 295.52), Mapper::Panel::Output_Range, false);
   makeSwitch(this, Vec(30.00, 140.43), Mapper::Panel::Input_Range, false);

   makeInput(this, Vec(30.00, 175.83),  Mapper::Panel::Input_In, true);

   makeOutput(this, Vec(30.00, 330.92), Mapper::Panel::Output_Out, true);

   makeLED(this, Vec(30.00, 271.23), Mapper::Panel::RGB_Output_10V);
   makeLED(this, Vec(30.00, 257.73), Mapper::Panel::RGB_Output_8V);
   makeLED(this, Vec(30.00, 244.23), Mapper::Panel::RGB_Output_5V);
   makeLED(this, Vec(30.00, 116.14), Mapper::Panel::RGB_Input_10V);
   makeLED(this, Vec(30.00, 102.64), Mapper::Panel::RGB_Input_8V);
   makeLED(this, Vec(30.00, 89.14), Mapper::Panel::RGB_Input_5V);
}

#endif // NOT MapperHPP
