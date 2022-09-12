#include "BitBusCommon.h"

BitBusMessage::BitBusMessage()
   : byte{}
   , channelCount(1)
{
}

BitBusMessage::BitBusMessage(const BitBusMessage& other)
   : BitBusMessage()
{
   *this = other;
}

BitBusMessage& BitBusMessage::operator=(const BitBusMessage& other)
{
   for (uint8_t channel = 0; channel < 16; channel++)
      byte[channel] = other.byte[channel];

   channelCount = other.channelCount;
   return *this;
}
