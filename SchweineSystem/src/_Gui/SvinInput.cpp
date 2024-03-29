#include "SvinInput.h"

#include "SvinModule.h"

Svin::Input::Input(Module* module, const uint16_t& inputIndex)
   : module(module)
   , inputIndex(inputIndex)
   , triggerThreshold(3.0)
//, triggers{}
{
}

bool Svin::Input::isConnected() const
{
   return module->inputs[inputIndex].isConnected();
}

uint8_t Svin::Input::getNumberOfChannels() const
{
   return module->inputs[inputIndex].getChannels();
}

float Svin::Input::getVoltage(const uint8_t channel) const
{
   return module->inputs[inputIndex].getVoltage(channel);
}

bool Svin::Input::isTriggered(const uint8_t channel) const
{
   const bool on = (getVoltage(channel) > triggerThreshold);
   return triggers[channel].process(on);
}

bool Svin::Input::isOn(const uint8_t channel) const
{
   const bool on = (getVoltage(channel) > triggerThreshold);
   return on;
}

bool Svin::Input::isOff(const uint8_t channel) const
{
   return !isOn(channel);
}

const float& Svin::Input::getTriggerThreshold() const
{
   return triggerThreshold;
}

void Svin::Input::setTriggerThreshold(const float& value)
{
   triggerThreshold = value;
}
