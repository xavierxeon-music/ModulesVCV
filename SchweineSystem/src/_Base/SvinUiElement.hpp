#ifndef SvinUiElementHPP
#define SvinUiElementHPP

#include "SvinUiElement.h"

// view

template <typename ControllerType>
Svin::UiElement::View<ControllerType>::View(Module* module, const uint16_t identifier)
   : Base{module, identifier}
{
}

template <typename ControllerType>
ControllerType* Svin::UiElement::View<ControllerType>::findController() const
{
   if (ControllerType::controllerMap.find(module) == ControllerType::controllerMap.end())
      return nullptr;

   const typename ControllerType::IdMap& idMap = ControllerType::controllerMap.at(module);
   if (idMap.find(identifier) == idMap.end())
      return nullptr;

   return idMap.at(identifier);
}

// base

template <typename ControllerType>
typename Svin::UiElement::Controller<ControllerType>::ControllerMap Svin::UiElement::Controller<ControllerType>::controllerMap;

template <typename ControllerType>
Svin::UiElement::Controller<ControllerType>::Controller(Module* module, const uint16_t identifier, ControllerType* controller)
   : Base{module, identifier}
{
   controllerMap[module][identifier] = controller;
}

template <typename ControllerType>
Svin::UiElement::Controller<ControllerType>::~Controller()
{
   controllerMap[module][identifier] = nullptr;
}

#endif // NOT SvinUiElementHPP
