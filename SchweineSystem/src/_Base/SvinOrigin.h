#ifndef SvinOriginH
#define SvinOriginH

#include <iostream>

#include <rack.hpp>
using namespace rack;

// the "main" function
void init(Plugin* pluginInstance);

namespace Svin
{
   class Origin
   {
   public:
      using ModelList = std::vector<Model*>;

   public:
      static Origin* the();

      template <typename AudioClass, typename WidgetClass>
      Model* addModule(const std::string& name);

      Plugin* instance();

   private:
      friend void ::init(Plugin* pluginInstance);

   private:
      Origin();

   private:
      Plugin* pluginInstance;
      ModelList modelList;
   };
} // namespace Svin

#ifndef SvinOriginHPP
#include "SvinOrigin.hpp"
#endif // NOT SvinOriginHPP

#endif // NOT SvinOriginH
