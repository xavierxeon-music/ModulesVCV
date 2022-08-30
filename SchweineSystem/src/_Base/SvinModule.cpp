#include "SvinModule.h"

#include <osdialog.h>

// majordomo

Svin::Module::Majordomo* Svin::Module::Majordomo::me = nullptr;
Svin::Module::Queue Svin::Module::Majordomo::sendBuffer = Svin::Module::Queue();

using LockGuard = std::lock_guard<std::mutex>;

void Svin::Module::Majordomo::hello(Svin::Module* server)
{
   if (!me)
      me = new Majordomo();

   const LockGuard lock(me->mutex);

   if (0 == me->instanceList.size())
      me->start();

   me->instanceList.push_back(server);
}

void Svin::Module::Majordomo::bye(Svin::Module* server)
{
   if (!me)
      return;

   const LockGuard lock(me->mutex);

   std::vector<Svin::Module*>::iterator it = std::find(me->instanceList.begin(), me->instanceList.end(), server);
   if (it != me->instanceList.end())
      me->instanceList.erase(it);

   if (0 == me->instanceList.size())
      me->stop();
}

void Svin::Module::Majordomo::send(const Queue& messages)
{
   if (!me)
      return;

   const LockGuard lock(me->mutex);

   sendBuffer.insert(sendBuffer.end(), messages.begin(), messages.end());
}

void Svin::Module::Majordomo::process()
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

Svin::Module::Majordomo::Majordomo()
   : mutex()
   , midiInput()
   , midiOutput()
   , instanceList()
{
}

void Svin::Module::Majordomo::start()
{
   midiInput.openVirtualPort("Majordomo");

   midiInput.setErrorCallback(&Majordomo::midiError);
   midiInput.setCallback(&Majordomo::midiReceive, this);
   midiInput.ignoreTypes(false, false, false); // do not ignore anything

   midiOutput.openVirtualPort("Majordomo");
   midiOutput.setErrorCallback(&Majordomo::midiError);
}

void Svin::Module::Majordomo::stop()
{
   midiInput.closePort();
}

void Svin::Module::Majordomo::midiReceive(double timeStamp, std::vector<unsigned char>* message, void* userData)
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

      for (Module* module : me->instanceList)
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

void Svin::Module::Majordomo::midiError(RtMidiError::Type type, const std::string& errorText, void* userData)
{
   if (me != userData)
      return;

   std::cout << "MIDI ERROR: " << type << ",  " << errorText << std::endl;
}

// module

Svin::Module::Module()
   : rack::Module()
{
}

void Svin::Module::updateDisplays()
{
   // do nothing
}

std::string Svin::Module::getOpenFileName(const std::string& filter) const
{
   const char* path = osdialog_file(OSDIALOG_OPEN, nullptr, nullptr, osdialog_filters_parse(filter.c_str()));
   if (path)
      return std::string(path);
   else
      return std::string();
}

void Svin::Module::dataFromMidiInput(const Bytes& message)
{
   (void)message;
   // do nothing
}

void Svin::Module::load(const Json::Object& rootObject)
{
   (void)rootObject;
   // do nothing
}

void Svin::Module::save(Json::Object& rootObject)
{
   (void)rootObject;
   // do nothing
}

void Svin::Module::dataFromJson(json_t* rootJson)
{
   const Json::Object rootObject(rootJson);
   load(rootObject);
}

json_t* Svin::Module::dataToJson()
{
   Json::Object rootObject;
   save(rootObject);

   return rootObject.toJson();
}
