#include "SchweineSystemModule.h"

// majordomo

SchweineSystem::Module::Majordomo *SchweineSystem::Module::Majordomo::me = nullptr;
SchweineSystem::Module::Queue SchweineSystem::Module::Majordomo::sendBuffer = SchweineSystem::Module::Queue();

using LockGuard = std::lock_guard<std::mutex>;

void SchweineSystem::Module::Majordomo::hello(SchweineSystem::Module *server)
{
   if (!me)
      me = new Majordomo();

   const LockGuard lock(me->mutex);

   if (0 == me->instanceList.size())
      me->start();

   me->instanceList.push_back(server);
}

void SchweineSystem::Module::Majordomo::bye(SchweineSystem::Module *server)
{
   if (!me)
      return;

   const LockGuard lock(me->mutex);

   std::vector<SchweineSystem::Module *>::iterator it = std::find(me->instanceList.begin(), me->instanceList.end(), server);
   if (it != me->instanceList.end())
      me->instanceList.erase(it);

   if (0 == me->instanceList.size())
      me->stop();
}

void SchweineSystem::Module::Majordomo::send(const Queue &messages)
{
   if (!me)
      return;

   const LockGuard lock(me->mutex);

   sendBuffer.insert(sendBuffer.end(), messages.begin(), messages.end());
}

void SchweineSystem::Module::Majordomo::process()
{
   if (!me)
      return;

   std::lock_guard<std::mutex> lock(me->mutex, std::try_to_lock);
   if (!lock.owns_lock())
      return;

   if (!sendBuffer.empty())
   {
      const Bytes bytes = sendBuffer.front();
      sendBuffer.pop_front();

      me->midiOutput.sendMessage(&bytes);
   }
}

SchweineSystem::Module::Majordomo::Majordomo()
    : mutex(), midiInput(), midiOutput(), instanceList()
{
}

void SchweineSystem::Module::Majordomo::start()
{
   midiInput.openVirtualPort("Majordomo");

   midiInput.setErrorCallback(&Majordomo::midiError);
   midiInput.setCallback(&Majordomo::midiReceive, this);
   midiInput.ignoreTypes(false, false, false); // do not ignore anything

   midiOutput.openVirtualPort("Majordomo");
   midiOutput.setErrorCallback(&Majordomo::midiError);
}

void SchweineSystem::Module::Majordomo::stop()
{
   midiInput.closePort();
}

void SchweineSystem::Module::Majordomo::midiReceive(double timeStamp, std::vector<unsigned char> *message, void *userData)
{
   (void)timeStamp;

   if (me != userData)
      return;

   if (!message)
      return;

   static Bytes buffer;
   auto maybeProcessBuffer = [&]()
   {
      if (0 == buffer.size())
         return;

      for (Module *module : me->instanceList)
         module->dataFromMidiInput(buffer);
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

void SchweineSystem::Module::Majordomo::midiError(RtMidiError::Type type, const std::string &errorText, void *userData)
{
   if (me != userData)
      return;

   std::cout << "MIDI ERROR: " << type << ",  " << errorText << std::endl;
}

// module

SchweineSystem::Module::Module()
    : rack::Module(), texts(), values(), pixels()
{
}

void SchweineSystem::Module::updateDisplays()
{
   // do nothing
}

void SchweineSystem::Module::configText(const uint16_t &textId, std::string name)
{
   texts[textId] = std::string();
}

void SchweineSystem::Module::configMeter(const uint16_t &valueId, std::string name)
{
   values[valueId] = 0.0;
}

void SchweineSystem::Module::configPixels(const uint16_t &valueId, const uint8_t &width, const uint8_t &height, std::string name)
{
   const uint16_t size = width * height;
   pixels[valueId] = new NVGcolor[size];
}

void SchweineSystem::Module::dataFromMidiInput(const Bytes &message)
{
   (void)message;
   // do nothing
}
