#include "SchweineSystemLightMeter.h"

// controller

SchweineSystem::LightMeter::Controller::Controller(rack::engine::Module* module, const uint16_t& valueParamId)
   : module(module)
   , valueParamId(valueParamId)
   , valueMapper(0.0, 1.0, 0.0, 1.0)
{
}

void SchweineSystem::LightMeter::Controller::setMaxValue(const uint16_t& newMaxValue)
{
   valueMapper.setMaxInput(newMaxValue);
}

void SchweineSystem::LightMeter::Controller::setValue(const uint32_t& value)
{
   const float fValue = valueMapper(value);
   module->params[valueParamId].setValue(fValue);
}

// controller list

SchweineSystem::LightMeter::Controller::List::List(rack::engine::Module* module)
   : module(module)
{
}

SchweineSystem::LightMeter::Controller::List::~List()
{
   for (Controller* instance : instanceList)
      delete instance;
}

void SchweineSystem::LightMeter::Controller::List::append(const std::vector<uint16_t>& paramIdList)
{
   for (const uint16_t& valueParamId : paramIdList)
   {
      Controller* controller = new Controller(module, valueParamId);
      instanceList.push_back(controller);
   }
}

SchweineSystem::LightMeter::Controller* SchweineSystem::LightMeter::Controller::List::operator[](const uint16_t& index)
{
   return instanceList[index];
}

// widget

SchweineSystem::LightMeter::Widget::Widget(rack::math::Vec pos, rack::engine::Module* module, const uint8_t& segmentCount, const uint16_t& valueParamId)
   : rack::TransparentWidget()
   , module(module)
   , valueParamId(valueParamId)
   , segmentCount(segmentCount)
   , meterMapper(0.0, 1.0, 0.0, 3.0 * segmentCount)
{
   box.pos = rack::math::Vec(pos.x, pos.y);
}

void SchweineSystem::LightMeter::Widget::drawLayer(const DrawArgs& args, int layer)
{
   if (layer != 1)
      return;

   static const std::vector<NVGcolor> stageColorList = {nvgRGB(0, 0, 0), nvgRGB(100, 100, 255), nvgRGB(255, 255, 100), nvgRGB(255, 100, 100)};

   const uint8_t meterValue = [&]() -> uint8_t
   {
      if (!module)
         return 13;

      const float fValue = module->params[valueParamId].getValue();
      return static_cast<uint8_t>(meterMapper(fValue));
   }();

   auto drawSegment = [&](float x, uint8_t colorIndex)
   {
      nvgBeginPath(args.vg);
      nvgRect(args.vg, x, 1, 4, 6);

      //nvgFillColor(args.vg, stageColorList[colorIndex]);

      static const NVGcolor black = nvgRGB(0, 0, 0);
      static const NVGcolor white = nvgRGB(255, 255, 255);

      const NVGcolor darkColor = nvgLerpRGBA(stageColorList[colorIndex], black, 0.4);
      const NVGcolor lightColor = nvgLerpRGBA(stageColorList[colorIndex], white, 0.4);
      const NVGpaint gradiant = nvgLinearGradient(args.vg, x + 2, 0, x + 2, 6, lightColor, darkColor);
      nvgFillPaint(args.vg, gradiant);

      nvgFill(args.vg);

   };

   if (0 == meterValue)
   {
      for (uint8_t index = 0; index < segmentCount; index++)
      {
         const float x = 1 + (5.0 * index);
         drawSegment(x, 0);
      }
   }
   else
   {
      const uint8_t numberOn = (meterValue - 1) % segmentCount;
      const uint8_t stageSocket = meterValue - (1 + numberOn);
      const uint8_t stage = stageSocket / segmentCount;

      for (uint8_t index = 0; index < segmentCount; index++)
      {
         const float x = 1 + (5.0 * index);
         if (index < numberOn + 1)
            drawSegment(x, stage + 1);
         else
            drawSegment(x, stage);
      }
   }
}
