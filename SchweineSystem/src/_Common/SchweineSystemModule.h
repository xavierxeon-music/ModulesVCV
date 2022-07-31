#ifndef SchweineSystemModuleH
#define SchweineSystemModuleH

#include <rack.hpp>

#include <rtmidi/RtMidi.h>

#include <MusicTools.h>

namespace SchweineSystem
{
   class Module : public rack::Module
   {
   public:
      using TextMap = std::map<uint16_t, std::string>;
      using ValueMap = std::map<uint16_t, float>;
      using PixelMap = std::map<uint16_t, NVGcolor*>;
      using Queue = std::list<Bytes>;

   public:
      Module();

   public:
      virtual void updateDisplays();

   public:
      TextMap texts;
      ValueMap values;
      PixelMap pixels;

   protected:
      // communicate with external helper apps via midi
      class Majordomo
      {
      public:
         static void hello(SchweineSystem::Module* server);
         static void bye(SchweineSystem::Module* server);
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
         std::vector<SchweineSystem::Module*> instanceList;
      };

   protected:
      void configText(const uint16_t& textId, std::string name = "");
      void configMeter(const uint16_t& valueId, std::string name = "");
      void configPixels(const uint16_t& valueId, const uint8_t& width, const uint8_t& height, std::string name = "");
      virtual void dataFromMidiInput(const Bytes& message);
   };
} // namespace SchweineSystem

#endif // NOT SchweineSystemModuleH
