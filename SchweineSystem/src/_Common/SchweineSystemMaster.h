#ifndef SchweineSystemMasterH
#define SchweineSystemMasterH

#include <iostream>

#include <rack.hpp>
using namespace rack;

// the "main" function
void init(Plugin* pluginInstance);

namespace SchweineSystem
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
} // namespace SchweineSystem

#ifndef SchweineSystemMasterHPP
#include "SchweineSystemMaster.hpp"
#endif // NOT SchweineSystemMasterHPP

#endif // NOT SchweineSystemMasterH
