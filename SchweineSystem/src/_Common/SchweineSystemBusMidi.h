#ifndef SchweineSystemBusMidiH
#define SchweineSystemBusMidiH

#include <Blocks/Sequencer.h>
#include <Midi/MidiCommon.h>

namespace SchweineSystem
{
   struct BusMidi
   {
      Sequencer::Track::NoteEvent::List offEventList;
      Sequencer::Track::NoteEvent::List onEventList;
   };
} // namespace SchweineSystem

#endif // NOT SchweineSystemBusMidiH
