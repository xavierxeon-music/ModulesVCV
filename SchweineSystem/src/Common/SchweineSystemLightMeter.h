#ifndef SchweineSystemLightMeterH
#define SchweineSystemLightMeterH

#include <rack.hpp>

#include <Tools/Range.h>

#include "SchweineSystemLight.h"

// TODO make template with variable number of lights
static constexpr uint8_t NumberOfLights = 5;

namespace SchweineSystem
{
   class LightMeter
   {
   public:
      using RedIndexList = uint16_t[NumberOfLights];

   public:
      class List;

   public:
      LightMeter(std::vector<rack::engine::Light>& fullList);

   public:
      void assign(const RedIndexList& redIndexList);
      void setMaxValue(const uint16_t& newMaxValue);
      void setMeter(const uint16_t& value);

   private:
      Light lights[NumberOfLights];
      Range::Mapper MeterMapper;
   };

   class LightMeter::List
   {
   public:
      List(std::vector<rack::engine::Light>& fullList);

   public:
      void append(std::vector<RedIndexList> redIndexLists);
      LightMeter* operator[](const uint16_t& index);

   private:
      std::vector<rack::engine::Light>& fullList;
      std::vector<LightMeter> instanceList;
   };

} // namespace SchweineSystem

#endif // NOT SchweineSystemLightMeterH
