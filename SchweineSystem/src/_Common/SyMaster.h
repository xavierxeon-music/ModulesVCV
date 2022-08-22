#ifndef SyMasterH
#define SyMasterH

#include <iostream>

#include <rack.hpp>
using namespace rack;

// the "main" function
void init(Plugin* pluginInstance);

namespace Sy
{
   class Master
   {
   public:
      using ModelList = std::vector<Model*>;

   public:
      static Master* the();

      template <typename AudioClass, typename WidgetClass>
      Model* addModule(const std::string& name);

      Plugin* instance();

   private:
      friend void ::init(Plugin* pluginInstance);

   private:
      Master();

   private:
      Plugin* pluginInstance;
      ModelList modelList;
   };
} // namespace Sy

#ifndef SyMasterHPP
#include "SyMaster.hpp"
#endif // NOT SyMasterHPP

#endif // NOT SyMasterH
