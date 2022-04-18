#include "TimeLordServer.h"
#include "TimeLordServerPanel.h"

#include <Midi/MidiCommon.h>

#include "SchweineSystemMaster.h"

TimeLordServer::TimeLordServer()
   : Module()
   , input()
{
   setup();
   input.openVirtualPort("TimeLordServer");

   input.setErrorCallback(&TimeLordServer::midiError);
   input.setCallback(&TimeLordServer::midiReceive, this);
   input.ignoreTypes(false, false, false); // do not ignore anything
}

TimeLordServer::~TimeLordServer()
{
   input.closePort();
}

void TimeLordServer::process(const ProcessArgs& args)
{
}

void TimeLordServer::dataFromInput(const Bytes& message)
{
   static Bytes buffer;

   const bool isSystemEvent = (0xF0 == (message[0] & 0xF0));
   if (isSystemEvent)
      return;

   const Midi::Event event = static_cast<Midi::Event>(message[0] & 0xF0);
   const Midi::Channel channel = 1 + (message[0] & 0x0F);
   if (11 != channel)
      return;

   if (Midi::Event::ControlChange != event)
      return;

   const Midi::ControllerMessage controllerMessage = static_cast<Midi::ControllerMessage>(message[1]);
   const uint8_t value = message[2];

   if (Midi::ControllerMessage::RememberBlock == controllerMessage)
   {
      buffer << value;
   }
   else if (Midi::ControllerMessage::RememberApply == controllerMessage)
   {
      // convert to JSON and load
      buffer.clear();
   }
}

void TimeLordServer::midiReceive(double timeStamp, std::vector<unsigned char>* message, void* userData)
{
   (void)timeStamp;

   if (!message || !userData)
      return;

   TimeLordServer* me = reinterpret_cast<TimeLordServer*>(userData);
   if (!me)
      return;

   static Bytes buffer;
   auto maybeProcessBuffer = [&]()
   {
      if (0 == buffer.size())
         return;

      me->dataFromInput(buffer);
      buffer.clear();
   };

   static const uint8_t mask = 0x80;
   for (const uint8_t byte : *message)
   {
      const uint8_t test = byte & mask;
      if (test == mask) // new message start
         maybeProcessBuffer();

      buffer.push_back(byte);
   }
   maybeProcessBuffer();
}

void TimeLordServer::midiError(RtMidiError::Type type, const std::string& errorText, void* userData)
{
   (void)userData;
   std::cout << "MIDI ERROR: " << type << ",  " << errorText << std::endl;
}

TimeLordServerWidget::TimeLordServerWidget(TimeLordServer* module)
: ModuleWidget()
{
   SvgPanel* mainPanel = setup(module);
   (void)mainPanel;
}

Model* modelTimeLordServer = SchweineSystem::Master::the()->addModule<TimeLordServer, TimeLordServerWidget>("TimeLordServer");

