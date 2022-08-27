#ifndef SvinMasterHPP
#define SvinMasterHPP

#include "SvinMaster.h"

template <typename AudioClass, typename WidgetClass>
Model* Svin::Master::addModule(const std::string& name)
{
   Model* model = createModel<AudioClass, WidgetClass>(name);
   modelList.push_back(model);
   return model;
}
#endif // NOT SvinMasterHPP
