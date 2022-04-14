#include "SchweineSystem.h"

SchweineSystem::SchweineSystem()
   : pluginInstance(nullptr)
   , modelMap()
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
   using ModelMap = SchweineSystem::ModelMap;
   const ModelMap& modelMap = SchweineSystem::the()->modelMap;

   for (ModelMap::const_iterator it = modelMap.cbegin(); it != modelMap.cend(); it++)
   {
      const ModelList& modelList = it->second;
      for (Model* model : modelList)
         pluginInstance->addModel(model);
   }
}
