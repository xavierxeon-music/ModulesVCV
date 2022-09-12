#include "SvinSvgImage.h"

Svin::SvgImage::SvgImage(rack::math::Vec pos, Module* module, const std::string& path, const float& scale)
   : widget::OpaqueWidget()
   , tw(nullptr)
   , scale(scale)
{
   // sub widgets
   widget::FramebufferWidget* fb = new widget::FramebufferWidget;
   addChild(fb);

   tw = new widget::TransformWidget;
   tw->scale(math::Vec(scale, scale));
   fb->addChild(tw);

   widget::SvgWidget* sw = new widget::SvgWidget;
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

void Svin::SvgImage::onButton(const rack::event::Button& buttonEvent)
{
   if (0 > buttonEvent.pos.x || box.size.x <= buttonEvent.pos.x)
      return;
   if (0 > buttonEvent.pos.y || box.size.y <= buttonEvent.pos.y)
      return;

   if (GLFW_MOUSE_BUTTON_LEFT == buttonEvent.button && GLFW_PRESS == buttonEvent.action)
   {
      buttonEvent.consume(this);
      std::cout << "image clicked" << std::endl;
   }
}
