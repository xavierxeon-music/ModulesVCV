#include "SvinOrigin.h"

Svin::Origin::Origin()
   : pluginInstance(nullptr)
   , modelList()
{
}

Svin::Origin* Svin::Origin::the()
{
   static Origin* theOnlyOne = new Origin();
   return theOnlyOne;
}

Plugin* Svin::Origin::instance()
{
   return pluginInstance;
}

// the "main" function
void init(Plugin* pluginInstance)
{
   Svin::Origin* origin = Svin::Origin::the();
   origin->pluginInstance = pluginInstance;

   using ModelList = Svin::Origin::ModelList;
   const ModelList& modelList = origin->modelList;

   for (Model* model : modelList)
      pluginInstance->addModel(model);
}
