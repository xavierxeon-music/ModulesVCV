#include "Schweinesystem.h"

rack::Plugin* Schweinesystem::pluginInstance = nullptr;

Schweinesystem::Schweinesystem(rack::Plugin* pluginInstance)
{
   Schweinesystem::pluginInstance = pluginInstance;
}

rack::Plugin* Schweinesystem::instance()
{
   return pluginInstance;
}

template <typename AudioClass, typename WidgetClass>
void Schweinesystem::addModule(const std::string& name)
{
   rack::Model* model = rack::createModel<AudioClass, WidgetClass>(name);
   pluginInstance->addModel(model);
}

// main funtion

#include "DemoDummy.h"

void init(rack::Plugin* pluginInstance)
{
   Schweinesystem myStuff(pluginInstance);
   myStuff.addModule<DemoDummy, DemoDummyWidget>("DemoDummy");
}
