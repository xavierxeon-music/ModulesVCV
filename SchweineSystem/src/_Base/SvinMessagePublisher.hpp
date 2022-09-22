#ifndef SvinMessagePublisherHPP
#define SvinMessagePublisherHPP

#include "SvinMessagePublisher.h"

#include "SvinMessageSubscriber.h"

template <typename MessageType>
Svin::Message<MessageType>::Publisher::Publisher(Module* module)
   : module(module)
{
}

template <typename MessageType>
void Svin::Message<MessageType>::Publisher::publishMessage(const MessageType& message, Module* receiver)
{
   for (typename Message<MessageType>::Subscriber* subscriber : Message<MessageType>::broker()->subscriberList)
   {
      if (receiver && subscriber->module != receiver)
         continue;

      subscriber->queue(message, module);
   }
}

#endif // NOT SvinMessagePublisherHPP
