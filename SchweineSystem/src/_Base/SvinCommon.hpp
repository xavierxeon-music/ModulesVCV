#ifndef SvinCommonHPP
#define SvinCommonHPP

#include "SvinCommon.h"

// ElementList

template <typename ElementType>
Svin::ElementList<ElementType>::ElementList(Module* module)
   : module(module)
   , instanceList()
{
}

template <typename ElementType>
Svin::ElementList<ElementType>::~ElementList()
{
   for (ElementType* element : instanceList)
      delete element;
   instanceList.clear();
}

template <typename ElementType>
void Svin::ElementList<ElementType>::append(const std::vector<uint16_t>& paramIndexList)
{
   for (const uint16_t paramIndex : paramIndexList)
   {
      ElementType* element = new ElementType(module, paramIndex);
      instanceList.push_back(element);
   }
}

template <typename ElementType>
void Svin::ElementList<ElementType>::append(const typename Params::List& paramsList)
{
   for (const Params& params : paramsList)
   {
      ElementType* element = new ElementType(module, params.paramA, params.paramB);
      instanceList.push_back(element);
   }
}

template <typename ElementType>
ElementType* Svin::ElementList<ElementType>::operator[](const uint16_t& index)
{
   return instanceList[index];
}

// InstanceMap::Access

template <typename ContentType>
Svin::InstanceMap<ContentType>::Access::Access(Module* module, const uint16_t identifier)
   : Base{module, identifier}
{
}

template <typename ContentType>
ContentType* Svin::InstanceMap<ContentType>::Access::findIntstance() const
{
   if (ContentType::instances.find(module) == ContentType::instances.end())
      return nullptr;

   const typename ContentType::IdMap& idMap = ContentType::instances.at(module);
   if (idMap.find(identifier) == idMap.end())
      return nullptr;

   ContentType* instance = idMap.at(identifier);
   return instance;
}

// InstanceMap

template <typename ControllerType>
typename Svin::InstanceMap<ControllerType>::ContentMap Svin::InstanceMap<ControllerType>::instances;

template <typename ControllerType>
Svin::InstanceMap<ControllerType>::InstanceMap(Module* module, const uint16_t identifier, ControllerType* controller)
   : Base{module, identifier}
{
   instances[module][identifier] = controller;
}

template <typename ControllerType>
Svin::InstanceMap<ControllerType>::~InstanceMap()
{
   instances[module][identifier] = nullptr;
}

#endif // NOT SvinCommonHPP
