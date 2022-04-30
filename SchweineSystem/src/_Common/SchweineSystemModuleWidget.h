#ifndef SchweineSystemModuleWidgetH
#define SchweineSystemModuleWidgetH

#include <rack.hpp>

namespace SchweineSystem
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
} // namespace SchweineSystem

#endif // NOT SchweineSystemModuleWidgetH
