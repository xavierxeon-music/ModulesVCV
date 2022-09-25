#include "BitBusCommon.h"

BitBus::Data::Data()
   : byte{}
   , channelCount(1)
{
}

BitBus::Data::Data(const Data& other)
   : Data()
{
   *this = other;
}

BitBus::Data& BitBus::Data::operator=(const Data& other)
{
   for (uint8_t channel = 0; channel < 16; channel++)
      byte[channel] = other.byte[channel];

   channelCount = other.channelCount;
   return *this;
}
