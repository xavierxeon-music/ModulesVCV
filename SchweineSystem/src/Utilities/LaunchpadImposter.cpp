#include "LaunchpadImposter.h"

#include <Tools/Text.h>
#include <Tools/Variable.h>

#include <SvinLaunchpadClient.h>

LaunchpadImposter::LaunchpadImposter()
   : Svin::Module()
   , Svin::Midi::Input(true)
   , Svin::Midi::Output(true)
   , deviceId(0)
   , deviceIdDisplay(this, Panel::Text_DeviceId)
   , deviceIdUpButton(this, Panel::DeviceIdUp)
   , deviceIdDownButton(this, Panel::DeviceIdDown)
   , buttonList(this)
   , statusLED(this, Panel::RGB_RowNine_Logo)
{
   setup();

   deviceIdDisplay.setColor(Color::Predefined::Yellow);

   buttonList.append({{Panel::RowOne_ColOne, Panel::RGB_RowOne_ColOne},
                      {Panel::RowOne_ColTwo, Panel::RGB_RowOne_ColTwo},
                      {Panel::RowOne_ColThree, Panel::RGB_RowOne_ColThree},
                      {Panel::RowOne_ColFour, Panel::RGB_RowOne_ColFour},
                      {Panel::RowOne_ColFive, Panel::RGB_RowOne_ColFive},
                      {Panel::RowOne_ColSix, Panel::RGB_RowOne_ColSix},
                      {Panel::RowOne_ColSeven, Panel::RGB_RowOne_ColSeven},
                      {Panel::RowOne_ColEight, Panel::RGB_RowOne_ColEight},
                      {Panel::RowOne_ColNine, Panel::RGB_RowOne_ColNine},
                      {Panel::RowTwo_ColOne, Panel::RGB_RowTwo_ColOne},
                      {Panel::RowTwo_ColTwo, Panel::RGB_RowTwo_ColTwo},
                      {Panel::RowTwo_ColThree, Panel::RGB_RowTwo_ColThree},
                      {Panel::RowTwo_ColFour, Panel::RGB_RowTwo_ColFour},
                      {Panel::RowTwo_ColFive, Panel::RGB_RowTwo_ColFive},
                      {Panel::RowTwo_ColSix, Panel::RGB_RowTwo_ColSix},
                      {Panel::RowTwo_ColSeven, Panel::RGB_RowTwo_ColSeven},
                      {Panel::RowTwo_ColEight, Panel::RGB_RowTwo_ColEight},
                      {Panel::RowTwo_ColNine, Panel::RGB_RowTwo_ColNine},
                      {Panel::RowThree_ColOne, Panel::RGB_RowThree_ColOne},
                      {Panel::RowThree_ColTwo, Panel::RGB_RowThree_ColTwo},
                      {Panel::RowThree_ColThree, Panel::RGB_RowThree_ColThree},
                      {Panel::RowThree_ColFour, Panel::RGB_RowThree_ColFour},
                      {Panel::RowThree_ColFive, Panel::RGB_RowThree_ColFive},
                      {Panel::RowThree_ColSix, Panel::RGB_RowThree_ColSix},
                      {Panel::RowThree_ColSeven, Panel::RGB_RowThree_ColSeven},
                      {Panel::RowThree_ColEight, Panel::RGB_RowThree_ColEight},
                      {Panel::RowThree_ColNine, Panel::RGB_RowThree_ColNine},
                      {Panel::RowFour_ColOne, Panel::RGB_RowFour_ColOne},
                      {Panel::RowFour_ColTwo, Panel::RGB_RowFour_ColTwo},
                      {Panel::RowFour_ColThree, Panel::RGB_RowFour_ColThree},
                      {Panel::RowFour_ColFour, Panel::RGB_RowFour_ColFour},
                      {Panel::RowFour_ColFive, Panel::RGB_RowFour_ColFive},
                      {Panel::RowFour_ColSix, Panel::RGB_RowFour_ColSix},
                      {Panel::RowFour_ColSeven, Panel::RGB_RowFour_ColSeven},
                      {Panel::RowFour_ColEight, Panel::RGB_RowFour_ColEight},
                      {Panel::RowFour_ColNine, Panel::RGB_RowFour_ColNine},
                      {Panel::RowFive_ColOne, Panel::RGB_RowFive_ColOne},
                      {Panel::RowFive_ColTwo, Panel::RGB_RowFive_ColTwo},
                      {Panel::RowFive_ColThree, Panel::RGB_RowFive_ColThree},
                      {Panel::RowFive_ColFour, Panel::RGB_RowFive_ColFour},
                      {Panel::RowFive_ColFive, Panel::RGB_RowFive_ColFive},
                      {Panel::RowFive_ColSix, Panel::RGB_RowFive_ColSix},
                      {Panel::RowFive_ColSeven, Panel::RGB_RowFive_ColSeven},
                      {Panel::RowFive_ColEight, Panel::RGB_RowFive_ColEight},
                      {Panel::RowFive_ColNine, Panel::RGB_RowFive_ColNine},
                      {Panel::RowSix_ColOne, Panel::RGB_RowSix_ColOne},
                      {Panel::RowSix_ColTwo, Panel::RGB_RowSix_ColTwo},
                      {Panel::RowSix_ColThree, Panel::RGB_RowSix_ColThree},
                      {Panel::RowSix_ColFour, Panel::RGB_RowSix_ColFour},
                      {Panel::RowSix_ColFive, Panel::RGB_RowSix_ColFive},
                      {Panel::RowSix_ColSix, Panel::RGB_RowSix_ColSix},
                      {Panel::RowSix_ColSeven, Panel::RGB_RowSix_ColSeven},
                      {Panel::RowSix_ColEight, Panel::RGB_RowSix_ColEight},
                      {Panel::RowSix_ColNine, Panel::RGB_RowSix_ColNine},
                      {Panel::RowSeven_ColOne, Panel::RGB_RowSeven_ColOne},
                      {Panel::RowSeven_ColTwo, Panel::RGB_RowSeven_ColTwo},
                      {Panel::RowSeven_ColThree, Panel::RGB_RowSeven_ColThree},
                      {Panel::RowSeven_ColFour, Panel::RGB_RowSeven_ColFour},
                      {Panel::RowSeven_ColFive, Panel::RGB_RowSeven_ColFive},
                      {Panel::RowSeven_ColSix, Panel::RGB_RowSeven_ColSix},
                      {Panel::RowSeven_ColSeven, Panel::RGB_RowSeven_ColSeven},
                      {Panel::RowSeven_ColEight, Panel::RGB_RowSeven_ColEight},
                      {Panel::RowSeven_ColNine, Panel::RGB_RowSeven_ColNine},
                      {Panel::RowEight_ColOne, Panel::RGB_RowEight_ColOne},
                      {Panel::RowEight_ColTwo, Panel::RGB_RowEight_ColTwo},
                      {Panel::RowEight_ColThree, Panel::RGB_RowEight_ColThree},
                      {Panel::RowEight_ColFour, Panel::RGB_RowEight_ColFour},
                      {Panel::RowEight_ColFive, Panel::RGB_RowEight_ColFive},
                      {Panel::RowEight_ColSix, Panel::RGB_RowEight_ColSix},
                      {Panel::RowEight_ColSeven, Panel::RGB_RowEight_ColSeven},
                      {Panel::RowEight_ColEight, Panel::RGB_RowEight_ColEight},
                      {Panel::RowEight_ColNine, Panel::RGB_RowEight_ColNine},
                      {Panel::RowNine_ColOne, Panel::RGB_RowNine_ColOne},
                      {Panel::RowNine_ColTwo, Panel::RGB_RowNine_ColTwo},
                      {Panel::RowNine_ColThree, Panel::RGB_RowNine_ColThree},
                      {Panel::RowNine_ColFour, Panel::RGB_RowNine_ColFour},
                      {Panel::RowNine_ColFive, Panel::RGB_RowNine_ColFive},
                      {Panel::RowNine_ColSix, Panel::RGB_RowNine_ColSix},
                      {Panel::RowNine_ColSeven, Panel::RGB_RowNine_ColSeven},
                      {Panel::RowNine_ColEight, Panel::RGB_RowNine_ColEight}});

   indexToMidiNote = {{0, 11},
                      {1, 12},
                      {2, 13},
                      {3, 14},
                      {4, 15},
                      {5, 16},
                      {6, 17},
                      {7, 18},
                      {8, 19},
                      {9, 21},
                      {10, 22},
                      {11, 23},
                      {12, 24},
                      {13, 25},
                      {14, 26},
                      {15, 27},
                      {16, 28},
                      {17, 29},
                      {18, 31},
                      {19, 32},
                      {20, 33},
                      {21, 34},
                      {22, 35},
                      {23, 36},
                      {24, 37},
                      {25, 38},
                      {26, 39},
                      {27, 41},
                      {28, 42},
                      {29, 43},
                      {30, 44},
                      {31, 45},
                      {32, 46},
                      {33, 47},
                      {34, 48},
                      {35, 49},
                      {36, 51},
                      {37, 52},
                      {38, 53},
                      {39, 54},
                      {40, 55},
                      {41, 56},
                      {42, 57},
                      {43, 58},
                      {44, 59},
                      {45, 61},
                      {46, 62},
                      {47, 63},
                      {48, 64},
                      {49, 65},
                      {50, 66},
                      {51, 67},
                      {52, 68},
                      {53, 69},
                      {54, 71},
                      {55, 72},
                      {56, 73},
                      {57, 74},
                      {58, 75},
                      {59, 76},
                      {60, 77},
                      {61, 78},
                      {62, 79},
                      {63, 81},
                      {64, 82},
                      {65, 83},
                      {66, 84},
                      {67, 85},
                      {68, 86},
                      {69, 87},
                      {70, 88},
                      {71, 89},
                      {72, 91},
                      {73, 92},
                      {74, 93},
                      {75, 94},
                      {76, 95},
                      {77, 96},
                      {78, 97},
                      {79, 98},
                      {80, 99}};

   midiNoteToIndex = {{11, 0},
                      {12, 1},
                      {13, 2},
                      {14, 3},
                      {15, 4},
                      {16, 5},
                      {17, 6},
                      {18, 7},
                      {19, 8},
                      {21, 9},
                      {22, 10},
                      {23, 11},
                      {24, 12},
                      {25, 13},
                      {26, 14},
                      {27, 15},
                      {28, 16},
                      {29, 17},
                      {31, 18},
                      {32, 19},
                      {33, 20},
                      {34, 21},
                      {35, 22},
                      {36, 23},
                      {37, 24},
                      {38, 25},
                      {39, 26},
                      {41, 27},
                      {42, 28},
                      {43, 29},
                      {44, 30},
                      {45, 31},
                      {46, 32},
                      {47, 33},
                      {48, 34},
                      {49, 35},
                      {51, 36},
                      {52, 37},
                      {53, 38},
                      {54, 39},
                      {55, 40},
                      {56, 41},
                      {57, 42},
                      {58, 43},
                      {59, 44},
                      {61, 45},
                      {62, 46},
                      {63, 47},
                      {64, 48},
                      {65, 49},
                      {66, 50},
                      {67, 51},
                      {68, 52},
                      {69, 53},
                      {71, 54},
                      {72, 55},
                      {73, 56},
                      {74, 57},
                      {75, 58},
                      {76, 59},
                      {77, 60},
                      {78, 61},
                      {79, 62},
                      {81, 63},
                      {82, 64},
                      {83, 65},
                      {84, 66},
                      {85, 67},
                      {86, 68},
                      {87, 69},
                      {88, 70},
                      {89, 71},
                      {91, 72},
                      {92, 73},
                      {93, 74},
                      {94, 75},
                      {95, 76},
                      {96, 77},
                      {97, 78},
                      {98, 79},
                      {99, 80}};
}

