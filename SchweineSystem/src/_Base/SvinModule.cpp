#include "SvinModule.h"

#include <osdialog.h>

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
