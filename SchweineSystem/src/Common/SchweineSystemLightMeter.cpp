#include "SchweineSystemLightMeter.h"

#include <iostream>

SchweineSystem::LightMeter::LightMeter(std::vector<rack::engine::Light>& fullList)
   : meterLights()
   , meterMapper(0, 3 * NumberOfLights, 0, 3 * NumberOfLights)
{
   for (uint8_t index = 0; index < NumberOfLights; index++)
      meterLights[index] = new Light(fullList);
}

SchweineSystem::LightMeter::~LightMeter()
{
   for (uint8_t index = 0; index < NumberOfLights; index++)
      delete meterLights[index];
}

void SchweineSystem::LightMeter::assign(const RedIndexList& redIndexList)
{
   if (NumberOfLights != redIndexList.size())
      return;

   for (uint8_t index = 0; index < NumberOfLights; index++)
      meterLights[index]->assign(redIndexList[index]);
}

void SchweineSystem::LightMeter::setMaxValue(const uint16_t& newMaxValue)
{
   meterMapper.setMaxInput(newMaxValue);
}

void SchweineSystem::LightMeter::setMeter(const uint16_t& value)
{
   const uint8_t meterValue = meterMapper(value);

   if (0 == meterValue)
   {
      for (uint8_t index = 0; index < NumberOfLights; index++)
         meterLights[index]->setOff();
   }
   else
   {
      const uint8_t numberOn = (meterValue - 1) % NumberOfLights;
      const uint8_t stageSocket = meterValue - (1 + numberOn);
      const uint8_t stage = stageSocket / NumberOfLights;

      static const std::vector<Color> stageColorList = {Color{0, 0, 0}, Color{100, 0, 255}, Color{255, 255, 0}, Color{255, 0, 0}};

      const Color onColor = stageColorList.at(stage + 1);
      const Color offColor = stageColorList.at(stage);
      for (uint8_t index = 0; index < NumberOfLights; index++)
      {
         if (index < numberOn + 1)
            meterLights[index]->setColor(onColor);
         else
            meterLights[index]->setColor(offColor);
      }
   }
}

// list

SchweineSystem::LightMeter::List::List(std::vector<rack::engine::Light>& fullList)
   : fullList(fullList)
   , instanceList()
{
}

SchweineSystem::LightMeter::List::~List()
{
   for (LightMeter* instance : instanceList)
      delete instance;
}

void SchweineSystem::LightMeter::List::append(const std::vector<RedIndexList>& redIndexLists)
{
   for (const RedIndexList& redIndexList : redIndexLists)
   {
      LightMeter* lightMeter = new LightMeter(fullList);
      lightMeter->assign(redIndexList);
      instanceList.push_back(lightMeter);
   }
}

SchweineSystem::LightMeter* SchweineSystem::LightMeter::List::operator[](const uint16_t& index)
{
   return instanceList[index];
}
