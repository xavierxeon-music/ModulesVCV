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
      // communicate with external helper apps via midi

      class Majordomo
      {
      public:
         static void hello(Svin::Module* server);
         static void bye(Svin::Module* server);
         static void send(const Queue& messages);
         static void process();

      private:
         Majordomo();
         void start();
         void stop();
         static void midiReceive(double timeStamp, std::vector<unsigned char>* message, void* userData);
         static void midiError(RtMidiError::Type type, const std::string& errorText, void* userData);

      private:
         static Majordomo* me;
         std::mutex mutex;
         RtMidiIn midiInput;
         RtMidiOut midiOutput;
         static Queue sendBuffer;
         std::vector<Svin::Module*> instanceList;
      };

   protected:
      virtual void dataFromMidiInput(const Bytes& message);
      virtual void load(const Json::Object& rootObject);
      virtual void save(Json::Object& rootObject);

   private:
      void dataFromJson(json_t* rootJson) override final;
      json_t* dataToJson() override final;
   };
} // namespace Svin

#endif // NOT SvinModuleH
