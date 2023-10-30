#ifndef SvinMidiH
#define SvinMidiH

#include <Midi/MidiParser.h>

#include <map>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#include <rtmidi/RtMidi.h>
#pragma GCC diagnostic pop

#include <Midi/MidiCommon.h>
#include <Music/Note.h>
#include <Music/Tempo.h>
#include <MusicTools.h>

#include <SvinJson.h>

namespace Svin
{

   // midi channels range from 1 -16

   struct MidiBus
   {
      struct Channel
      {
         Midi::MessageList messageList;
         bool hasEvents = false;
      };

      Tempo::RunState runState = Tempo::Reset;
      uint8_t noOfChannels = 0;
      Channel channels[16];

      Midi::MessageList otherMessageList;
   };

   class MidiCommon
   {
   public:
      using InterfaceMap = std::map<Midi::Device::Channel, std::string>;
      static const InterfaceMap interfaceMap;

   protected:
      MidiCommon(bool isVirtual);

   protected:
      static void midiError(RtMidiError::Type type, const std::string& errorText, void* userData);
      void setTargetDeviceName(const std::string& newTargetDeviceName);

   protected:
      bool isVirtual;
      bool virtualOpen;
      std::string targetDeviceName;
   };

   class MidiOutput : public MidiCommon
   {
   public:
      MidiOutput(bool isVirtual);
      MidiOutput(const std::string& targetDeviceName, bool isVirtual = false);
      MidiOutput(const Midi::Device::Channel& deviceChannel);
      virtual ~MidiOutput();

   public:
      bool open(bool verbose = false);
      void close();
      bool connected();

      void sendNoteOn(const Midi::Channel& channel, const uint8_t& midiNote, const Midi::Velocity& velocity);
      void sendNoteOff(const Midi::Channel& channel, const uint8_t& midiNote);
      void sendControllerChange(const Midi::Channel& channel, const Midi::ControllerMessage& controllerMessage, const uint8_t& value);
      void sendDocument(const Midi::Channel& channel, const Json::Object& object, const uint8_t docIndex = 0);

   protected:
      void sendMessage(const Bytes& message);

   private:
      RtMidiOut midiOutput;
   };

   class MidiInput : public MidiCommon, public Midi::Parser
   {
   public:
      MidiInput(bool isVirtual);
      MidiInput(const std::string& targetDeviceName, bool isVirtual = false);
      MidiInput(const Midi::Device::Channel& deviceChannel);
      virtual ~MidiInput();

   public:
      bool open(bool verbose = false);
      void close();
      bool connected();

      virtual void controllerChange(const Midi::Channel& channel, const Midi::ControllerMessage& controllerMessage, const uint8_t& value) override;
      virtual void document(const Midi::Channel& channel, const Json::Object& object, const uint8_t docIndex);

   private:
      using BufferMap = std::map<Midi::Channel, std::string>;

   private:
      static void midiReceive(double timeStamp, std::vector<unsigned char>* message, void* userData);

   private:
      RtMidiIn midiInput;
      BufferMap docBufferMap;
   };

} // namespace Svin

#endif // NOT SvinMidiH
