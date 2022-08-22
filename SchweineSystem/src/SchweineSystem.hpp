#ifndef SyHPP
#define SyHPP

#include "SyMaster.h"

template <typename AudioClass, typename WidgetClass>
Model* Sy::addModule(const std::string& name)
{
   Model* model = createModel<AudioClass, WidgetClass>(name);
   modelList.push_back(model);
   return model;
}

#endif // NOT SyHPP
