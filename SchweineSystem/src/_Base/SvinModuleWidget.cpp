#include "SvinModuleWidget.h"

#include <SvinModule.h>
#include <SvinOrigin.h>

namespace Svin
{
   static const NVGcolor topColor = nvgRGB(220, 230, 230);
   static const NVGcolor bottomColor = nvgRGB(180, 180, 190);

   struct ModuleWidget::PanelBackground : rack::widget::TransparentWidget
   {
      PanelBackground(Vec _size)
         : rack::widget::TransparentWidget()
      {
         box.size = _size;
      }

      void draw(const DrawArgs& args) override
      {
         NVGpaint paint = nvgLinearGradient(args.vg, 0.0, 0.0, box.size.x, box.size.y, topColor, bottomColor);

         nvgBeginPath(args.vg);
         nvgFillPaint(args.vg, paint);
         nvgRect(args.vg, 0, 0, box.size.x, box.size.y);
         nvgFill(args.vg);
         TransparentWidget::draw(args);
      }
   };

   struct ModuleWidget::PanelFrame : rack::widget::TransparentWidget
   {
      PanelFrame(Vec _size)
         : rack::widget::TransparentWidget()
      {
         box.size = _size;
      }

      void draw(const DrawArgs& args) override
      {
         static const float colorScale = 0.98;
         const NVGcolor frameTopColor = nvgRGBAf(colorScale * topColor.r, colorScale * topColor.g, colorScale * topColor.b, topColor.a);
         const NVGcolor frameBottompColor = nvgRGBAf(colorScale * bottomColor.r, colorScale * bottomColor.g, colorScale * bottomColor.b, bottomColor.a);

         NVGpaint paint = nvgLinearGradient(args.vg, 0.0, 0.0, box.size.x, box.size.y, frameTopColor, frameBottompColor);
         static const uint8_t padding = 2;

         nvgBeginPath(args.vg);
         nvgFillPaint(args.vg, paint);
         nvgRect(args.vg, 0, 0, padding, box.size.y);
         nvgRect(args.vg, box.size.x - padding, 0, padding, box.size.y);
         nvgRect(args.vg, 0, 0, box.size.x, padding);
         nvgRect(args.vg, 0, box.size.y - padding, box.size.x, padding);
         nvgFill(args.vg);
         TransparentWidget::draw(args);
      }
   };
} // namespace Svin

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

void Svin::ModuleWidget::draw(const DrawArgs& args)
{
   if (schweineModule)
      schweineModule->updateDisplays();

   rack::ModuleWidget::draw(args);
}

void Svin::ModuleWidget::makePanel(const std::string& resPath)
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), resPath);

   std::shared_ptr<rack::window::Svg> svg = APP->window->loadSvg(panelPath);
   setPanel(svg);

   SvgPanel* svgPanel = (SvgPanel*)getPanel();

   svgPanel->fb->addChildBottom(new PanelBackground(svgPanel->box.size));
   svgPanel->fb->addChild(new PanelFrame(svgPanel->box.size));
}
