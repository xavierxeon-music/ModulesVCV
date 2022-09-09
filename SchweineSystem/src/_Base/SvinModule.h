#ifndef SvinModuleH
#define SvinModuleH

#include <rack.hpp>

#include <rtmidi/RtMidi.h>

#include <MusicTools.h>

#include "SvinJson.h"

namespace Svin
{
   class Module : public rack::Module
   {
   public:
      using Queue = std::list<Bytes>;

   public:
      Module();

   public:
      virtual void updateDisplays();
      std::string getOpenFileName(const std::string& filter) const;

   protected:
      virtual void load(const Json::Object& rootObject);
      virtual void save(Json::Object& rootObject);
      float getSampleRate() const;

   private:
      void dataFromJson(json_t* rootJson) override final;
      json_t* dataToJson() override final;
   };
} // namespace Svin

#endif // NOT SvinModuleH
