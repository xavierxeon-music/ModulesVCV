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
   using ModelList = std::vector<Model*>;

public:
   static SchweineSystem* the();

   template <typename AudioClass, typename WidgetClass>
   Model* addModule(const std::string& name);

   Plugin* instance();

private:
   friend void init(Plugin* pluginInstance);

private:
   SchweineSystem();

private:
   Plugin* pluginInstance;
   ModelList modelList;
};

#ifndef SchweineSystemHPP
#include "SchweineSystemMaster.hpp"
#endif // NOT SchweineSystemHPP

#endif // NOT  SchweineSystemH
