#ifndef SySvgImageH
#define SySvgImageH

#include <rack.hpp>
using namespace rack;

#include "SyModule.h"

namespace Sy
{
   class SvgImage : public widget::OpaqueWidget
   {
   public:
      SvgImage(rack::math::Vec pos, Module* module, const std::string& path, const float& scale = 1.0);

   public:
      void shift(rack::math::Vec diff);

   private:
      widget::FramebufferWidget* fb;
      widget::TransformWidget* tw;
      widget::SvgWidget* sw;
   };
} // namespace Sy

#endif // NOT SySvgImageH
