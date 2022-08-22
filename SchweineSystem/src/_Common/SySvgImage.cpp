#include "SySvgImage.h"

Sy::SvgImage::SvgImage(rack::math::Vec pos, Module* module, const std::string& path, const float& scale)
{
   // sub widgets
   fb = new widget::FramebufferWidget;
   addChild(fb);

   tw = new widget::TransformWidget;
   tw->scale(math::Vec(scale, scale));
   fb->addChild(tw);

   sw = new widget::SvgWidget;
   tw->addChild(sw);

   // setup
   sw->setSvg(Svg::load(path));
   tw->box.size = sw->box.size;
   fb->box.size = sw->box.size;

   fb->dirty = true;

   box.size = sw->box.size;
   box.pos = pos;
}

void Sy::SvgImage::shift(rack::math::Vec diff)
{
   tw->translate(diff);
}
