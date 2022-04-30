#include "SchweineSystemMaster.h"

SchweineSystem::Master::Master()
   : pluginInstance(nullptr)
   , modelList()
{
}

SchweineSystem::Master* SchweineSystem::Master::the()
{
   static Master* theOnlyOne = new Master();
   return theOnlyOne;
}

Plugin* SchweineSystem::Master::instance()
{
   return pluginInstance;
}

// the "main" function
void init(Plugin* pluginInstance)
{
   SchweineSystem::Master* master = SchweineSystem::Master::the();
   master->pluginInstance = pluginInstance;

   using ModelList = SchweineSystem::Master::ModelList;
   const ModelList& modelList = master->modelList;

   for (Model* model : modelList)
      pluginInstance->addModel(model);
}
