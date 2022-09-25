#ifndef BitBusCommonH
#define BitBusCommonH

#include <MusicTools.h>

namespace BitBus
{
   struct Data
   {
      uint8_t byte[16];
      uint8_t channelCount;

      Data();
      Data(const Data& other);
      Data& operator=(const Data& other);
   };
} // namespace BitBus

#endif // NOT BitBusCommonH
