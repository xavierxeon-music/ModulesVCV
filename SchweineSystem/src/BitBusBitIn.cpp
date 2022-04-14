#include "BitBusBitIn.h"
#include "BitBusBitInPanel.h"

#include "SchweineSystem.h"

BitBusBitIn::BitBusBitIn()
   : Module()
{
   setup();
}

BitBusBitIn::~BitBusBitIn()
{
}

void BitBusBitIn::process(const ProcessArgs& args)
{
}

Model* modelBitBusBitIn = SchweineSystem::the()->addModule<BitBusBitIn, BitBusBitInWidget>("BitBusBitIn", SchweineSystem::Series::None);

