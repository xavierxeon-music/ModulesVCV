#include "SvinMaster.h"

Svin::Master::Master()
   : pluginInstance(nullptr)
   , modelList()
{
}

Svin::Master* Svin::Master::the()
{
   static Master* theOnlyOne = new Master();
   return theOnlyOne;
}

Plugin* Svin::Master::instance()
{
   return pluginInstance;
}

// the "main" function
void init(Plugin* pluginInstance)
{
   Svin::Master* master = Svin::Master::the();
   master->pluginInstance = pluginInstance;

   using ModelList = Svin::Master::ModelList;
   const ModelList& modelList = master->modelList;

   for (Model* model : modelList)
      pluginInstance->addModel(model);
}
