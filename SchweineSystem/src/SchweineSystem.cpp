#include "SchweineSystem.h"

SchweineSystem::SchweineSystem()
   : pluginInstance(nullptr)
   , modelList()
{
}

SchweineSystem* SchweineSystem::the()
{
   static SchweineSystem* theOnlyOne = new SchweineSystem();
   return theOnlyOne;
}

Plugin* SchweineSystem::instance()
{
   return pluginInstance;
}

// the "main" function
void init(Plugin* pluginInstance)
{
   SchweineSystem::the()->pluginInstance = pluginInstance;

   using ModelList = SchweineSystem::ModelList;
   const ModelList& modelList = SchweineSystem::the()->modelList;

   for (Model* model : modelList)
      pluginInstance->addModel(model);
}
