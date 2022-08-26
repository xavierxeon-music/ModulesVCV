#include "SyMaster.h"

Sy::Master::Master()
   : pluginInstance(nullptr)
   , modelList()
{
}

Sy::Master* Sy::Master::the()
{
   static Master* theOnlyOne = new Master();
   return theOnlyOne;
}

Plugin* Sy::Master::instance()
{
   return pluginInstance;
}

// the "main" function
void init(Plugin* pluginInstance)
{
   Sy::Master* master = Sy::Master::the();
   master->pluginInstance = pluginInstance;

   using ModelList = Sy::Master::ModelList;
   const ModelList& modelList = master->modelList;

   for (Model* model : modelList)
      pluginInstance->addModel(model);
}
