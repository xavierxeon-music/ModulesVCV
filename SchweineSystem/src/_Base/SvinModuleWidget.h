#ifndef SvinModuleWidgetH
#define SvinModuleWidgetH

#include <rack.hpp>

#include <Colour.h>

namespace Svin
{
   class Module;

   class ModuleWidget : public rack::ModuleWidget
   {
   public:
      static const Color BackGroundColor;

   public:
      ModuleWidget(Module* schweineModule);
      virtual ~ModuleWidget();

   public:
      Module* getSchweineModule() const;

   protected:
      void draw(const DrawArgs& args) override;
      void makePanel(const std::string& resPath);

   protected:
      Module* schweineModule;

   private:
      struct PanelBackground;
      struct PanelFrame;
   };
} // namespace Svin

#endif // NOT SvinModuleWidgetH