void LaunchpadImposter::process(const ProcessArgs& args)
{
   Variable::Integer<uint8_t> varBank(deviceId, 0, 15, true);
   if (deviceIdUpButton.isTriggered())
      varBank.increment();
   else if (deviceIdDownButton.isTriggered())
      varBank.decrement();
}

void LaunchpadImposter::updateDisplays()
{
   static const std::vector<Color> palette = Svin::LaunchpadClient::getPalette();

   deviceIdDisplay.setText(Text::pad(std::to_string(deviceId + 1), 2));

   const bool even = (0 == (deviceId % 2));
   uint8_t colorIndex = even ? 0 : 64;
   for (uint8_t row = 0; row < 8; row++)
   {
      for (uint8_t column = 0; column < 8; column++)
      {
         const uint8_t buttonIndex = (9 * (7 - row)) + column;
         buttonList[buttonIndex]->setColor(palette.at(colorIndex));

         colorIndex++;
      }
   }
}

void LaunchpadImposter::load(const Svin::Json::Object& rootObject)
{
   deviceId = rootObject.get("deviceId").toInt();
}

void LaunchpadImposter::save(Svin::Json::Object& rootObject)
{
   rootObject.set("deviceId", deviceId);
}

// widget

LaunchpadImposterWidget::LaunchpadImposterWidget(LaunchpadImposter* module)
: Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelLaunchpadImposter = Svin::Origin::the()->addModule<LaunchpadImposter, LaunchpadImposterWidget>("LaunchpadImposter");

