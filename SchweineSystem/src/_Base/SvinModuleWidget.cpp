#include "SvinModuleWidget.h"

#include <SvinModule.h>
#include <SvinOrigin.h>

class PanelWidget : public rack::widget::TransparentWidget
{
public:
   PanelBaseWidget(Vec _size, float* _panelContrastSrc)
   {
      box.size = _size;
      panelContrastSrc = _panelContrastSrc;
   }
   void draw(const DrawArgs& args) override;
};

// module widget

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

void Svin::ModuleWidget::makePanel(const std::string& resPath)
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), resPath);
   /*
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);
   */

   std::shared_ptr<rack::window::Svg> svg = APP->window->loadSvg(panelPath);
   setPanel(svg);

   SvgPanel* svgPanel = (SvgPanel*)getPanel();
   //svgPanel->fb->addChildBottom(new PanelBaseWidget(svgPanel->box.size, cont));
}