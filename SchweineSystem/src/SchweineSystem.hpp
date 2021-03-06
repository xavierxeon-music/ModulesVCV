#ifndef SchweineSystemHPP
#define SchweineSystemHPP

#include "SchweineSystemMaster.h"

template <typename AudioClass, typename WidgetClass>
Model* SchweineSystem::addModule(const std::string& name)
{
   Model* model = createModel<AudioClass, WidgetClass>(name);
   modelList.push_back(model);
   return model;
}

#endif // NOT SchweineSystemHPP
