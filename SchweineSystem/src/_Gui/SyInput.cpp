#include "SyInput.h"

#include "SyModule.h"

Sy::Input::Input(Module* module, const uint16_t& inputIndex)
   : module(module)
   , inputIndex(inputIndex)
   , triggers{}
{
}

bool Sy::Input::isConnected() const
{
   return module->inputs[inputIndex].isConnected();
}

uint8_t Sy::Input::getNumberOfChannels() const
{
   return module->inputs[inputIndex].getChannels();
}

float Sy::Input::getVoltage(const uint8_t channel) const
{
   return module->inputs[inputIndex].getVoltage(channel);
}

bool Sy::Input::isTriggered(const uint8_t channel) const
{
   const bool on = (getVoltage(channel) > 3.0);
   return triggers[channel].process(on);
}

bool Sy::Input::isOn(const uint8_t channel) const
{
   const bool on = (getVoltage(channel) > 3.0);
   return on;
}

bool Sy::Input::isOff(const uint8_t channel) const
{
   return !isOn(channel);
}
