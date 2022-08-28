#ifndef SvinDisplayOLEDHPP
#define SvinDisplayOLEDHPP

#include "SvinDisplayOLED.h"

template <typename ClassType>
void Svin::DisplayOLED::Controller::onClicked(ClassType* instance, void (ClassType::*functionPointer)(const float&, const float&))
{
   ClickedFunction clickedFunction = std::bind(functionPointer, instance, std::placeholders::_1, std::placeholders::_2);
   clickedFunctionList.push_back(clickedFunction);
}

#endif // NOT SvinDisplayOLEDHPP
