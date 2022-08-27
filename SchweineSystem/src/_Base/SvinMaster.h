#ifndef SvinMasterH
#define SvinMasterH

#include <iostream>

#include <rack.hpp>
using namespace rack;

// the "main" function
void init(Plugin* pluginInstance);

namespace Svin
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
} // namespace Svin

#ifndef SvinMasterHPP
#include "SvinMaster.hpp"
#endif // NOT SvinMasterHPP

#endif // NOT SvinMasterH
