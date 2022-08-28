#ifndef SvinUiElementHPP
#define SvinUiElementHPP

#include "SvinUiElement.h"

// view

template <typename ControllerType>
Svin::UiElement::View<ControllerType>::View(Module* module, const uint16_t controllerId)
   : module(module)
   , controllerId(controllerId)
{
}

template <typename ControllerType>
ControllerType* Svin::UiElement::View<ControllerType>::findController() const
{
   if (ControllerType::controllerMap.find(module) == ControllerType::controllerMap.end())
      return nullptr;

   const typename ControllerType::IdMap& idMap = ControllerType::controllerMap.at(module);
   if (idMap.find(controllerId) == idMap.end())
      return nullptr;

   return idMap.at(controllerId);
}

// base

template <typename ControllerType>
typename Svin::UiElement::Controller<ControllerType>::ControllerMap Svin::UiElement::Controller<ControllerType>::controllerMap;

template <typename ControllerType>
Svin::UiElement::Controller<ControllerType>::Controller(Module* module, const uint16_t controllerId, ControllerType* controller)
   : module(module)
   , controllerId(controllerId)
{
   controllerMap[module][controllerId] = controller;
}

template <typename ControllerType>
Svin::UiElement::Controller<ControllerType>::~Controller()
{
   controllerMap[module][controllerId] = nullptr;
}

#endif // NOT SvinUiElementHPP
