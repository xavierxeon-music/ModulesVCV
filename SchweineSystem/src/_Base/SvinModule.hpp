#ifndef SvinModuleHPP
#define SvinModuleHPP

#include "SvinModule.h"

// bus

template <typename DataType>
typename Svin::Module::Bus<DataType>* Svin::Module::Bus<DataType>::me = nullptr;

template <typename DataType>
Svin::Module::Bus<DataType>::Bus()
   : BusAbstract()
   , mutex()
{
   busList.push_back(this);
}

template <typename DataType>
Svin::Module::Bus<DataType>* Svin::Module::Bus<DataType>::the()
{
   if (!me)
      me = new Bus<DataType>();

   return me;
}

template <typename DataType>
void Svin::Module::Bus<DataType>::append(Module* module)
{
   instanceMap[module] = typename Message<DataType>::List();
}

template <typename DataType>
bool Svin::Module::Bus<DataType>::contains(Module* module)
{
   if (instanceMap.find(module) == instanceMap.cend())
      return false;

   return true;
}

template <typename DataType>
void Svin::Module::Bus<DataType>::queue(const DataType& data, const Json::Object& document, const Module* sender, const Module* target)
{
   std::lock_guard<std::mutex> guard(mutex);

   Message<DataType> buffer = {data, document, sender};

   for (typename InstanceMap::iterator it = instanceMap.begin(); it != instanceMap.end(); it++)
   {
      Module* receiver = it->first;

      if (receiver == sender)
         continue;

      if (target && (target != receiver))
         continue;

      it->second.push_back(buffer);
   }
}

template <typename DataType>
bool Svin::Module::Bus<DataType>::empty(Module* module) const
{
   std::lock_guard<std::mutex> guard(mutex);

   if (instanceMap.find(module) == instanceMap.cend())
      return true;

   return instanceMap.at(module).empty();
}

template <typename DataType>
Svin::Module::Message<DataType> Svin::Module::Bus<DataType>::takeFirst(Module* module)
{
   std::lock_guard<std::mutex> guard(mutex);

   typename Message<DataType>::List& messageList = instanceMap[module];

   const Message<DataType> message = messageList.front();
   messageList.pop_front();

   return message;
}

template <typename DataType>
void Svin::Module::Bus<DataType>::removeModule(Module* module)
{
   instanceMap.erase(module);
}

// module

template <typename DataType>
Svin::Module* Svin::Module::busModule(const Side& side) const
{
   rack::Module* expanderModule = (Side::Left == side) ? leftExpander.module : rightExpander.module;
   if (!expanderModule)
      return nullptr;

   Module* module = dynamic_cast<Module*>(expanderModule);
   if (!module)
      return nullptr;

   if (!Bus<DataType>::the()->contains(module))
      return nullptr;

   return module;
}

template <typename DataType>
void Svin::Module::registerAsBusModule()
{
   Bus<DataType>::the()->append(this);

   leftExpander.producerMessage = new DataType{};
   leftExpander.consumerMessage = new DataType{};

   rightExpander.producerMessage = new DataType{};
   rightExpander.consumerMessage = new DataType{};
}

template <typename DataType>
void Svin::Module::sendBusData(const Side& side, const DataType& data)
{
   if (!busModule<DataType>(side))
      return;

   Module::Expander& target = (Side::Left == side) ? leftExpander.module->rightExpander : rightExpander.module->leftExpander;
   DataType* busData = reinterpret_cast<DataType*>(target.producerMessage);
   *busData = data;

   target.requestMessageFlip();
}

template <typename DataType>
DataType Svin::Module::getBusData(const Side& side)
{
   if (!busModule<DataType>(side))
      return DataType{};

   Module::Expander& source = (Side::Left == side) ? leftExpander : rightExpander;
   DataType* busData = reinterpret_cast<DataType*>(source.consumerMessage);

   if (!busData)
      return DataType{};

   return *busData;
}

template <typename DataType>
uint8_t Svin::Module::indexOfBusModule(const Side& side, Module* module)
{
   if (!module)
      return 0;

   uint8_t counter = 0;
   for (Module* searchModule = busModule<DataType>(side); searchModule != nullptr; searchModule = searchModule->busModule<DataType>(side))
   {
      counter++;
      if (searchModule == module)
         return counter;
   }

   return 0;
}

template <typename DataType, typename ModuleType>
ModuleType* Svin::Module::findFirstBusModule(const Side& side)
{
   for (Module* module = busModule<DataType>(side); module != nullptr; module = module->busModule<DataType>(side))
   {
      ModuleType* targetModule = dynamic_cast<ModuleType*>(module);
      if (targetModule)
         return targetModule;
   }

   return nullptr;
}

template <typename DataType, typename ModuleType>
ModuleType* Svin::Module::findLastBusModule(const Side& side, bool consecutive)
{
   ModuleType* foundModule = nullptr;
   for (Module* module = busModule<DataType>(side); module != nullptr; module = module->busModule<DataType>(side))
   {
      ModuleType* targetModule = dynamic_cast<ModuleType*>(module);
      if (targetModule)
         foundModule = targetModule;
      else if (foundModule && consecutive)
         break;
   }

   return foundModule;
}

template <typename DataType>
void Svin::Module::broadcastMessage(const DataType& data, const Json::Object& document, const Module* target)
{
   const Module* sender = const_cast<const Module*>(this);
   Bus<DataType>::the()->queue(data, document, sender, target);
}

template <typename DataType>
bool Svin::Module::hasMessage()
{
   return !Bus<DataType>::the()->empty(this);
}

template <typename DataType>
Svin::Module::Message<DataType> Svin::Module::popMessage()
{
   return Bus<DataType>::the()->takeFirst(this);
}

#endif // NOT SvinModuleHPP
