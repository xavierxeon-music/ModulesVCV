#ifndef SvinMidiH
#define SvinMidiH

#include <map>

#include <rtmidi/RtMidi.h>

#include <Midi/MidiCommon.h>
#include <Music/Note.h>
#include <MusicTools.h>

#include <SvinJson.h>

namespace Svin
{

   // midi channels range from 1 -16
   namespace Midi
   {
      class Common
      {
      public:
         using InterfaceMap = std::map<::Midi::Device::Channel, std::string>;
         static const InterfaceMap interfaceMap;

      protected:
         Common(const std::string& targetDeviceName, bool isVirtual = false);

      protected:
         static void midiError(RtMidiError::Type type, const std::string& errorText, void* userData);

      protected:
         bool isVirtual;
         bool virtualOpen;
         const std::string targetDeviceName;
      };

      class Output : public Common
      {
      public:
         Output(const std::string& targetDeviceName, bool isVirtual = false);
         Output(const ::Midi::Device::Channel& deviceChannel);
         virtual ~Output();

      public:
         bool open();
         void close();
         bool connected();

         void sendNoteOn(const ::Midi::Channel& channel, const Note& note, const ::Midi::Velocity& velocity);
         void sendNoteOff(const ::Midi::Channel& channel, const Note& note);
         void sendControllerChange(const ::Midi::Channel& channel, const ::Midi::ControllerMessage& controllerMessage, const uint8_t& value);
         void sendDocument(const ::Midi::Channel& channel, const Json::Object& object, const uint8_t docIndex = 0);

      protected:
         void sendMessage(const std::vector<uint8_t>& message);

      private:
         RtMidiOut midiOutput;
      };

      class Input : public Common
      {
      public:
         Input(const std::string& targetDeviceName, bool isVirtual = false);
         Input(const ::Midi::Device::Channel& deviceChannel);
         virtual ~Input();

      public:
         bool open();
         void close();
         bool connected();

         virtual void clockTick();
         virtual void songPosition(const uint16_t position);

         virtual void noteOn(const ::Midi::Channel& channel, const Note& note, const ::Midi::Velocity& velocity);
         virtual void noteOff(const ::Midi::Channel& channel, const Note& note);
         virtual void controllerChange(const ::Midi::Channel& channel, const ::Midi::ControllerMessage& controllerMessage, const uint8_t& value);
         virtual void document(const ::Midi::Channel& channel, const Json::Object& object, const uint8_t docIndex);

      private:
         using BufferMap = std::map<::Midi::Channel, std::string>;

      private:
         static void midiReceive(double timeStamp, std::vector<unsigned char>* message, void* userData);
         void prcocess(const Bytes& buffer);

      private:
         RtMidiIn midiInput;
         BufferMap docBufferMap;
      };
   } // namespace Midi
} // namespace Svin

#endif // NOT SvinMidiH
