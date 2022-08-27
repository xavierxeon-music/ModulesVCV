#include "SvinSvgImage.h"

Svin::SvgImage::SvgImage(rack::math::Vec pos, Module* module, const std::string& path, const float& scale)
   : fb(nullptr)
   , tw(nullptr)
   , sw(nullptr)
   , scale(scale)
{
   // sub widgets
   fb = new widget::FramebufferWidget;
   addChild(fb);

   tw = new widget::TransformWidget;
   tw->scale(math::Vec(scale, scale));
   fb->addChild(tw);

   sw = new widget::SvgWidget;
   tw->addChild(sw);

   // load
   sw->setSvg(Svg::load(path));
   const math::Vec boxSize(sw->box.size.x * scale, sw->box.size.y * scale);

   // setup
   tw->box.size = boxSize;
   fb->box.size = boxSize;
   fb->dirty = true;

   box.size = boxSize;
   box.pos = pos;
}

void Svin::SvgImage::shift(rack::math::Vec precentage)
{
   const float x = static_cast<float>(precentage.x * (box.size.x / scale));
   const float y = static_cast<float>(precentage.y * (box.size.y / scale));

   const rack::math::Vec diff(x, y);
   tw->translate(diff);
}
