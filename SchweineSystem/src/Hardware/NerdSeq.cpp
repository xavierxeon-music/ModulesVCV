#include "NerdSeq.h"

NerdSeq::NerdSeq()
   : Svin::Module()
   , Svin::Midi::Input(Midi::Device::FromNerdSEQ)
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
   , busMessage()
{
   setup();
   registerAsBusModule<Svin::Midi::Bus>();

   connectionButton.setDefaultColor(Color::Predefined::Green);
   connectToMidiDevice();
}

void NerdSeq::process(const ProcessArgs& args)
{
   if (connectionButton.isTriggered())
      connectToMidiDevice();

   busMessage.runState = Tempo::Running;
   sendBusData<Svin::Midi::Bus>(Side::Right, busMessage);

   busMessage = Svin::Midi::Bus{}; // reset
}

void NerdSeq::connectToMidiDevice()
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

void NerdSeq::processMessage(const Bytes& message)
{
   const bool isSystemEvent = (0xF0 == (message[0] & 0xF0));
   if (!isSystemEvent)
   {
      const Midi::Event event = static_cast<Midi::Event>(message[0] & 0xF0);

      busMessage.noOfChannels = 16;
      const uint8_t channelNo = (message[0] & 0x0F);
      Svin::Midi::Bus::Channel& channelRef = busMessage.channels[channelNo];

      switch (event)
      {
         case Midi::Event::NoteOn:
         case Midi::Event::NoteOff:
         case Midi::Event::ControlChange:
         {
            channelRef.messageList.push_back(message);
            channelRef.hasEvents = true;
            return;
         }
         default:
         {
            break;
         }
      }
   }
   busMessage.otherMessageList.push_back(message);
}

// widget

NerdSeqWidget::NerdSeqWidget(NerdSeq* module)
: Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelNerdSeq = Svin::Origin::the()->addModule<NerdSeq, NerdSeqWidget>("NerdSeq");

