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
      RowOne_ColNine = 2,
      RowOne_ColEigth = 3,
      RowOne_ColSeven = 4,
      RowOne_ColSix = 5,
      RowOne_ColFive = 6,
      RowOne_ColFour = 7,
      RowOne_ColThree = 8,
      RowOne_ColTwo = 9,
      RowOne_ColOne = 10,
      RowTwo_ColNine = 11,
      RowTwo_ColEigth = 12,
      RowTwo_ColSeven = 13,
      RowTwo_ColSix = 14,
      RowTwo_ColFive = 15,
      RowTwo_ColFour = 16,
      RowTwo_ColThree = 17,
      RowTwo_ColTwo = 18,
      RowTwo_ColOne = 19,
      RowThree_ColNine = 20,
      RowThree_ColEigth = 21,
      RowThree_ColSeven = 22,
      RowThree_ColSix = 23,
      RowThree_ColFive = 24,
      RowThree_ColFour = 25,
      RowThree_ColThree = 26,
      RowThree_ColTwo = 27,
      RowThree_ColOne = 28,
      RowFour_ColNine = 29,
      RowFour_ColEigth = 30,
      RowFour_ColSeven = 31,
      RowFour_ColSix = 32,
      RowFour_ColFive = 33,
      RowFour_ColFour = 34,
      RowFour_ColThree = 35,
      RowFour_ColTwo = 36,
      RowFour_ColOne = 37,
      RowFive_ColNine = 38,
      RowFive_ColEigth = 39,
      RowFive_ColSeven = 40,
      RowFive_ColSix = 41,
      RowFive_ColFive = 42,
      RowFive_ColFour = 43,
      RowFive_ColThree = 44,
      RowFive_ColTwo = 45,
      RowFive_ColOne = 46,
      RowSix_ColNine = 47,
      RowSix_ColEigth = 48,
      RowSix_ColSeven = 49,
      RowSix_ColSix = 50,
      RowSix_ColFive = 51,
      RowSix_ColFour = 52,
      RowSix_ColThree = 53,
      RowSix_ColTwo = 54,
      RowSix_ColOne = 55,
      RowSeven_ColNine = 56,
      RowSeven_ColEigth = 57,
      RowSeven_ColSeven = 58,
      RowSeven_ColSix = 59,
      RowSeven_ColFive = 60,
      RowSeven_ColFour = 61,
      RowSeven_ColThree = 62,
      RowSeven_ColTwo = 63,
      RowSeven_ColOne = 64,
      RowEight_ColNine = 65,
      RowEight_ColEigth = 66,
      RowEight_ColSeven = 67,
      RowEight_ColSix = 68,
      RowEight_ColFive = 69,
      RowEight_ColFour = 70,
      RowEight_ColThree = 71,
      RowEight_ColTwo = 72,
      RowEight_ColOne = 73,
      RowNine_ColEigth = 74,
      RowNine_ColSeven = 75,
      RowNine_ColSix = 76,
      RowNine_ColFive = 77,
      RowNine_ColFour = 78,
      RowNine_ColThree = 79,
      RowNine_ColTwo = 80,
      RowNine_ColOne = 81,
      // knobs
      // sliders
      PARAMS_LEN = 82
   };

   enum DisplayId
   {
      // lcd
      Text_DeviceId = 0,
      // oled
      DISPLAYS_LEN = 1
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
      RGB_RowNine_Logo = 0,
      // ledbuttons
      RGB_RowOne_ColNine = 3,
      RGB_RowOne_ColEigth = 6,
      RGB_RowOne_ColSeven = 9,
      RGB_RowOne_ColSix = 12,
      RGB_RowOne_ColFive = 15,
      RGB_RowOne_ColFour = 18,
      RGB_RowOne_ColThree = 21,
      RGB_RowOne_ColTwo = 24,
      RGB_RowOne_ColOne = 27,
      RGB_RowTwo_ColNine = 30,
      RGB_RowTwo_ColEigth = 33,
      RGB_RowTwo_ColSeven = 36,
      RGB_RowTwo_ColSix = 39,
      RGB_RowTwo_ColFive = 42,
      RGB_RowTwo_ColFour = 45,
      RGB_RowTwo_ColThree = 48,
      RGB_RowTwo_ColTwo = 51,
      RGB_RowTwo_ColOne = 54,
      RGB_RowThree_ColNine = 57,
      RGB_RowThree_ColEigth = 60,
      RGB_RowThree_ColSeven = 63,
      RGB_RowThree_ColSix = 66,
      RGB_RowThree_ColFive = 69,
      RGB_RowThree_ColFour = 72,
      RGB_RowThree_ColThree = 75,
      RGB_RowThree_ColTwo = 78,
      RGB_RowThree_ColOne = 81,
      RGB_RowFour_ColNine = 84,
      RGB_RowFour_ColEigth = 87,
      RGB_RowFour_ColSeven = 90,
      RGB_RowFour_ColSix = 93,
      RGB_RowFour_ColFive = 96,
      RGB_RowFour_ColFour = 99,
      RGB_RowFour_ColThree = 102,
      RGB_RowFour_ColTwo = 105,
      RGB_RowFour_ColOne = 108,
      RGB_RowFive_ColNine = 111,
      RGB_RowFive_ColEigth = 114,
      RGB_RowFive_ColSeven = 117,
      RGB_RowFive_ColSix = 120,
      RGB_RowFive_ColFive = 123,
      RGB_RowFive_ColFour = 126,
      RGB_RowFive_ColThree = 129,
      RGB_RowFive_ColTwo = 132,
      RGB_RowFive_ColOne = 135,
      RGB_RowSix_ColNine = 138,
      RGB_RowSix_ColEigth = 141,
      RGB_RowSix_ColSeven = 144,
      RGB_RowSix_ColSix = 147,
      RGB_RowSix_ColFive = 150,
      RGB_RowSix_ColFour = 153,
      RGB_RowSix_ColThree = 156,
      RGB_RowSix_ColTwo = 159,
      RGB_RowSix_ColOne = 162,
      RGB_RowSeven_ColNine = 165,
      RGB_RowSeven_ColEigth = 168,
      RGB_RowSeven_ColSeven = 171,
      RGB_RowSeven_ColSix = 174,
      RGB_RowSeven_ColFive = 177,
      RGB_RowSeven_ColFour = 180,
      RGB_RowSeven_ColThree = 183,
      RGB_RowSeven_ColTwo = 186,
      RGB_RowSeven_ColOne = 189,
      RGB_RowEight_ColNine = 192,
      RGB_RowEight_ColEigth = 195,
      RGB_RowEight_ColSeven = 198,
      RGB_RowEight_ColSix = 201,
      RGB_RowEight_ColFive = 204,
      RGB_RowEight_ColFour = 207,
      RGB_RowEight_ColThree = 210,
      RGB_RowEight_ColTwo = 213,
      RGB_RowEight_ColOne = 216,
      RGB_RowNine_ColEigth = 219,
      RGB_RowNine_ColSeven = 222,
      RGB_RowNine_ColSix = 225,
      RGB_RowNine_ColFive = 228,
      RGB_RowNine_ColFour = 231,
      RGB_RowNine_ColThree = 234,
      RGB_RowNine_ColTwo = 237,
      RGB_RowNine_ColOne = 240,
      // sliders
      LIGHTS_LEN = 243
   };

};

