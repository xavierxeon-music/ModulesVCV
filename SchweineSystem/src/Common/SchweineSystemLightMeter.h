#ifndef SchweineSystemLightMeterH
#define SchweineSystemLightMeterH

#include <rack.hpp>

#include <Tools/Range.h>

#include "SchweineSystemLight.h"

// TODO make templates with variable number of lights
static constexpr uint8_t NumberOfLights = 5;

namespace SchweineSystem
{
   class LightMeter
   {
   public:
      using RedIndexList = std::vector<uint16_t>;

   public:
      class List;

   public:
      LightMeter(std::vector<rack::engine::Light>& fullList);
      ~LightMeter();

   public:
      void assign(const RedIndexList& redIndexList);
      void setMaxValue(const uint16_t& newMaxValue);
      void setMeter(const uint16_t& value);

   private:
      Light* meterLights[NumberOfLights];
      Range::Mapper meterMapper;
   };

   class LightMeter::List
   {
   public:
      List(std::vector<rack::engine::Light>& fullList);
      ~List();

   public:
      void append(const std::vector<RedIndexList>& redIndexLists);
      LightMeter* operator[](const uint16_t& index);

   private:
      std::vector<rack::engine::Light>& fullList;
      std::vector<LightMeter*> instanceList;
   };

} // namespace SchweineSystem

#endif // NOT SchweineSystemLightMeterH
