#include "SvinModuleWidget.h"

#include <SvinModule.h>

Svin::ModuleWidget::ModuleWidget(Module* schweineModule)
   : rack::ModuleWidget()
   , schweineModule(schweineModule)
{
   rack::ModuleWidget::setModule(schweineModule);
}

Svin::ModuleWidget::~ModuleWidget()
{
}

Svin::Module* Svin::ModuleWidget::getSchweineModule() const
{
   return schweineModule;
}

void Svin::ModuleWidget::preDraw()
{
   // do nothing
}

void Svin::ModuleWidget::draw(const DrawArgs& args)
{
   preDraw();

   if (schweineModule)
      schweineModule->updateDisplays();

   rack::ModuleWidget::draw(args);
}
