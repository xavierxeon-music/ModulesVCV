#ifndef SvinModuleHPP
#define SvinModuleHPP

#include "SvinModule.h"

// bus
template <typename MessageType>
typename Svin::Module::Bus<MessageType>* Svin::Module::Bus<MessageType>::me = nullptr;

template <typename MessageType>
Svin::Module::Bus<MessageType>::Bus()
   : BusAbstract()
{
   busList.push_back(this);
}

template <typename MessageType>
Svin::Module::Bus<MessageType>* Svin::Module::Bus<MessageType>::the()
{
   if (!me)
      me = new Bus<MessageType>();

   return me;
}

template <typename MessageType>
void Svin::Module::Bus<MessageType>::append(Module* module)
{
   instanceList.push_back(module);
}

template <typename MessageType>
bool Svin::Module::Bus<MessageType>::contains(Module* module)
{
   if (std::find(instanceList.cbegin(), instanceList.cend(), module) == instanceList.cend())
      return false;

   return true;
}

template <typename MessageType>
void Svin::Module::Bus<MessageType>::removeModule(Module* module)
{
   instanceList.remove(module);
}

// module

template <typename MessageType>
void Svin::Module::registerAsBusModule()
{
   Bus<MessageType>::the()->append(this);

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

   if (!Bus<MessageType>::the()->contains(module))
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
