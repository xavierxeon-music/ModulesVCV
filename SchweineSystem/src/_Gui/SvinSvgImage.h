#ifndef SvinSvgImageH
#define SvinSvgImageH

#include <rack.hpp>
using namespace rack;

#include "SvinModule.h"

namespace Svin
{
   class SvgImage : public widget::OpaqueWidget
   {
   public:
      SvgImage(rack::math::Vec pos, Module* module, const std::string& path, const float& scale = 1.0);

   public:
      void shift(rack::math::Vec precentage);

   private:
      widget::FramebufferWidget* fb;
      widget::TransformWidget* tw;
      widget::SvgWidget* sw;

      float scale;
   };
} // namespace Svin

#endif // NOT SvinSvgImageH
