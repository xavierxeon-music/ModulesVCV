#include "Bitify.h"
#include "BitifyPanel.h"

#include <iostream>

using Panel = Bitify::Panel;

// ordered from LSB to MSB
static const std::vector<Panel::ParamId> latchId = {Panel::FlipSwitch8, Panel::FlipSwitch7, Panel::FlipSwitch6, Panel::FlipSwitch5, Panel::FlipSwitch4, Panel::FlipSwitch3, Panel::FlipSwitch2, Panel::FlipSwitch1};
static const std::vector<Panel::LightId> lightId = {Panel::Light_FlipSwitch8, Panel::Light_FlipSwitch7, Panel::Light_FlipSwitch6, Panel::Light_FlipSwitch5, Panel::Light_FlipSwitch4, Panel::Light_FlipSwitch3, Panel::Light_FlipSwitch2, Panel::Light_FlipSwitch1};

static const std::vector<Panel::InputId> gateId = {Panel::GateIn8, Panel::GateIn7, Panel::GateIn6, Panel::GateIn5, Panel::GateIn4, Panel::GateIn3, Panel::GateIn2, Panel::GateIn1};
static const std::vector<Panel::OutputId> bitOutId = {Panel::BitOut8, Panel::BitOut7, Panel::BitOut6, Panel::BitOut5, Panel::BitOut4, Panel::BitOut3, Panel::BitOut2, Panel::BitOut1};
static const std::vector<Panel::InputId> bitInId = {Panel::BitIn8, Panel::BitIn7, Panel::BitIn6, Panel::BitIn5, Panel::BitIn4, Panel::BitIn3, Panel::BitIn2, Panel::BitIn1};

Bitify::Bitify()
   : Module()
   , boolFieldIn()
   , boolFieldOutLast()
   , inputMapper(-5.0, 5.0, 0.0, 255.0)
   , outputMapper(0.0, 255.0, -5.0, 5.0)
{
   setup();
}

Bitify::~Bitify()
{
}

void Bitify::process(const ProcessArgs& args)
{
   const float voltageInput = inputs[Panel::AudioIn].getVoltage(); // from -5.0 V to + 5.0 V
   boolFieldIn = static_cast<uint8_t>(inputMapper(voltageInput));

   // do byte mainpulation
   BoolField8 boolFieldOut = 0;
   BoolField8 lockMask = 0;

   for (uint8_t index = 0; index < 8; index++)
   {
      // gate latches
      if (gateTriggers[index].process(params[latchId.at(index)].getValue()))
         gates[index] ^= true;
      lights[lightId.at(index)].setBrightness(gates[index]);

      bool toggle = false;
      if (inputs[gateId.at(index)].isConnected())
         toggle = (inputs[gateId.at(index)].getVoltage() > 3.0);
      if (gates[index])
         toggle = !toggle;

      bool value = boolFieldIn.get(index);
      if (toggle)
         value = !value;

      // set bit output to value
      outputs[bitOutId.at(index)].setVoltage(value ? 5.0 : 0.0);

      // override value if bit in is patched -> this will lag one frame behind!
      if (inputs[bitInId.at(index)].isConnected())
      {
         value = (inputs[bitInId.at(index)].getVoltage() > 3.0);
      }
      else // lock current value for future use and revert to last value
      {
         const bool futureValue = value;
         value = boolFieldOutLast.get(index);

         lockMask.set(index, true);
         boolFieldOutLast.set(index, futureValue);
      }

      boolFieldOut.set(index, value);
   }

   const float voltageOutput = outputMapper(static_cast<float>(boolFieldOut));

   for (uint8_t index = 0; index < 8; index++)
   {
      const bool value = boolFieldOut.get(index);
      if (!lockMask.get(index))
         boolFieldOutLast.set(index, value);
   }

   outputs[Panel::AudioOut].setVoltage(voltageOutput);
}
