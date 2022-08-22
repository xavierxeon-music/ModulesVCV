#include "SyModuleWidget.h"

#include <SyModule.h>

Sy::ModuleWidget::ModuleWidget(Module* schweineModule)
   : rack::ModuleWidget()
   , schweineModule(schweineModule)
{
   rack::ModuleWidget::setModule(schweineModule);
}

Sy::Module* Sy::ModuleWidget::getSchweineModule() const
{
   return schweineModule;
}

void Sy::ModuleWidget::draw(const DrawArgs& args)
{
   if (schweineModule)
      schweineModule->updateDisplays();

   rack::ModuleWidget::draw(args);
}
