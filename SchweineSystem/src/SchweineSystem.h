#ifndef SchweineSystemH
#define SchweineSystemH

#include <iostream>

#include <rack.hpp>
using namespace rack;

// the "main" function
void init(Plugin* pluginInstance);

class SchweineSystem
{
public:
   enum class Series
   {
      None,
      BitBus,
      Mopher
   };
   using ModelList = std::vector<Model*>;
   using ModelMap = std::map<Series, ModelList>;

public:
   static SchweineSystem* the();

   template <typename AudioClass, typename WidgetClass>
   Model* addModule(const std::string& name, const Series series = Series::None);

   Plugin* instance();

private:
   friend void init(Plugin* pluginInstance);

private:
   SchweineSystem();

private:
   Plugin* pluginInstance;
   ModelMap modelMap;
};

#ifndef SchweineSystemHPP
#include "SchweineSystem.hpp"
#endif // NOT SchweineSystemHPP

#endif // NOT  SchweineSystemH
