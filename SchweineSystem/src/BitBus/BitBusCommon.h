#ifndef BitBusCommonH
#define BitBusCommonH

#include <MusicTools.h>

struct BitBusMessage
{
   uint8_t byte[16];
   uint8_t channelCount;

   BitBusMessage();
   BitBusMessage(const BitBusMessage& other);
   BitBusMessage& operator=(const BitBusMessage& other);
};

#endif // NOT BitBusCommonH
