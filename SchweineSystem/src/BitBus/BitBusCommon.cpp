#include "BitBusCommon.h"

BitBus::Message::Message()
   : byte{}
   , channelCount(1)
{
}

BitBus::Message::Message(const Message& other)
   : Message()
{
   *this = other;
}

BitBus::Message& BitBus::Message::operator=(const Message& other)
{
   for (uint8_t channel = 0; channel < 16; channel++)
      byte[channel] = other.byte[channel];

   channelCount = other.channelCount;
   return *this;
}
