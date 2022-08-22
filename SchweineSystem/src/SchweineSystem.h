#ifndef SyH
#define SyH

#include <iostream>

#include <rack.hpp>
using namespace rack;

// the "main" function
void init(Plugin* pluginInstance);

class Sy
{
public:
   using ModelList = std::vector<Model*>;

public:
   static Sy* the();

   template <typename AudioClass, typename WidgetClass>
   Model* addModule(const std::string& name);

   Plugin* instance();

private:
   friend void init(Plugin* pluginInstance);

private:
   Sy();

private:
   Plugin* pluginInstance;
   ModelList modelList;
};

#ifndef SyHPP
#include "SyMaster.hpp"
#endif // NOT SyHPP

#endif // NOT  SyH
