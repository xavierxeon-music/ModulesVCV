#ifndef BitBusCommonH
#define BitBusCommonH

#include <MusicTools.h>

struct BitBusMessage
{
   uint8_t byte[16];
   uint8_t channelCount = 1;
};

#endif // NOT BitBusCommonH
