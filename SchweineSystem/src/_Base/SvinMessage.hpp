#ifndef SvinMessageHPP
#define SvinMessageHPP

#include "SvinMessage.h"

template <typename MessageType>
Svin::Message<MessageType>::Message()
   : publisherList()
   , subscriberList()
{
}

#endif // NOT SvinMessageHPP
