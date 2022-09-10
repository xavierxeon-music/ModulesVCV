#ifndef BitBusRandomWalkH
#define BitBusRandomWalkH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SvinButton.h>
#include <SvinDisplayLCD.h>
#include <SvinExapnder.h>
#include <SvinLED.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <Sound/WaveTable.h>

class BitBusRandomWalk : public Svin::Module, public Svin::Exapnder<BitBusMessage>
{
public:
   struct Panel;

public:
   BitBusTransmutorBitBusRandomWalk();

public:
   void process(const ProcessArgs& args) override;

private:
   static constexpr uint16_t seedCount = 256;

private:
   void setup();

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   Svin::Button upButton;
   Svin::Button downButton;
   Svin::DisplayLCD::Controller displayController;

   Svin::LED busInIndicator;
   Svin::LED busOutIndicator;

   uint8_t seed;
   uint8_t tables[seedCount][256]; // seed, index
};

// widget

class BitBusRandomWalkWidget : public Svin::ModuleWidget
{
public:
   BitBusTransmutorWidget(BitBusRandomWalk* module);

private:
   void setup();
};

#endif BitBusRandomWalkH
