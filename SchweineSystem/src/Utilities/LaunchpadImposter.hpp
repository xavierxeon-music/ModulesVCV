#ifndef LaunchpadImposterHPP
#define LaunchpadImposterHPP

#include "LaunchpadImposter.h"

#include <SvinOrigin.h>

struct LaunchpadImposter::Panel
{
   enum ParamId
   {
      // buttons
      DeviceIdDown = 0,
      DeviceIdUp = 1,
      // switches
      // ledbuttons
      // knobs
      // sliders
      PARAMS_LEN = 2
   };

   enum DisplayId
   {
      // lcd
      Text_DeviceId = 0,
      // oled
      Pixels_RowOne_ColNine = 1,
      Pixels_RowOne_ColEight = 2,
      Pixels_RowOne_ColSeven = 3,
      Pixels_RowOne_ColSix = 4,
      Pixels_RowOne_ColFive = 5,
      Pixels_RowOne_ColFour = 6,
      Pixels_RowOne_ColThree = 7,
      Pixels_RowOne_ColTwo = 8,
      Pixels_RowOne_ColOne = 9,
      Pixels_RowTwo_ColNine = 10,
      Pixels_RowTwo_ColEight = 11,
      Pixels_RowTwo_ColSeven = 12,
      Pixels_RowTwo_ColSix = 13,
      Pixels_RowTwo_ColFive = 14,
      Pixels_RowTwo_ColFour = 15,
      Pixels_RowTwo_ColThree = 16,
      Pixels_RowTwo_ColTwo = 17,
      Pixels_RowTwo_ColOne = 18,
      Pixels_RowThree_ColNine = 19,
      Pixels_RowThree_ColEight = 20,
      Pixels_RowThree_ColSeven = 21,
      Pixels_RowThree_ColSix = 22,
      Pixels_RowThree_ColFive = 23,
      Pixels_RowThree_ColFour = 24,
      Pixels_RowThree_ColThree = 25,
      Pixels_RowThree_ColTwo = 26,
      Pixels_RowThree_ColOne = 27,
      Pixels_RowFour_ColNine = 28,
      Pixels_RowFour_ColEight = 29,
      Pixels_RowFour_ColSeven = 30,
      Pixels_RowFour_ColSix = 31,
      Pixels_RowFour_ColFive = 32,
      Pixels_RowFour_ColFour = 33,
      Pixels_RowFour_ColThree = 34,
      Pixels_RowFour_ColTwo = 35,
      Pixels_RowFour_ColOne = 36,
      Pixels_RowFive_ColNine = 37,
      Pixels_RowFive_ColEight = 38,
      Pixels_RowFive_ColSeven = 39,
      Pixels_RowFive_ColSix = 40,
      Pixels_RowFive_ColFive = 41,
      Pixels_RowFive_ColFour = 42,
      Pixels_RowFive_ColThree = 43,
      Pixels_RowFive_ColTwo = 44,
      Pixels_RowFive_ColOne = 45,
      Pixels_RowSix_ColNine = 46,
      Pixels_RowSix_ColEight = 47,
      Pixels_RowSix_ColSeven = 48,
      Pixels_RowSix_ColSix = 49,
      Pixels_RowSix_ColFive = 50,
      Pixels_RowSix_ColFour = 51,
      Pixels_RowSix_ColThree = 52,
      Pixels_RowSix_ColTwo = 53,
      Pixels_RowSix_ColOne = 54,
      Pixels_RowSeven_ColNine = 55,
      Pixels_RowSeven_ColEight = 56,
      Pixels_RowSeven_ColSeven = 57,
      Pixels_RowSeven_ColSix = 58,
      Pixels_RowSeven_ColFive = 59,
      Pixels_RowSeven_ColFour = 60,
      Pixels_RowSeven_ColThree = 61,
      Pixels_RowSeven_ColTwo = 62,
      Pixels_RowSeven_ColOne = 63,
      Pixels_RowEight_ColNine = 64,
      Pixels_RowEight_ColEight = 65,
      Pixels_RowEight_ColSeven = 66,
      Pixels_RowEight_ColSix = 67,
      Pixels_RowEight_ColFive = 68,
      Pixels_RowEight_ColFour = 69,
      Pixels_RowEight_ColThree = 70,
      Pixels_RowEight_ColTwo = 71,
      Pixels_RowEight_ColOne = 72,
      Pixels_RowNine_ColEight = 73,
      Pixels_RowNine_ColSeven = 74,
      Pixels_RowNine_ColSix = 75,
      Pixels_RowNine_ColFive = 76,
      Pixels_RowNine_ColFour = 77,
      Pixels_RowNine_ColThree = 78,
      Pixels_RowNine_ColTwo = 79,
      Pixels_RowNine_ColOne = 80,
      DISPLAYS_LEN = 81
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
      OUTPUTS_LEN = 0
   };

