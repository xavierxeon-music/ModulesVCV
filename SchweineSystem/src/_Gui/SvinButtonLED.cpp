#include "SvinButtonLED.h"

#include "SvinInput.h"
#include "SvinModule.h"

Svin::ButtonLED::ButtonLED(Module* module, const uint16_t& paramIndex, const uint16_t& rgbIndex)
   : LED(module, rgbIndex)
   , paramIndex(paramIndex)
   , trigger()
   , latched(false)
   , latchBuddy(nullptr)
{
}

bool Svin::ButtonLED::isTriggered()
{
   const bool pressed = module->params[paramIndex].getValue();
   return trigger.process(pressed);
}

bool Svin::ButtonLED::isLatched(const bool update)
{
   if (!update)
      return latched;

   if (latchBuddy && latchBuddy->isConnected())
      latched = latchBuddy->isOn();
   else if (isTriggered())
      latched ^= true;

   return latched;
}

void Svin::ButtonLED::setLatched(bool on)
{
   latched = on;
}

void Svin::ButtonLED::setLatchBuddy(Input* input)
{
   latchBuddy = input;
}
