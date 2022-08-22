#ifndef SyModuleWidgetH
#define SyModuleWidgetH

#include <rack.hpp>

namespace Sy
{
   class Module;

   class ModuleWidget : public rack::ModuleWidget
   {
   public:
      ModuleWidget(Module* schweineModule);

   public:
      Module* getSchweineModule() const;

   public:
      void draw(const DrawArgs& args) override;

   protected:
      Module* schweineModule;
   };
} // namespace Sy

#endif // NOT SyModuleWidgetH
