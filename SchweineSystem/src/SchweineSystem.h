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
   template <typename AudioClass, typename WidgetClass>
   static Model* addModule(const std::string& name, const Series series = Series::None)
   {
      Model* model = createModel<AudioClass, WidgetClass>(name);
      modelMap[series].push_back(model);

      std::cout << "created model " << name << std::endl;

      return model;
   }

public:
   static Plugin* instance;

private:
   friend void init(Plugin* pluginInstance);

private:
   static ModelMap modelMap;
};

// list of all models ?
extern Model* modelBitify;

#endif // SchweineSystemH
