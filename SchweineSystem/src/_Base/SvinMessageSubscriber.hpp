#ifndef SvinMessageSubscriberHPP
#define SvinMessageSubscriberHPP

#include "SvinMessageSubscriber.h"

template <typename MessageType>
Svin::Message<MessageType>::Subscriber::Subscriber(Module* module)
   : module(module)
{
}

#endif // NOT SvinMessageSubscriberHPP
