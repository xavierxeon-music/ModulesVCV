#ifndef SvinUiElementHPP
#define SvinUiElementHPP

#include "SvinUiElement.h"

// access

template <typename ContentType>
Svin::UiElement::ElementMap<ContentType>::Access::Access(Module* module, const uint16_t identifier)
   : Base{module, identifier}
{
}

template <typename ContentType>
ContentType* Svin::UiElement::ElementMap<ContentType>::Access::findElement() const
{
   if (ContentType::instances.find(module) == ContentType::instances.end())
      return nullptr;

   const typename ContentType::IdMap& idMap = ContentType::instances.at(module);
   if (idMap.find(identifier) == idMap.end())
      return nullptr;

   return idMap.at(identifier);
}

// element map

template <typename ControllerType>
typename Svin::UiElement::ElementMap<ControllerType>::ContentMap Svin::UiElement::ElementMap<ControllerType>::instances;

template <typename ControllerType>
Svin::UiElement::ElementMap<ControllerType>::ElementMap(Module* module, const uint16_t identifier, ControllerType* controller)
   : Base{module, identifier}
{
   instances[module][identifier] = controller;
}

template <typename ControllerType>
Svin::UiElement::ElementMap<ControllerType>::~ElementMap()
{
   instances[module][identifier] = nullptr;
}

#endif // NOT SvinUiElementHPP
