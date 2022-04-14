#include "SchweineSystem.h"

Plugin* SchweineSystem::instance = nullptr;

// the "main" function
void init(Plugin* pluginInstance)
{
   using ModelList = SchweineSystem::ModelList;
   using ModelMap = SchweineSystem::ModelMap;

   SchweineSystem::instance = pluginInstance;

   std::cout << "init" << std::endl;

   for (ModelMap::const_iterator it = SchweineSystem::modelMap.cbegin(); it != SchweineSystem::modelMap.cend(); it++)
   {
      const ModelList& modelList = it->second;
      for (Model* model : modelList)
         pluginInstance->addModel(model);
   }
}
