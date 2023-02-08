#ifndef MidiBusModuleH
#define MidiBusModuleH

#include <rack.hpp>
using namespace rack;

#include <SvinMidi.h>
#include <SvinModule.h>

#include <Midi/MidiFile.h>
#include <Music/Tempo.h>

namespace Svin
{
   namespace MidiBus
   {
      struct Message
      {
         struct Channel
         {
            ::Midi::Sequence::MessageList messageList;
            bool hasEvents = false;
         };

         Tempo::RunState runState = Tempo::Reset;
         uint8_t noOfChannels = 0;
         Channel channels[16];
      };

      class Module : protected Svin::Midi::Output
      {
      public:
         Module(const ::Midi::Device::Channel& deviceChannel, Svin::Module* module);

      protected:
         void processBusMessage(const Message& busMessage);

      private:
         struct NoteBuffer
         {
            const uint8_t channel = 0;
            const uint8_t key = 0;

            NoteBuffer(uint8_t channel, uint8_t key);
            bool operator==(const NoteBuffer& other) const;

            using List = std::list<NoteBuffer>;
         };

      private:
         NoteBuffer::List bufferList;
         bool wasRunning;
      };
   } // namespace MidiBus
} // namespace Svin

#endif // NOT MidiBusModuleH
