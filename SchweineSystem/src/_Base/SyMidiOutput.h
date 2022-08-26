#ifndef SyMidiOutputH
#define SyMidiOutputH

#include <map>

#include <rtmidi/RtMidi.h>

#include <Midi/MidiCommon.h>
#include <Music/Note.h>
#include <MusicTools.h>

namespace Sy
{
   struct Common
   {
      using MidiInterfaceMap = std::map<Midi::Device::Channel, std::string>;
      static const MidiInterfaceMap midiInterfaceMap;
   };

   class MidiOutput
   {
   public:
      MidiOutput(const std::string& targetDeviceName);
      MidiOutput(const Midi::Device::Channel& deviceChannel);
      virtual ~MidiOutput();

   public:
      bool open();
      void close();
      bool connected();

      void sendNoteOn(const Midi::Channel& channel, const Note& note, const Midi::Velocity& velocity);
      void sendNoteOff(const Midi::Channel& channel, const Note& note);
      void sendControllerChange(const Midi::Channel& channel, const Midi::ControllerMessage& controllerMessage, const uint8_t& value);

   protected:
      void sendMessage(const std::vector<uint8_t>& message);

   private:
      const std::string targetDeviceName;
      RtMidiOut midiOutput;
   };
} // namespace Sy

#endif // NOT SyMidiOutputH
