#ifndef SchweinesystemH
#define SchweinesystemH

#include <rack.hpp>

class Schweinesystem
{
public:
   Schweinesystem(rack::Plugin* pluginInstance);

public:
   static rack::Plugin* instance();

   template <typename Audio, typename Widget>
   void addModule(const std::string& name);

private:
   static rack::Plugin* pluginInstance;
};

// global variable

#endif // SchweinesystemH
