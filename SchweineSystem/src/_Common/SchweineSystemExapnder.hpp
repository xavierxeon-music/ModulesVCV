#ifndef SchweineSystemExapnderHPP
#define SchweineSystemExapnderHPP

#include "SchweineSystemExapnder.h"

template <typename MessageType>
typename SchweineSystem::Exapnder<MessageType>::InstanceList SchweineSystem::Exapnder<MessageType>::instanceList;

template <typename MessageType>
SchweineSystem::Exapnder<MessageType>::Exapnder(Module* module)
   : module(module)
{
   instanceList.push_back(module);

   module->leftExpander.producerMessage = new MessageType{};
   module->leftExpander.consumerMessage = new MessageType{};

   module->rightExpander.producerMessage = new MessageType{};
   module->rightExpander.consumerMessage = new MessageType{};
}

template <typename MessageType>
SchweineSystem::Exapnder<MessageType>::~Exapnder()
{
   instanceList.remove(module);

   auto cleanUp = [&](Module::Expander& expander)
   {
      MessageType* busMessageProducer = reinterpret_cast<MessageType*>(expander.producerMessage);
      delete busMessageProducer;
      expander.producerMessage = nullptr;

      MessageType* busMessageConsumer = reinterpret_cast<MessageType*>(expander.consumerMessage);
      delete busMessageConsumer;
      expander.consumerMessage = nullptr;
   };

   cleanUp(module->leftExpander);
   cleanUp(module->rightExpander);
}

template <typename MessageType>
bool SchweineSystem::Exapnder<MessageType>::hasExpanderToLeft()
{
   rack::Module* expanderModule = module->leftExpander.module;

   InstanceList::const_iterator it = std::find(instanceList.cbegin(), instanceList.cend(), expanderModule);
   return (it != instanceList.cend());
}

template <typename MessageType>
bool SchweineSystem::Exapnder<MessageType>::hasExpanderToRight()
{
   rack::Module* expanderModule = module->rightExpander.module;

   InstanceList::const_iterator it = std::find(instanceList.cbegin(), instanceList.cend(), expanderModule);
   return (it != instanceList.cend());
}

template <typename MessageType>
void SchweineSystem::Exapnder<MessageType>::sendToLeft(const MessageType& message)
{
   if (!hasExpanderToLeft())
      return;

   rack::Module* expanderModule = module->leftExpander.module;
   Module::Expander& target = expanderModule->rightExpander;

   MessageType* busMessage = reinterpret_cast<MessageType*>(target.producerMessage);
   *busMessage = message;

   target.requestMessageFlip();
}

template <typename MessageType>
void SchweineSystem::Exapnder<MessageType>::sendToRight(const MessageType& message)
{
   if (!hasExpanderToRight())
      return;

   rack::Module* expanderModule = module->rightExpander.module;
   Module::Expander& target = expanderModule->leftExpander;

   MessageType* busMessage = reinterpret_cast<MessageType*>(target.producerMessage);
   *busMessage = message;

   target.requestMessageFlip();
}

template <typename MessageType>
MessageType SchweineSystem::Exapnder<MessageType>::receiveFromLeft()
{
   if (!hasExpanderToLeft())
      return MessageType{};

   Module::Expander& source = module->leftExpander;

   MessageType* busMessage = reinterpret_cast<MessageType*>(source.consumerMessage);
   return *busMessage;
}

template <typename MessageType>
MessageType SchweineSystem::Exapnder<MessageType>::receiveFromRight()
{
   if (!hasExpanderToRight())
      return MessageType{};

   Module::Expander& source = module->rightExpander;

   MessageType* busMessage = reinterpret_cast<MessageType*>(source.consumerMessage);
   return *busMessage;
}

#endif // NOT SchweineSystemExapnderHPP
