#include "SvinOutput.h"

#include "SvinModule.h"

Svin::Output::Output(Module* module, const uint16_t& outputIndex)
   : module(module)
   , outputIndex(outputIndex)
   , pulses{}
{
}

bool Svin::Output::isConnected() const
{
   return module->outputs[outputIndex].isConnected();
}

uint8_t Svin::Output::getNumberOfChannels() const
{
   return module->outputs[outputIndex].getChannels();
}

void Svin::Output::setNumberOfChannels(const uint8_t count)
{
   if (count == getNumberOfChannels())
      return;

   module->outputs[outputIndex].setChannels(count);
}

float Svin::Output::getVoltage(const uint8_t channel) const
{
   return module->outputs[outputIndex].getVoltage(channel);
}

void Svin::Output::setVoltage(const float& value, const uint8_t channel)
{
   module->outputs[outputIndex].setVoltage(value, channel);
}

void Svin::Output::trigger(const uint8_t channel)
{
   pulses[channel].trigger();
}

bool Svin::Output::animateTriggers(const rack::Module::ProcessArgs& args)
{
   bool active = false;
   for (uint8_t channel = 0; channel < 16; channel++)
   {
      if (channel < getNumberOfChannels() && pulses[channel].process(args.sampleTime))
      {
         setOn(channel);
         active = true;
      }
      else
      {
         setOff(channel);
      }
   }
   return active;
}

void Svin::Output::setOn(const uint8_t channel)
{
   setVoltage(10.0, channel);
}

void Svin::Output::setOff(const uint8_t channel)
{
   setVoltage(0.0, channel);
}

void Svin::Output::setActive(bool on, const uint8_t channel)
{
   if (on)
      setOn(channel);
   else
      setOff(channel);
}
