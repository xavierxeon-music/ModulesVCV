#ifndef SvinModuleWidgetH
#define SvinModuleWidgetH

#include <rack.hpp>

namespace Svin
{
   class Module;

   class ModuleWidget : public rack::ModuleWidget
   {
   public:
      ModuleWidget(Module* schweineModule);
      virtual ~ModuleWidget();

   public:
      Module* getSchweineModule() const;

   protected:
      virtual void preDraw();
      void draw(const DrawArgs& args) override;

   protected:
      Module* schweineModule;
   };
} // namespace Svin

#endif // NOT SvinModuleWidgetH
