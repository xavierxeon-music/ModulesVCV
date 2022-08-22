#include "SyMaster.h"

Sy::Sy()
   : pluginInstance(nullptr)
   , modelList()
{
}

Sy* Sy::Master::the()
{
   static Sy* theOnlyOne = new Sy();
   return theOnlyOne;
}

Plugin* Sy::instance()
{
   return pluginInstance;
}

// the "main" function
void init(Plugin* pluginInstance)
{
   Sy::Master::the()->pluginInstance = pluginInstance;

   using ModelList = Sy::ModelList;
   const ModelList& modelList = Sy::Master::the()->modelList;

   for (Model* model : modelList)
      pluginInstance->addModel(model);
}
