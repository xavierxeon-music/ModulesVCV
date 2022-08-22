#ifndef MidiBusModuleH
#define MidiBusModuleH

#include <rack.hpp>
using namespace rack;

#include <SyExapnder.h>
#include <SyMidiOutput.h>
#include <SyModule.h>

#include "../Utilities/MidiReplay.h"

class MidiBusModule : protected Sy::MidiOutput, public Sy::Exapnder<BusMidi>
{
public:
   MidiBusModule(const Midi::Device::Channel& deviceChannel, Sy::Module* module);

protected:
   void processBusMessage(const BusMidi& busMessage);

private:
   struct NoteBuffer
   {
      const uint8_t channel = 0;
      const uint8_t key = 0;

      NoteBuffer(uint8_t channel, uint8_t key);
      bool operator==(const NoteBuffer& other) const;

      using List = std::list<NoteBuffer>;
   };

   friend std::ostream& operator<<(std::ostream& os, const NoteBuffer& buffer);

private:
   NoteBuffer::List bufferList;
   bool wasRunning;
};

#endif // NOT MidiBusModuleH
