#ifndef SchweineSystemExapnderHPP
#define SchweineSystemExapnderHPP

#include "SchweineSystemExapnder.h"

template <typename MessageType>
typename SchweineSystem::Exapnder<MessageType>::InstanceMap SchweineSystem::Exapnder<MessageType>::instanceMap;

template <typename MessageType>
SchweineSystem::Exapnder<MessageType>::Exapnder(Module* module)
   : module(module)
{
   instanceMap[module] = Direction{};

   module->leftExpander.producerMessage = new MessageType{};
   module->leftExpander.consumerMessage = new MessageType{};

   module->rightExpander.producerMessage = new MessageType{};
   module->rightExpander.consumerMessage = new MessageType{};
}

template <typename MessageType>
SchweineSystem::Exapnder<MessageType>::~Exapnder()
{
   instanceMap.erase(module);

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
void SchweineSystem::Exapnder<MessageType>::allowExpanderOnLeft()
{
   instanceMap[module].left = true;
}

template <typename MessageType>
void SchweineSystem::Exapnder<MessageType>::allowExpanderOnRight()
{
   instanceMap[module].right = true;
}

template <typename MessageType>
bool SchweineSystem::Exapnder<MessageType>::canCommunicatWithLeft()
{
   if (!instanceMap[module].left)
      return false;

   rack::Module* expanderModule = module->leftExpander.module;
   if (!expanderModule)
      return false;

   typename InstanceMap::const_iterator itOther = instanceMap.find(expanderModule);
   if (itOther == instanceMap.cend())
      return false;

   return itOther->second.right;
}

template <typename MessageType>
bool SchweineSystem::Exapnder<MessageType>::canCommunicatWithRight()
{
   if (!instanceMap[module].right)
      return false;

   rack::Module* expanderModule = module->rightExpander.module;
   if (!expanderModule)
      return false;

   typename InstanceMap::const_iterator itOther = instanceMap.find(expanderModule);
   if (itOther == instanceMap.cend())
      return false;

   return itOther->second.left;
}

template <typename MessageType>
void SchweineSystem::Exapnder<MessageType>::sendToLeft(const MessageType& message)
{
   if (!canCommunicatWithLeft())
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
   if (!canCommunicatWithRight())
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
   if (!canCommunicatWithLeft())
      return MessageType{};

   Module::Expander& source = module->leftExpander;

   MessageType* busMessage = reinterpret_cast<MessageType*>(source.consumerMessage);
   return *busMessage;
}

template <typename MessageType>
MessageType SchweineSystem::Exapnder<MessageType>::receiveFromRight()
{
   if (!canCommunicatWithRight())
      return MessageType{};

   Module::Expander& source = module->rightExpander;

   MessageType* busMessage = reinterpret_cast<MessageType*>(source.consumerMessage);
   return *busMessage;
}

#endif // NOT SchweineSystemExapnderHPP
