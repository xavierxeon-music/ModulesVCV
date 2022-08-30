#ifndef SvinDisplayOLEDHPP
#define SvinDisplayOLEDHPP

#include "SvinDisplayOLED.h"

template <typename ClassType>
void Svin::DisplayOLED::Controller::onClicked(ClassType* instance, void (ClassType::*functionPointer)(const float&, const float&))
{
   ClickedFunction clickedFunction = std::bind(functionPointer, instance, std::placeholders::_1, std::placeholders::_2);
   clickedFunctionList.push_back(clickedFunction);
}

template <typename ClassType>
void Svin::DisplayOLED::Controller::onClickedOpenFileFunction(ClassType* instance, void (ClassType::*functionPointer)(const std::string& fileName), const std::string& filter)
{
   OpenFile::Function fileFunction = std::bind(functionPointer, instance, std::placeholders::_1);
   openFileList.push_back({fileFunction, filter});
}

#endif // NOT SvinDisplayOLEDHPP
