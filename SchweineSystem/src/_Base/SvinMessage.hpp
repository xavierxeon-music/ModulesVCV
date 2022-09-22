#ifndef SvinMessageHPP
#define SvinMessageHPP

#include "SvinMessage.h"

template <typename MessageType>
Svin::Message<MessageType>::Message()
   : subscriberList()
{
}

template <typename MessageType>
Svin::Message<MessageType>* Svin::Message<MessageType>::broker()
{
   static Message<MessageType>* me = new Message<MessageType>();
   return me;
}

#endif // NOT SvinMessageHPP
