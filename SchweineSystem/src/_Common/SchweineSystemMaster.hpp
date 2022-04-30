#ifndef SchweineSystemMasterHPP
#define SchweineSystemMasterHPP

#include "SchweineSystemMaster.h"

template <typename AudioClass, typename WidgetClass>
Model* SchweineSystem::Master::addModule(const std::string& name)
{
   Model* model = createModel<AudioClass, WidgetClass>(name);
   modelList.push_back(model);
   return model;
}
#endif // NOT SchweineSystemMasterHPP
