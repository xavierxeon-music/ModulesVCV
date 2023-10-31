#ifndef SvinMidiH
#define SvinMidiH

#include <Midi/MidiParser.h>

#include <rack.hpp>

#include <map>

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
      MidiCommon();

   protected:
      void setTargetDeviceName(const std::string& newTargetDeviceName);
      int findDeviceId(rack::midi::Port* port, bool verbose) const;

   protected:
      std::string targetDeviceName;
   };

   class MidiOutput : public MidiCommon, private rack::midi::Output
   {
   public:
      MidiOutput();
      MidiOutput(const std::string& targetDeviceName);
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
   };

   class MidiInput : public MidiCommon, public Midi::Parser, private rack::midi::Input
   {
   public:
      MidiInput();
      MidiInput(const std::string& targetDeviceName);
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
      void onMessage(const rack::midi::Message& message) override;

   private:
      BufferMap docBufferMap;
   };

} // namespace Svin

#endif // NOT SvinMidiH
