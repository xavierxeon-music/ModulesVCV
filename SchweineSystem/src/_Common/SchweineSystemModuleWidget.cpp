#include "SchweineSystemModuleWidget.h"

#include <SchweineSystemModule.h>

SchweineSystem::ModuleWidget::ModuleWidget(Module* schweineModule)
   : rack::ModuleWidget()
   , schweineModule(schweineModule)
{
   rack::ModuleWidget::setModule(schweineModule);
}

SchweineSystem::Module* SchweineSystem::ModuleWidget::getSchweineModule() const
{
   return schweineModule;
}
