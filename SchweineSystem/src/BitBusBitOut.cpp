#include "BitBusBitOut.h"
#include "BitBusBitOutPanel.h"

#include "SchweineSystem.h"

BitBusBitOut::BitBusBitOut()
   : Module()
{
   setup();
}

BitBusBitOut::~BitBusBitOut()
{
}

void BitBusBitOut::process(const ProcessArgs& args)
{
}

Model* modelBitBusBitOut = SchweineSystem::the()->addModule<BitBusBitOut, BitBusBitOutWidget>("BitBusBitOut", SchweineSystem::Series::None);

