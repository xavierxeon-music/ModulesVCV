#include "SvinModule.h"

#include <osdialog.h>

// majordomo

Svin::Module::Majordomo::Majordomo()
   : Svin::MidiInput("HubVCV", false)
   , Svin::MidiOutput("HubVCV", false)
   , moduleMap()
{
   tryConnect();
}

Svin::Module::Majordomo::~Majordomo()
{
   MidiInput::close();
   MidiOutput::close();
}

bool Svin::Module::Majordomo::add(Module* module, const std::string& name)
{
   if (moduleMap.find(name) != moduleMap.end()) // already resgistered  mdoule with that name
      return false;

   moduleMap[name] = module;
   return true;
}

bool Svin::Module::Majordomo::remove(Module* module)
{
   for (Map::iterator it = moduleMap.begin(); it != moduleMap.end(); it++)
   {
      if (module != it->second)
         continue;

      moduleMap.erase(it);
      break;
   }

   return moduleMap.empty();
}

bool Svin::Module::Majordomo::connected()
{
   return (MidiInput::connected() && MidiOutput::connected());
}

void Svin::Module::Majordomo::tryConnect()
{
   if (!MidiInput::connected())
      MidiInput::open();

   if (!MidiOutput::connected())
      MidiOutput::open();
}

void Svin::Module::Majordomo::document(const ::Midi::Channel& channel, const Json::Object& object, const uint8_t docIndex)
{
   const std::string appName = object.get("_Application").toString();

   if (moduleMap.find(appName) == moduleMap.end())
      return;

   moduleMap[appName]->receivedDocumentFromHub(channel, object, docIndex);
}

// bus abstract

Svin::Module::BusAbstract::List Svin::Module::BusAbstract::busList;

Svin::Module::BusAbstract::BusAbstract()
{
}

Svin::Module::BusAbstract::~BusAbstract()
{
}

void Svin::Module::BusAbstract::removeModuleFromAllBuses(Module* module)
{
   for (BusAbstract* bus : busList)
      bus->removeModule(module);
}

// module

Svin::Module::Majordomo* Svin::Module::majordomo = nullptr;

Svin::Module::Module()
   : rack::Module()
{
}

Svin::Module::~Module()
{
   if (majordomo && majordomo->remove(this))
   {
      delete majordomo;
      majordomo = nullptr;
   }

   BusAbstract::removeModuleFromAllBuses(this);
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

float Svin::Module::getSampleRate() const
{
   return APP->engine->getSampleRate();
}

bool Svin::Module::hubConnected()
{
   if (!majordomo)
      return false;

   return majordomo->connected();
}
void Svin::Module::connectToHub()
{
   if (!majordomo)
      return;

   majordomo->tryConnect();
}

bool Svin::Module::registerHubClient(const std::string& name)
{
   if (!majordomo)
      majordomo = new Majordomo();

   return majordomo->add(this, name);
}

void Svin::Module::sendDocumentToHub(const ::Midi::Channel& channel, const Json::Object& object, const uint8_t docIndex)
{
   if (!majordomo)
      return;

   majordomo->sendDocument(channel, object, docIndex);
}

void Svin::Module::receivedDocumentFromHub(const ::Midi::Channel& channel, const Json::Object& object, const uint8_t docIndex)
{
   (void)channel;
   (void)object;
   (void)docIndex;
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
