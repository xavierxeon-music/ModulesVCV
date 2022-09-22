#ifndef BitBusCommonH
#define BitBusCommonH

#include <MusicTools.h>

namespace BitBus
{
   struct Message
   {
      uint8_t byte[16];
      uint8_t channelCount;

      Message();
      Message(const Message& other);
      Message& operator=(const Message& other);
   };
} // namespace BitBus

#endif // NOT BitBusCommonH
