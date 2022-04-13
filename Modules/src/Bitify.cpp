#include "Bitify.h"
#include "BitifyData.h"

Bitify::Bitify()
   : Module()
{
   setup();
}

Bitify::~Bitify()
{
}

void Bitify::process(const ProcessArgs& args)
{
   // Gate buttons
   static const std::vector<Data::ParamId> gateId = {Data::FlipSwitch8, Data::FlipSwitch7, Data::FlipSwitch6, Data::FlipSwitch5, Data::FlipSwitch4, Data::FlipSwitch3, Data::FlipSwitch2, Data::FlipSwitch1};
   static const std::vector<Data::LightId> lightId = {Data::Light_FlipSwitch8, Data::Light_FlipSwitch7, Data::Light_FlipSwitch6, Data::Light_FlipSwitch5, Data::Light_FlipSwitch4, Data::Light_FlipSwitch3, Data::Light_FlipSwitch2, Data::Light_FlipSwitch1};

   for (int i = 0; i < 8; i++)
   {
      if (gateTriggers[i].process(params[gateId.at(i)].getValue()))
      {
         gates[i] ^= true;
      }
      lights[lightId.at(i)].setBrightness(gates[i]);
   }

   const float voltage = inputs[Data::AudioIn].getVoltage();
   outputs[Data::AudioOut].setVoltage(voltage);
}
