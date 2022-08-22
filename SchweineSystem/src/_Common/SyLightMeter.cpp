#include "SyLightMeter.h"

// controller

Sy::LightMeter::Controller::Controller(Module* module, const uint16_t& valueId)
   : module(module)
   , valueId(valueId)
   , valueMapper(0.0, 1.0, 0.0, 100.0)
{
}

void Sy::LightMeter::Controller::setMaxValue(const uint16_t& newMaxValue)
{
   valueMapper.setMaxInput(newMaxValue);
}

void Sy::LightMeter::Controller::setValue(const uint32_t& value)
{
   module->values[valueId] = valueMapper(value);
}

// controller list

Sy::LightMeter::Controller::List::List(Module* module)
   : module(module)
{
}

Sy::LightMeter::Controller::List::~List()
{
   for (Controller* instance : instanceList)
      delete instance;
}

void Sy::LightMeter::Controller::List::append(const std::vector<uint16_t>& valueIdList)
{
   for (const uint16_t& valueId : valueIdList)
   {
      Controller* controller = new Controller(module, valueId);
      instanceList.push_back(controller);
   }
}

Sy::LightMeter::Controller* Sy::LightMeter::Controller::List::operator[](const uint16_t& index)
{
   return instanceList[index];
}

// widget

Sy::LightMeter::Widget::Widget(rack::math::Vec pos, Module* module, const uint8_t& segmentCount, const uint16_t& valueId)
   : rack::TransparentWidget()
   , module(module)
   , valueId(valueId)
   , segmentCount(segmentCount)
   , meterMapper(0.0, 100.0, 0.0, 3.0 * segmentCount)
{
   box.pos = rack::math::Vec(pos.x, pos.y);
}

void Sy::LightMeter::Widget::drawLayer(const DrawArgs& args, int layer)
{
   if (layer != 1)
      return;

   static const std::vector<NVGcolor> stageColorList = {nvgRGB(0, 0, 0), nvgRGB(0, 150, 255), nvgRGB(255, 255, 0), nvgRGB(255, 50, 50)};

   const uint8_t meterValue = [&]() -> uint8_t
   {
      if (!module)
         return 13;

      const float fValue = module->values[valueId];
      return static_cast<uint8_t>(meterMapper(fValue));
   }();

   auto drawSegment = [&](const uint8_t index, const uint8_t colorIndex)
   {
      const float y = 1 + (5.0 * (segmentCount - 1 - index));

      nvgBeginPath(args.vg);
      nvgRect(args.vg, 1, y, 4, 4);

      //nvgFillColor(args.vg, stageColorList[colorIndex]);

      static const NVGcolor black = nvgRGB(0, 0, 0);
      static const NVGcolor white = nvgRGB(255, 255, 255);

      const NVGcolor darkColor = nvgLerpRGBA(stageColorList[colorIndex], black, 0.4);
      const NVGcolor lightColor = nvgLerpRGBA(stageColorList[colorIndex], white, 0.4);
      const NVGpaint gradiant = nvgLinearGradient(args.vg, 2, y, 2, y + 4, lightColor, darkColor);
      nvgFillPaint(args.vg, gradiant);

      nvgFill(args.vg);
   };

   if (0 == meterValue)
   {
      for (uint8_t index = 0; index < segmentCount; index++)
      {
         drawSegment(index, 0);
      }
   }
   else
   {
      const uint8_t numberOn = (meterValue - 1) % segmentCount;
      const uint8_t stageSocket = meterValue - (1 + numberOn);
      const uint8_t stage = stageSocket / segmentCount;

      for (uint8_t index = 0; index < segmentCount; index++)
      {
         if (index < numberOn + 1)
            drawSegment(index, stage + 1);
         else
            drawSegment(index, stage);
      }
   }
}
