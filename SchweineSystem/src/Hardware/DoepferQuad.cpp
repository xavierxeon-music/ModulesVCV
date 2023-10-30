#include "DoepferQuad.h"

#include <SvinOrigin.h>

DoepferQuad::DoepferQuad()
   : Svin::Module()
   , Svin::MidiOutput(Midi::Device::DopeferQuad1)
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
{
   setup();
   registerAsBusModule<Svin::MidiBus>();

   connectionButton.setDefaultColor(Color::Predefined::Green);
   connectToMidiDevice();
}

void DoepferQuad::process(const ProcessArgs& args)
{
   Svin::MidiBus busMessage = getBusData<Svin::MidiBus>(Side::Left);
   sendBusData<Svin::MidiBus>(Side::Right, busMessage);

   if (connectionButton.isTriggered())
      connectToMidiDevice();

   if (!connected())
      return;

   for (uint8_t channel = 0; channel < busMessage.noOfChannels; channel++)
   {
      if (!busMessage.channels[channel].hasEvents)
         continue;

      const ::Midi::MessageList& messageList = busMessage.channels[channel].messageList;
      for (const Bytes& message : messageList)
         sendMessage(message);
   }
}

void DoepferQuad::connectToMidiDevice()
{
   if (connected())
   {
      connectionButton.setOn();
      return;
   }

   connectionButton.setOff();
   if (!open())
      return;

   connectionButton.setOn();
}

// widget
DoepferQuadWidget::DoepferQuadWidget(DoepferQuad* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelDoepferQuad = Svin::Origin::the()->addModule<DoepferQuad, DoepferQuadWidget>("DoepferQuad");
