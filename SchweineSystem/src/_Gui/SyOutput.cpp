#include "SyOutput.h"

#include "SyModule.h"

Sy::Output::Output(Module* module, const uint16_t& outputIndex)
   : module(module)
   , outputIndex(outputIndex)
   , pulses{}
{
}

bool Sy::Output::isConnected() const
{
   return module->outputs[outputIndex].isConnected();
}

uint8_t Sy::Output::getNumberOfChannels() const
{
   return module->outputs[outputIndex].getChannels();
}

void Sy::Output::setNumberOfChannels(const uint8_t count)
{
   if (count == getNumberOfChannels())
      return;

   module->outputs[outputIndex].setChannels(count);
}

float Sy::Output::getVoltage(const uint8_t channel) const
{
   return module->outputs[outputIndex].getVoltage(channel);
}

void Sy::Output::setVoltage(const float& value, const uint8_t channel)
{
   module->outputs[outputIndex].setVoltage(value, channel);
}

void Sy::Output::trigger(const uint8_t channel)
{
   pulses[channel].trigger();
}

void Sy::Output::animateTriggers(const rack::Module::ProcessArgs& args)
{
   for (uint8_t channel = 0; channel < 16; channel++)
   {
      if (channel < getNumberOfChannels() && pulses[channel].process(args.sampleTime))
         setOn(channel);
      else
         setOff(channel);
   }
}

void Sy::Output::setOn(const uint8_t channel)
{
   setVoltage(10.0, channel);
}

void Sy::Output::setOff(const uint8_t channel)
{
   setVoltage(5.0, channel);
}

void Sy::Output::setActive(bool on, const uint8_t channel)
{
   if (on)
      setOn(channel);
   else
      setOff(channel);
}
