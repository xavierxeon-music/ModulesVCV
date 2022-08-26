#include "SyModule.h"

// majordomo

Sy::Module::Majordomo *Sy::Module::Majordomo::me = nullptr;
Sy::Module::Queue Sy::Module::Majordomo::sendBuffer = Sy::Module::Queue();

using LockGuard = std::lock_guard<std::mutex>;

void Sy::Module::Majordomo::hello(Sy::Module *server)
{
   if (!me)
      me = new Majordomo();

   const LockGuard lock(me->mutex);

   if (0 == me->instanceList.size())
      me->start();

   me->instanceList.push_back(server);
}

void Sy::Module::Majordomo::bye(Sy::Module *server)
{
   if (!me)
      return;

   const LockGuard lock(me->mutex);

   std::vector<Sy::Module *>::iterator it = std::find(me->instanceList.begin(), me->instanceList.end(), server);
   if (it != me->instanceList.end())
      me->instanceList.erase(it);

   if (0 == me->instanceList.size())
      me->stop();
}

void Sy::Module::Majordomo::send(const Queue &messages)
{
   if (!me)
      return;

   const LockGuard lock(me->mutex);

   sendBuffer.insert(sendBuffer.end(), messages.begin(), messages.end());
}

void Sy::Module::Majordomo::process()
{
   if (!me)
      return;

   if (!me->mutex.try_lock())
      return;

   if (!sendBuffer.empty())
   {
      const Bytes bytes = sendBuffer.front();
      sendBuffer.pop_front();

      me->midiOutput.sendMessage(&bytes);
   }

   me->mutex.unlock();
}

Sy::Module::Majordomo::Majordomo()
    : mutex(), midiInput(), midiOutput(), instanceList()
{
}

void Sy::Module::Majordomo::start()
{
   midiInput.openVirtualPort("Majordomo");

   midiInput.setErrorCallback(&Majordomo::midiError);
   midiInput.setCallback(&Majordomo::midiReceive, this);
   midiInput.ignoreTypes(false, false, false); // do not ignore anything

   midiOutput.openVirtualPort("Majordomo");
   midiOutput.setErrorCallback(&Majordomo::midiError);
}

void Sy::Module::Majordomo::stop()
{
   midiInput.closePort();
}

void Sy::Module::Majordomo::midiReceive(double timeStamp, std::vector<unsigned char> *message, void *userData)
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

void Sy::Module::Majordomo::midiError(RtMidiError::Type type, const std::string &errorText, void *userData)
{
   if (me != userData)
      return;

   std::cout << "MIDI ERROR: " << type << ",  " << errorText << std::endl;
}

// module

Sy::Module::Module()
    : rack::Module(), texts(), values(), pixels()
{
}

void Sy::Module::updateDisplays()
{
   // do nothing
}

void Sy::Module::configText(const uint16_t &textId, std::string name)
{
   texts[textId] = std::string();
}

void Sy::Module::configMeter(const uint16_t &valueId, std::string name)
{
   values[valueId] = 0.0;
}

void Sy::Module::configPixels(const uint16_t &valueId, const uint8_t &width, const uint8_t &height, std::string name)
{
   const uint16_t size = width * height;
   pixels[valueId] = new NVGcolor[size];
}

void Sy::Module::dataFromMidiInput(const Bytes &message)
{
   (void)message;
   // do nothing
}

void Sy::Module::load(const Json::Object& rootObject)
{
   (void)rootObject;
   // do nothing
}

void Sy::Module::save(Json::Object& rootObject)
{
   (void)rootObject;
   // do nothing
}

void Sy::Module::dataFromJson(json_t* rootJson)
{
   const Json::Object rootObject(rootJson);
   load(rootObject);
}

json_t* Sy::Module::dataToJson()
{
   Json::Object rootObject;
   save(rootObject);

   return rootObject.toJson();
}
