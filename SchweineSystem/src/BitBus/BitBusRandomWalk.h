#ifndef BitBusRandomWalkH
#define BitBusRandomWalkH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SvinExapnder.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButton.h>
#include <SvinDisplayLCD.h>
#include <SvinInput.h>
#include <SvinLED.h>
#include <SvinSlider.h>

#include <Tools/Range.h>

class BitBusRandomWalk : public Svin::Module, public Svin::Exapnder<BitBusMessage>
{
public:
   struct Panel;

public:
   BitBusRandomWalk();

public:
   void process(const ProcessArgs& args) override;

private:
   static constexpr uint16_t seedCount = 256;

private:
   void setup();

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   Svin::LED busInIndicator;
   Svin::LED busOutIndicator;

   Svin::Slider mixSlider;
   Svin::Button upButton;
   Svin::Button downButton;
   Svin::DisplayLCD::Controller displayController;
   Svin::Input scanInput;
   Range::Mapper scanMapper;

   float mix;
   uint8_t seed;
   uint8_t tables[seedCount][256]; // seed, index
};

// widget

class BitBusRandomWalkWidget : public Svin::ModuleWidget
{
public:
   BitBusRandomWalkWidget(BitBusRandomWalk* module);

private:
   void setup();
};

#endif // NOT BitBusRandomWalkH