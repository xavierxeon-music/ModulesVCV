#include "SvinModuleWidget.h"

#include <SvinModule.h>
#include <SvinOrigin.h>

struct PanelWidget : rack::widget::TransparentWidget
{
   PanelWidget(Vec _size)
      : rack::widget::TransparentWidget()
   {
      box.size = _size;
   }

   void draw(const DrawArgs& args) override
   {
      nvgBeginPath(args.vg);
      NVGcolor baseColor = nvgRGB(255, 200, 200);

      nvgFillColor(args.vg, baseColor);
      nvgRect(args.vg, 0, 0, box.size.x, box.size.y);
      nvgFill(args.vg);
      TransparentWidget::draw(args);
   }
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
   svgPanel->fb->addChildBottom(new PanelWidget(svgPanel->box.size));
}