void LaunchpadImposter::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::DeviceIdDown, "DeviceIdDown");
   configButton(Panel::DeviceIdUp, "DeviceIdUp");

   configButton(Panel::RowOne_ColNine, "RowOne_ColNine");
   configButton(Panel::RowOne_ColEigth, "RowOne_ColEigth");
   configButton(Panel::RowOne_ColSeven, "RowOne_ColSeven");
   configButton(Panel::RowOne_ColSix, "RowOne_ColSix");
   configButton(Panel::RowOne_ColFive, "RowOne_ColFive");
   configButton(Panel::RowOne_ColFour, "RowOne_ColFour");
   configButton(Panel::RowOne_ColThree, "RowOne_ColThree");
   configButton(Panel::RowOne_ColTwo, "RowOne_ColTwo");
   configButton(Panel::RowOne_ColOne, "RowOne_ColOne");
   configButton(Panel::RowTwo_ColNine, "RowTwo_ColNine");
   configButton(Panel::RowTwo_ColEigth, "RowTwo_ColEigth");
   configButton(Panel::RowTwo_ColSeven, "RowTwo_ColSeven");
   configButton(Panel::RowTwo_ColSix, "RowTwo_ColSix");
   configButton(Panel::RowTwo_ColFive, "RowTwo_ColFive");
   configButton(Panel::RowTwo_ColFour, "RowTwo_ColFour");
   configButton(Panel::RowTwo_ColThree, "RowTwo_ColThree");
   configButton(Panel::RowTwo_ColTwo, "RowTwo_ColTwo");
   configButton(Panel::RowTwo_ColOne, "RowTwo_ColOne");
   configButton(Panel::RowThree_ColNine, "RowThree_ColNine");
   configButton(Panel::RowThree_ColEigth, "RowThree_ColEigth");
   configButton(Panel::RowThree_ColSeven, "RowThree_ColSeven");
   configButton(Panel::RowThree_ColSix, "RowThree_ColSix");
   configButton(Panel::RowThree_ColFive, "RowThree_ColFive");
   configButton(Panel::RowThree_ColFour, "RowThree_ColFour");
   configButton(Panel::RowThree_ColThree, "RowThree_ColThree");
   configButton(Panel::RowThree_ColTwo, "RowThree_ColTwo");
   configButton(Panel::RowThree_ColOne, "RowThree_ColOne");
   configButton(Panel::RowFour_ColNine, "RowFour_ColNine");
   configButton(Panel::RowFour_ColEigth, "RowFour_ColEigth");
   configButton(Panel::RowFour_ColSeven, "RowFour_ColSeven");
   configButton(Panel::RowFour_ColSix, "RowFour_ColSix");
   configButton(Panel::RowFour_ColFive, "RowFour_ColFive");
   configButton(Panel::RowFour_ColFour, "RowFour_ColFour");
   configButton(Panel::RowFour_ColThree, "RowFour_ColThree");
   configButton(Panel::RowFour_ColTwo, "RowFour_ColTwo");
   configButton(Panel::RowFour_ColOne, "RowFour_ColOne");
   configButton(Panel::RowFive_ColNine, "RowFive_ColNine");
   configButton(Panel::RowFive_ColEigth, "RowFive_ColEigth");
   configButton(Panel::RowFive_ColSeven, "RowFive_ColSeven");
   configButton(Panel::RowFive_ColSix, "RowFive_ColSix");
   configButton(Panel::RowFive_ColFive, "RowFive_ColFive");
   configButton(Panel::RowFive_ColFour, "RowFive_ColFour");
   configButton(Panel::RowFive_ColThree, "RowFive_ColThree");
   configButton(Panel::RowFive_ColTwo, "RowFive_ColTwo");
   configButton(Panel::RowFive_ColOne, "RowFive_ColOne");
   configButton(Panel::RowSix_ColNine, "RowSix_ColNine");
   configButton(Panel::RowSix_ColEigth, "RowSix_ColEigth");
   configButton(Panel::RowSix_ColSeven, "RowSix_ColSeven");
   configButton(Panel::RowSix_ColSix, "RowSix_ColSix");
   configButton(Panel::RowSix_ColFive, "RowSix_ColFive");
   configButton(Panel::RowSix_ColFour, "RowSix_ColFour");
   configButton(Panel::RowSix_ColThree, "RowSix_ColThree");
   configButton(Panel::RowSix_ColTwo, "RowSix_ColTwo");
   configButton(Panel::RowSix_ColOne, "RowSix_ColOne");
   configButton(Panel::RowSeven_ColNine, "RowSeven_ColNine");
   configButton(Panel::RowSeven_ColEigth, "RowSeven_ColEigth");
   configButton(Panel::RowSeven_ColSeven, "RowSeven_ColSeven");
   configButton(Panel::RowSeven_ColSix, "RowSeven_ColSix");
   configButton(Panel::RowSeven_ColFive, "RowSeven_ColFive");
   configButton(Panel::RowSeven_ColFour, "RowSeven_ColFour");
   configButton(Panel::RowSeven_ColThree, "RowSeven_ColThree");
   configButton(Panel::RowSeven_ColTwo, "RowSeven_ColTwo");
   configButton(Panel::RowSeven_ColOne, "RowSeven_ColOne");
   configButton(Panel::RowEight_ColNine, "RowEight_ColNine");
   configButton(Panel::RowEight_ColEigth, "RowEight_ColEigth");
   configButton(Panel::RowEight_ColSeven, "RowEight_ColSeven");
   configButton(Panel::RowEight_ColSix, "RowEight_ColSix");
   configButton(Panel::RowEight_ColFive, "RowEight_ColFive");
   configButton(Panel::RowEight_ColFour, "RowEight_ColFour");
   configButton(Panel::RowEight_ColThree, "RowEight_ColThree");
   configButton(Panel::RowEight_ColTwo, "RowEight_ColTwo");
   configButton(Panel::RowEight_ColOne, "RowEight_ColOne");
   configButton(Panel::RowNine_ColEigth, "RowNine_ColEigth");
   configButton(Panel::RowNine_ColSeven, "RowNine_ColSeven");
   configButton(Panel::RowNine_ColSix, "RowNine_ColSix");
   configButton(Panel::RowNine_ColFive, "RowNine_ColFive");
   configButton(Panel::RowNine_ColFour, "RowNine_ColFour");
   configButton(Panel::RowNine_ColThree, "RowNine_ColThree");
   configButton(Panel::RowNine_ColTwo, "RowNine_ColTwo");
   configButton(Panel::RowNine_ColOne, "RowNine_ColOne");
}

