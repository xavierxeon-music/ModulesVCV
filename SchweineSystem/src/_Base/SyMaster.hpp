#ifndef SyMasterHPP
#define SyMasterHPP

#include "SyMaster.h"

template <typename AudioClass, typename WidgetClass>
Model* Sy::Master::addModule(const std::string& name)
{
   Model* model = createModel<AudioClass, WidgetClass>(name);
   modelList.push_back(model);
   return model;
}
#endif // NOT SyMasterHPP
