#ifndef SvinMessageSubscriberHPP
#define SvinMessageSubscriberHPP

#include "SvinMessageSubscriber.h"

template <typename MessageType>
Svin::Message<MessageType>::Subscriber::Subscriber(Module* module)
   : module(module)
   , stackList()
   , mutex()
{
   Message<MessageType>::broker()->subscriberList.push_back(this);
}

template <typename MessageType>
Svin::Message<MessageType>::Subscriber::~Subscriber()
{
   Message<MessageType>::broker()->subscriberList.remove(this);
}

template <typename MessageType>
void Svin::Message<MessageType>::Subscriber::processMessageBuffer()
{
   std::lock_guard<std::mutex> guard(mutex);

   for (const Stack& stack : stackList)
      receiveMessage(stack.message, stack.sender);

   stackList.clear();
}

template <typename MessageType>
void Svin::Message<MessageType>::Subscriber::queue(const MessageType& message, Module* sender)
{
   std::lock_guard<std::mutex> guard(mutex);

   stackList.push_back({message, sender});
}

#endif // NOT SvinMessageSubscriberHPP