void LaunchpadImposterWidget::setup()
{
   makePanel("res/Utilities/LaunchpadImposter.svg");

   makeButton(this, Vec(145.91, 83.61), LaunchpadImposter::Panel::DeviceIdDown);
   makeButton(this, Vec(145.91, 64.97), LaunchpadImposter::Panel::DeviceIdUp);

   makeLEDButton(this, Vec(205.10, 323.26), LaunchpadImposter::Panel::RowOne_ColNine, LaunchpadImposter::Panel::RGB_RowOne_ColNine);
   makeLEDButton(this, Vec(175.90, 323.26), LaunchpadImposter::Panel::RowOne_ColEigth, LaunchpadImposter::Panel::RGB_RowOne_ColEigth);
   makeLEDButton(this, Vec(153.61, 323.26), LaunchpadImposter::Panel::RowOne_ColSeven, LaunchpadImposter::Panel::RGB_RowOne_ColSeven);
   makeLEDButton(this, Vec(131.33, 323.26), LaunchpadImposter::Panel::RowOne_ColSix, LaunchpadImposter::Panel::RGB_RowOne_ColSix);
   makeLEDButton(this, Vec(109.04, 323.26), LaunchpadImposter::Panel::RowOne_ColFive, LaunchpadImposter::Panel::RGB_RowOne_ColFive);
   makeLEDButton(this, Vec(86.76, 323.26), LaunchpadImposter::Panel::RowOne_ColFour, LaunchpadImposter::Panel::RGB_RowOne_ColFour);
   makeLEDButton(this, Vec(64.47, 323.26), LaunchpadImposter::Panel::RowOne_ColThree, LaunchpadImposter::Panel::RGB_RowOne_ColThree);
   makeLEDButton(this, Vec(42.18, 323.26), LaunchpadImposter::Panel::RowOne_ColTwo, LaunchpadImposter::Panel::RGB_RowOne_ColTwo);
   makeLEDButton(this, Vec(19.90, 323.26), LaunchpadImposter::Panel::RowOne_ColOne, LaunchpadImposter::Panel::RGB_RowOne_ColOne);
   makeLEDButton(this, Vec(205.10, 301.26), LaunchpadImposter::Panel::RowTwo_ColNine, LaunchpadImposter::Panel::RGB_RowTwo_ColNine);
   makeLEDButton(this, Vec(175.90, 301.26), LaunchpadImposter::Panel::RowTwo_ColEigth, LaunchpadImposter::Panel::RGB_RowTwo_ColEigth);
   makeLEDButton(this, Vec(153.61, 301.26), LaunchpadImposter::Panel::RowTwo_ColSeven, LaunchpadImposter::Panel::RGB_RowTwo_ColSeven);
   makeLEDButton(this, Vec(131.33, 301.26), LaunchpadImposter::Panel::RowTwo_ColSix, LaunchpadImposter::Panel::RGB_RowTwo_ColSix);
   makeLEDButton(this, Vec(109.04, 301.26), LaunchpadImposter::Panel::RowTwo_ColFive, LaunchpadImposter::Panel::RGB_RowTwo_ColFive);
   makeLEDButton(this, Vec(86.76, 301.26), LaunchpadImposter::Panel::RowTwo_ColFour, LaunchpadImposter::Panel::RGB_RowTwo_ColFour);
   makeLEDButton(this, Vec(64.47, 301.26), LaunchpadImposter::Panel::RowTwo_ColThree, LaunchpadImposter::Panel::RGB_RowTwo_ColThree);
   makeLEDButton(this, Vec(42.18, 301.26), LaunchpadImposter::Panel::RowTwo_ColTwo, LaunchpadImposter::Panel::RGB_RowTwo_ColTwo);
   makeLEDButton(this, Vec(19.90, 301.26), LaunchpadImposter::Panel::RowTwo_ColOne, LaunchpadImposter::Panel::RGB_RowTwo_ColOne);
   makeLEDButton(this, Vec(205.10, 279.26), LaunchpadImposter::Panel::RowThree_ColNine, LaunchpadImposter::Panel::RGB_RowThree_ColNine);
   makeLEDButton(this, Vec(175.90, 279.26), LaunchpadImposter::Panel::RowThree_ColEigth, LaunchpadImposter::Panel::RGB_RowThree_ColEigth);
   makeLEDButton(this, Vec(153.61, 279.26), LaunchpadImposter::Panel::RowThree_ColSeven, LaunchpadImposter::Panel::RGB_RowThree_ColSeven);
   makeLEDButton(this, Vec(131.33, 279.26), LaunchpadImposter::Panel::RowThree_ColSix, LaunchpadImposter::Panel::RGB_RowThree_ColSix);
   makeLEDButton(this, Vec(109.04, 279.26), LaunchpadImposter::Panel::RowThree_ColFive, LaunchpadImposter::Panel::RGB_RowThree_ColFive);
   makeLEDButton(this, Vec(86.76, 279.26), LaunchpadImposter::Panel::RowThree_ColFour, LaunchpadImposter::Panel::RGB_RowThree_ColFour);
   makeLEDButton(this, Vec(64.47, 279.26), LaunchpadImposter::Panel::RowThree_ColThree, LaunchpadImposter::Panel::RGB_RowThree_ColThree);
   makeLEDButton(this, Vec(42.18, 279.26), LaunchpadImposter::Panel::RowThree_ColTwo, LaunchpadImposter::Panel::RGB_RowThree_ColTwo);
   makeLEDButton(this, Vec(19.90, 279.26), LaunchpadImposter::Panel::RowThree_ColOne, LaunchpadImposter::Panel::RGB_RowThree_ColOne);
   makeLEDButton(this, Vec(205.10, 257.26), LaunchpadImposter::Panel::RowFour_ColNine, LaunchpadImposter::Panel::RGB_RowFour_ColNine);
   makeLEDButton(this, Vec(175.90, 257.26), LaunchpadImposter::Panel::RowFour_ColEigth, LaunchpadImposter::Panel::RGB_RowFour_ColEigth);
   makeLEDButton(this, Vec(153.61, 257.26), LaunchpadImposter::Panel::RowFour_ColSeven, LaunchpadImposter::Panel::RGB_RowFour_ColSeven);
   makeLEDButton(this, Vec(131.33, 257.26), LaunchpadImposter::Panel::RowFour_ColSix, LaunchpadImposter::Panel::RGB_RowFour_ColSix);
   makeLEDButton(this, Vec(109.04, 257.26), LaunchpadImposter::Panel::RowFour_ColFive, LaunchpadImposter::Panel::RGB_RowFour_ColFive);
   makeLEDButton(this, Vec(86.76, 257.26), LaunchpadImposter::Panel::RowFour_ColFour, LaunchpadImposter::Panel::RGB_RowFour_ColFour);
   makeLEDButton(this, Vec(64.47, 257.26), LaunchpadImposter::Panel::RowFour_ColThree, LaunchpadImposter::Panel::RGB_RowFour_ColThree);
   makeLEDButton(this, Vec(42.18, 257.26), LaunchpadImposter::Panel::RowFour_ColTwo, LaunchpadImposter::Panel::RGB_RowFour_ColTwo);
   makeLEDButton(this, Vec(19.90, 257.26), LaunchpadImposter::Panel::RowFour_ColOne, LaunchpadImposter::Panel::RGB_RowFour_ColOne);
   makeLEDButton(this, Vec(205.10, 234.26), LaunchpadImposter::Panel::RowFive_ColNine, LaunchpadImposter::Panel::RGB_RowFive_ColNine);
   makeLEDButton(this, Vec(175.90, 234.26), LaunchpadImposter::Panel::RowFive_ColEigth, LaunchpadImposter::Panel::RGB_RowFive_ColEigth);
   makeLEDButton(this, Vec(153.61, 234.26), LaunchpadImposter::Panel::RowFive_ColSeven, LaunchpadImposter::Panel::RGB_RowFive_ColSeven);
   makeLEDButton(this, Vec(131.33, 234.26), LaunchpadImposter::Panel::RowFive_ColSix, LaunchpadImposter::Panel::RGB_RowFive_ColSix);
   makeLEDButton(this, Vec(109.04, 234.26), LaunchpadImposter::Panel::RowFive_ColFive, LaunchpadImposter::Panel::RGB_RowFive_ColFive);
   makeLEDButton(this, Vec(86.76, 234.26), LaunchpadImposter::Panel::RowFive_ColFour, LaunchpadImposter::Panel::RGB_RowFive_ColFour);
   makeLEDButton(this, Vec(64.47, 234.26), LaunchpadImposter::Panel::RowFive_ColThree, LaunchpadImposter::Panel::RGB_RowFive_ColThree);
   makeLEDButton(this, Vec(42.18, 234.26), LaunchpadImposter::Panel::RowFive_ColTwo, LaunchpadImposter::Panel::RGB_RowFive_ColTwo);
   makeLEDButton(this, Vec(19.90, 234.26), LaunchpadImposter::Panel::RowFive_ColOne, LaunchpadImposter::Panel::RGB_RowFive_ColOne);
   makeLEDButton(this, Vec(205.10, 212.26), LaunchpadImposter::Panel::RowSix_ColNine, LaunchpadImposter::Panel::RGB_RowSix_ColNine);
   makeLEDButton(this, Vec(175.90, 212.26), LaunchpadImposter::Panel::RowSix_ColEigth, LaunchpadImposter::Panel::RGB_RowSix_ColEigth);
   makeLEDButton(this, Vec(153.61, 212.26), LaunchpadImposter::Panel::RowSix_ColSeven, LaunchpadImposter::Panel::RGB_RowSix_ColSeven);
   makeLEDButton(this, Vec(131.33, 212.26), LaunchpadImposter::Panel::RowSix_ColSix, LaunchpadImposter::Panel::RGB_RowSix_ColSix);
   makeLEDButton(this, Vec(109.04, 212.26), LaunchpadImposter::Panel::RowSix_ColFive, LaunchpadImposter::Panel::RGB_RowSix_ColFive);
   makeLEDButton(this, Vec(86.76, 212.26), LaunchpadImposter::Panel::RowSix_ColFour, LaunchpadImposter::Panel::RGB_RowSix_ColFour);
   makeLEDButton(this, Vec(64.47, 212.26), LaunchpadImposter::Panel::RowSix_ColThree, LaunchpadImposter::Panel::RGB_RowSix_ColThree);
   makeLEDButton(this, Vec(42.18, 212.26), LaunchpadImposter::Panel::RowSix_ColTwo, LaunchpadImposter::Panel::RGB_RowSix_ColTwo);
   makeLEDButton(this, Vec(19.90, 212.26), LaunchpadImposter::Panel::RowSix_ColOne, LaunchpadImposter::Panel::RGB_RowSix_ColOne);
   makeLEDButton(this, Vec(205.10, 189.26), LaunchpadImposter::Panel::RowSeven_ColNine, LaunchpadImposter::Panel::RGB_RowSeven_ColNine);
   makeLEDButton(this, Vec(175.90, 189.26), LaunchpadImposter::Panel::RowSeven_ColEigth, LaunchpadImposter::Panel::RGB_RowSeven_ColEigth);
   makeLEDButton(this, Vec(153.61, 189.26), LaunchpadImposter::Panel::RowSeven_ColSeven, LaunchpadImposter::Panel::RGB_RowSeven_ColSeven);
   makeLEDButton(this, Vec(131.33, 189.26), LaunchpadImposter::Panel::RowSeven_ColSix, LaunchpadImposter::Panel::RGB_RowSeven_ColSix);
   makeLEDButton(this, Vec(109.04, 189.26), LaunchpadImposter::Panel::RowSeven_ColFive, LaunchpadImposter::Panel::RGB_RowSeven_ColFive);
   makeLEDButton(this, Vec(86.76, 189.26), LaunchpadImposter::Panel::RowSeven_ColFour, LaunchpadImposter::Panel::RGB_RowSeven_ColFour);
   makeLEDButton(this, Vec(64.47, 189.26), LaunchpadImposter::Panel::RowSeven_ColThree, LaunchpadImposter::Panel::RGB_RowSeven_ColThree);
   makeLEDButton(this, Vec(42.18, 189.26), LaunchpadImposter::Panel::RowSeven_ColTwo, LaunchpadImposter::Panel::RGB_RowSeven_ColTwo);
   makeLEDButton(this, Vec(19.90, 189.26), LaunchpadImposter::Panel::RowSeven_ColOne, LaunchpadImposter::Panel::RGB_RowSeven_ColOne);
   makeLEDButton(this, Vec(205.10, 167.26), LaunchpadImposter::Panel::RowEight_ColNine, LaunchpadImposter::Panel::RGB_RowEight_ColNine);
   makeLEDButton(this, Vec(175.90, 167.26), LaunchpadImposter::Panel::RowEight_ColEigth, LaunchpadImposter::Panel::RGB_RowEight_ColEigth);
   makeLEDButton(this, Vec(153.61, 167.26), LaunchpadImposter::Panel::RowEight_ColSeven, LaunchpadImposter::Panel::RGB_RowEight_ColSeven);
   makeLEDButton(this, Vec(131.33, 167.26), LaunchpadImposter::Panel::RowEight_ColSix, LaunchpadImposter::Panel::RGB_RowEight_ColSix);
   makeLEDButton(this, Vec(109.04, 167.26), LaunchpadImposter::Panel::RowEight_ColFive, LaunchpadImposter::Panel::RGB_RowEight_ColFive);
   makeLEDButton(this, Vec(86.76, 167.26), LaunchpadImposter::Panel::RowEight_ColFour, LaunchpadImposter::Panel::RGB_RowEight_ColFour);
   makeLEDButton(this, Vec(64.47, 167.26), LaunchpadImposter::Panel::RowEight_ColThree, LaunchpadImposter::Panel::RGB_RowEight_ColThree);
   makeLEDButton(this, Vec(42.18, 167.26), LaunchpadImposter::Panel::RowEight_ColTwo, LaunchpadImposter::Panel::RGB_RowEight_ColTwo);
   makeLEDButton(this, Vec(19.90, 167.26), LaunchpadImposter::Panel::RowEight_ColOne, LaunchpadImposter::Panel::RGB_RowEight_ColOne);
   makeLEDButton(this, Vec(175.90, 137.94), LaunchpadImposter::Panel::RowNine_ColEigth, LaunchpadImposter::Panel::RGB_RowNine_ColEigth);
   makeLEDButton(this, Vec(153.61, 137.94), LaunchpadImposter::Panel::RowNine_ColSeven, LaunchpadImposter::Panel::RGB_RowNine_ColSeven);
   makeLEDButton(this, Vec(131.33, 137.94), LaunchpadImposter::Panel::RowNine_ColSix, LaunchpadImposter::Panel::RGB_RowNine_ColSix);
   makeLEDButton(this, Vec(109.04, 137.94), LaunchpadImposter::Panel::RowNine_ColFive, LaunchpadImposter::Panel::RGB_RowNine_ColFive);
   makeLEDButton(this, Vec(86.76, 137.94), LaunchpadImposter::Panel::RowNine_ColFour, LaunchpadImposter::Panel::RGB_RowNine_ColFour);
   makeLEDButton(this, Vec(64.47, 137.94), LaunchpadImposter::Panel::RowNine_ColThree, LaunchpadImposter::Panel::RGB_RowNine_ColThree);
   makeLEDButton(this, Vec(42.18, 137.94), LaunchpadImposter::Panel::RowNine_ColTwo, LaunchpadImposter::Panel::RGB_RowNine_ColTwo);
   makeLEDButton(this, Vec(19.90, 137.94), LaunchpadImposter::Panel::RowNine_ColOne, LaunchpadImposter::Panel::RGB_RowNine_ColOne);

   makeLED(this, Vec(205.10, 137.94), LaunchpadImposter::Panel::RGB_RowNine_Logo);

   makeLCD(this, Vec(98.89, 62.29), 2, LaunchpadImposter::Panel::Text_DeviceId, 18);
}

#endif // NOT LaunchpadImposterHPP
