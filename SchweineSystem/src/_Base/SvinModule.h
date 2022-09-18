#ifndef SvinModuleH
#define SvinModuleH

#include <rack.hpp>

#include <rtmidi/RtMidi.h>

#include <MusicTools.h>

#include <SvinJson.h>
#include <SvinMidi.h>

namespace Svin
{
   class Module : public rack::Module
   {
   public:
      using Queue = std::list<Bytes>;

   public:
      Module();
      ~Module();

   public:
      virtual void updateDisplays();
      std::string getOpenFileName(const std::string& filter) const;

   protected:
      virtual void load(const Json::Object& rootObject);
      virtual void save(Json::Object& rootObject);
      float getSampleRate() const;
      // hub client
      bool hubConnected();
      void connectToHub();
      bool registerHubClient(const std::string& name);
      void sendDocumentToHub(const ::Midi::Channel& channel, const Json::Object& object, const uint8_t docIndex = 0);
      virtual void receivedDocumentFromHub(const ::Midi::Channel& channel, const Json::Object& object, const uint8_t docIndex);

   private:
      using Map = std::map<std::string, Module*>;

      class Majordomo : public Svin::Midi::Input, public Svin::Midi::Output
      {
      public:
         Majordomo();
         ~Majordomo();

      public:
         bool add(Module* module, const std::string& name); // true if name not aready registerred
         bool remove(Module* module);                       // true if no more modules are registerred
         bool connected();
         void tryConnect();

      private:
         void document(const ::Midi::Channel& channel, const Json::Object& object, const uint8_t docIndex) override;

      private:
         Map moduleMap;
      };

   private:
      void dataFromJson(json_t* rootJson) override final;
      json_t* dataToJson() override final;

   private:
      static Majordomo* majordomo;
   };
} // namespace Svin

#endif // NOT SvinModuleH