   enum LightId
   {
      // leds
      RGB_Logo = 0,
      // ledbuttons
      // sliders
      LIGHTS_LEN = 3
   };

};

void LaunchpadImposter::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::DeviceIdDown, "DeviceIdDown");
   configButton(Panel::DeviceIdUp, "DeviceIdUp");
}

void LaunchpadImposterWidget::setup()
{
   makePanel("res/Utilities/LaunchpadImposter.svg");

   makeButton(this, Vec(160.91, 78.24), LaunchpadImposter::Panel::DeviceIdDown);
   makeButton(this, Vec(160.91, 59.60), LaunchpadImposter::Panel::DeviceIdUp);

   makeLED(this, Vec(234.00, 127.93), LaunchpadImposter::Panel::RGB_Logo);

   makeLCD(this, Vec(113.89, 56.92), 2, LaunchpadImposter::Panel::Text_DeviceId, 18);

   makeOLED(this, Vec(222.90, 329.83), LaunchpadImposter::Panel::Pixels_RowOne_ColNine, 20, 20);
   makeOLED(this, Vec(191.00, 329.83), LaunchpadImposter::Panel::Pixels_RowOne_ColEight, 20, 20);
   makeOLED(this, Vec(165.14, 329.83), LaunchpadImposter::Panel::Pixels_RowOne_ColSeven, 20, 20);
   makeOLED(this, Vec(139.29, 329.83), LaunchpadImposter::Panel::Pixels_RowOne_ColSix, 20, 20);
   makeOLED(this, Vec(113.43, 329.83), LaunchpadImposter::Panel::Pixels_RowOne_ColFive, 20, 20);
   makeOLED(this, Vec(87.57, 329.83), LaunchpadImposter::Panel::Pixels_RowOne_ColFour, 20, 20);
   makeOLED(this, Vec(61.71, 329.83), LaunchpadImposter::Panel::Pixels_RowOne_ColThree, 20, 20);
   makeOLED(this, Vec(35.86, 329.83), LaunchpadImposter::Panel::Pixels_RowOne_ColTwo, 20, 20);
   makeOLED(this, Vec(10.00, 329.83), LaunchpadImposter::Panel::Pixels_RowOne_ColOne, 20, 20);
   makeOLED(this, Vec(223.00, 303.98), LaunchpadImposter::Panel::Pixels_RowTwo_ColNine, 20, 20);
   makeOLED(this, Vec(191.10, 303.98), LaunchpadImposter::Panel::Pixels_RowTwo_ColEight, 20, 20);
   makeOLED(this, Vec(165.25, 303.98), LaunchpadImposter::Panel::Pixels_RowTwo_ColSeven, 20, 20);
   makeOLED(this, Vec(139.39, 303.98), LaunchpadImposter::Panel::Pixels_RowTwo_ColSix, 20, 20);
   makeOLED(this, Vec(113.53, 303.98), LaunchpadImposter::Panel::Pixels_RowTwo_ColFive, 20, 20);
   makeOLED(this, Vec(87.67, 303.98), LaunchpadImposter::Panel::Pixels_RowTwo_ColFour, 20, 20);
   makeOLED(this, Vec(61.82, 303.98), LaunchpadImposter::Panel::Pixels_RowTwo_ColThree, 20, 20);
   makeOLED(this, Vec(35.96, 303.98), LaunchpadImposter::Panel::Pixels_RowTwo_ColTwo, 20, 20);
   makeOLED(this, Vec(10.10, 303.98), LaunchpadImposter::Panel::Pixels_RowTwo_ColOne, 20, 20);
   makeOLED(this, Vec(222.95, 278.13), LaunchpadImposter::Panel::Pixels_RowThree_ColNine, 20, 20);
   makeOLED(this, Vec(191.05, 278.13), LaunchpadImposter::Panel::Pixels_RowThree_ColEight, 20, 20);
   makeOLED(this, Vec(165.19, 278.13), LaunchpadImposter::Panel::Pixels_RowThree_ColSeven, 20, 20);
   makeOLED(this, Vec(139.34, 278.13), LaunchpadImposter::Panel::Pixels_RowThree_ColSix, 20, 20);
   makeOLED(this, Vec(113.48, 278.13), LaunchpadImposter::Panel::Pixels_RowThree_ColFive, 20, 20);
   makeOLED(this, Vec(87.62, 278.13), LaunchpadImposter::Panel::Pixels_RowThree_ColFour, 20, 20);
   makeOLED(this, Vec(61.77, 278.13), LaunchpadImposter::Panel::Pixels_RowThree_ColThree, 20, 20);
   makeOLED(this, Vec(35.91, 278.13), LaunchpadImposter::Panel::Pixels_RowThree_ColTwo, 20, 20);
   makeOLED(this, Vec(10.05, 278.13), LaunchpadImposter::Panel::Pixels_RowThree_ColOne, 20, 20);
   makeOLED(this, Vec(223.00, 252.28), LaunchpadImposter::Panel::Pixels_RowFour_ColNine, 20, 20);
   makeOLED(this, Vec(191.10, 252.28), LaunchpadImposter::Panel::Pixels_RowFour_ColEight, 20, 20);
   makeOLED(this, Vec(165.25, 252.28), LaunchpadImposter::Panel::Pixels_RowFour_ColSeven, 20, 20);
   makeOLED(this, Vec(139.39, 252.28), LaunchpadImposter::Panel::Pixels_RowFour_ColSix, 20, 20);
   makeOLED(this, Vec(113.53, 252.28), LaunchpadImposter::Panel::Pixels_RowFour_ColFive, 20, 20);
   makeOLED(this, Vec(87.67, 252.28), LaunchpadImposter::Panel::Pixels_RowFour_ColFour, 20, 20);
   makeOLED(this, Vec(61.82, 252.28), LaunchpadImposter::Panel::Pixels_RowFour_ColThree, 20, 20);
   makeOLED(this, Vec(35.96, 252.28), LaunchpadImposter::Panel::Pixels_RowFour_ColTwo, 20, 20);
   makeOLED(this, Vec(10.10, 252.28), LaunchpadImposter::Panel::Pixels_RowFour_ColOne, 20, 20);
   makeOLED(this, Vec(223.00, 226.43), LaunchpadImposter::Panel::Pixels_RowFive_ColNine, 20, 20);
   makeOLED(this, Vec(191.10, 226.43), LaunchpadImposter::Panel::Pixels_RowFive_ColEight, 20, 20);
   makeOLED(this, Vec(165.25, 226.43), LaunchpadImposter::Panel::Pixels_RowFive_ColSeven, 20, 20);
   makeOLED(this, Vec(139.39, 226.43), LaunchpadImposter::Panel::Pixels_RowFive_ColSix, 20, 20);
   makeOLED(this, Vec(113.53, 226.43), LaunchpadImposter::Panel::Pixels_RowFive_ColFive, 20, 20);
   makeOLED(this, Vec(87.67, 226.43), LaunchpadImposter::Panel::Pixels_RowFive_ColFour, 20, 20);
   makeOLED(this, Vec(61.82, 226.43), LaunchpadImposter::Panel::Pixels_RowFive_ColThree, 20, 20);
   makeOLED(this, Vec(35.96, 226.43), LaunchpadImposter::Panel::Pixels_RowFive_ColTwo, 20, 20);
   makeOLED(this, Vec(10.10, 226.43), LaunchpadImposter::Panel::Pixels_RowFive_ColOne, 20, 20);
   makeOLED(this, Vec(223.00, 200.58), LaunchpadImposter::Panel::Pixels_RowSix_ColNine, 20, 20);
   makeOLED(this, Vec(191.10, 200.58), LaunchpadImposter::Panel::Pixels_RowSix_ColEight, 20, 20);
   makeOLED(this, Vec(165.25, 200.58), LaunchpadImposter::Panel::Pixels_RowSix_ColSeven, 20, 20);
   makeOLED(this, Vec(139.39, 200.58), LaunchpadImposter::Panel::Pixels_RowSix_ColSix, 20, 20);
   makeOLED(this, Vec(113.53, 200.58), LaunchpadImposter::Panel::Pixels_RowSix_ColFive, 20, 20);
   makeOLED(this, Vec(87.67, 200.58), LaunchpadImposter::Panel::Pixels_RowSix_ColFour, 20, 20);
   makeOLED(this, Vec(61.82, 200.58), LaunchpadImposter::Panel::Pixels_RowSix_ColThree, 20, 20);
   makeOLED(this, Vec(35.96, 200.58), LaunchpadImposter::Panel::Pixels_RowSix_ColTwo, 20, 20);
   makeOLED(this, Vec(10.10, 200.58), LaunchpadImposter::Panel::Pixels_RowSix_ColOne, 20, 20);
   makeOLED(this, Vec(223.00, 174.73), LaunchpadImposter::Panel::Pixels_RowSeven_ColNine, 20, 20);
   makeOLED(this, Vec(191.10, 174.73), LaunchpadImposter::Panel::Pixels_RowSeven_ColEight, 20, 20);
   makeOLED(this, Vec(165.25, 174.73), LaunchpadImposter::Panel::Pixels_RowSeven_ColSeven, 20, 20);
   makeOLED(this, Vec(139.39, 174.73), LaunchpadImposter::Panel::Pixels_RowSeven_ColSix, 20, 20);
   makeOLED(this, Vec(113.53, 174.73), LaunchpadImposter::Panel::Pixels_RowSeven_ColFive, 20, 20);
   makeOLED(this, Vec(87.67, 174.73), LaunchpadImposter::Panel::Pixels_RowSeven_ColFour, 20, 20);
   makeOLED(this, Vec(61.82, 174.73), LaunchpadImposter::Panel::Pixels_RowSeven_ColThree, 20, 20);
   makeOLED(this, Vec(35.96, 174.73), LaunchpadImposter::Panel::Pixels_RowSeven_ColTwo, 20, 20);
   makeOLED(this, Vec(10.10, 174.73), LaunchpadImposter::Panel::Pixels_RowSeven_ColOne, 20, 20);
   makeOLED(this, Vec(223.00, 148.88), LaunchpadImposter::Panel::Pixels_RowEight_ColNine, 20, 20);
   makeOLED(this, Vec(191.10, 148.88), LaunchpadImposter::Panel::Pixels_RowEight_ColEight, 20, 20);
   makeOLED(this, Vec(165.25, 148.88), LaunchpadImposter::Panel::Pixels_RowEight_ColSeven, 20, 20);
   makeOLED(this, Vec(139.39, 148.88), LaunchpadImposter::Panel::Pixels_RowEight_ColSix, 20, 20);
   makeOLED(this, Vec(113.53, 148.88), LaunchpadImposter::Panel::Pixels_RowEight_ColFive, 20, 20);
   makeOLED(this, Vec(87.67, 148.88), LaunchpadImposter::Panel::Pixels_RowEight_ColFour, 20, 20);
   makeOLED(this, Vec(61.82, 148.88), LaunchpadImposter::Panel::Pixels_RowEight_ColThree, 20, 20);
   makeOLED(this, Vec(35.96, 148.88), LaunchpadImposter::Panel::Pixels_RowEight_ColTwo, 20, 20);
   makeOLED(this, Vec(10.10, 148.88), LaunchpadImposter::Panel::Pixels_RowEight_ColOne, 20, 20);
   makeOLED(this, Vec(191.10, 116.93), LaunchpadImposter::Panel::Pixels_RowNine_ColEight, 20, 20);
   makeOLED(this, Vec(165.25, 116.93), LaunchpadImposter::Panel::Pixels_RowNine_ColSeven, 20, 20);
   makeOLED(this, Vec(139.39, 116.93), LaunchpadImposter::Panel::Pixels_RowNine_ColSix, 20, 20);
   makeOLED(this, Vec(113.53, 116.93), LaunchpadImposter::Panel::Pixels_RowNine_ColFive, 20, 20);
   makeOLED(this, Vec(87.67, 116.93), LaunchpadImposter::Panel::Pixels_RowNine_ColFour, 20, 20);
   makeOLED(this, Vec(61.82, 116.93), LaunchpadImposter::Panel::Pixels_RowNine_ColThree, 20, 20);
   makeOLED(this, Vec(35.96, 116.93), LaunchpadImposter::Panel::Pixels_RowNine_ColTwo, 20, 20);
   makeOLED(this, Vec(10.10, 116.93), LaunchpadImposter::Panel::Pixels_RowNine_ColOne, 20, 20);
}

#endif // NOT LaunchpadImposterHPP
