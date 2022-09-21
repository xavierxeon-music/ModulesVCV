#ifndef SvinModuleHPP
#define SvinModuleHPP

#include "SvinModule.h"

template <typename MessageType>
typename Svin::Module::BusManager<MessageType>::InstanceList Svin::Module::BusManager<MessageType>::instanceList;

template <typename MessageType>
void Svin::Module::resisterAsBusModule()
{
   BusManager<MessageType>::instanceList.append(this);

   leftExpander.producerMessage = new MessageType{};
   leftExpander.consumerMessage = new MessageType{};

   rightExpander.producerMessage = new MessageType{};
   rightExpander.consumerMessage = new MessageType{};
}

template <typename MessageType>
Svin::Module* Svin::Module::busModule(const Side& side) const
{
   rack::Module* expanderModule = (Side::Left == side) ? expanderModule = leftExpander.module : expanderModule = rightExpander.module;
   if (!expanderModule)
      return nullptr;

   Module* module = dynamic_cast<Module*>(expanderModule);
   if (!module)
      return nullptr;

   const auto& list = BusManager<MessageType>::instanceList;
   if (list.find(module) == list.cend())
      return nullptr;

   return module;
}

template <typename MessageType>
void Svin::Module::sendBusMessage(const Side& side, const MessageType& message)
{
   if (!busModule<MessageType>(side))
      return;

   Module::Expander& target = (Side::Left == side) ? leftExpander.module->rightExpander : rightExpander.module->leftExpander;
   MessageType* busMessage = reinterpret_cast<MessageType*>(target.producerMessage);
   *busMessage = message;

   target.requestMessageFlip();
}

template <typename MessageType>
MessageType Svin::Module::getBusMessage(const Side& side)
{
   if (!busModule<MessageType>(side))
      return MessageType{};

   Module::Expander& source = (Side::Left == side) ? leftExpander : rightExpander;
   MessageType* busMessage = reinterpret_cast<MessageType*>(source.consumerMessage);

   return *busMessage;
}

#endif // NOT SvinModuleHPP
