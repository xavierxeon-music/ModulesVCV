#ifndef SvinOriginHPP
#define SvinOriginHPP

#include "SvinOrigin.h"

template <typename AudioClass, typename WidgetClass>
Model* Svin::Origin::addModule(const std::string& name)
{
   Model* model = createModel<AudioClass, WidgetClass>(name);
   modelList.push_back(model);
   return model;
}
#endif // NOT SvinOriginHPP
