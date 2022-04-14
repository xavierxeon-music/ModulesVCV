#ifndef SchweineSystemHPP
#define SchweineSystemHPP

#include "SchweineSystem.h"

template <typename AudioClass, typename WidgetClass>
Model* SchweineSystem::addModule(const std::string& name, const Series series)
{
   Model* model = createModel<AudioClass, WidgetClass>(name);
   modelMap[series].push_back(model);
   return model;
}

#endif // NOT SchweineSystemHPP
