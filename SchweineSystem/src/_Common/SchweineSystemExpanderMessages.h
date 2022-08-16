#ifndef SchweineSystemExpanderMessagesH
#define SchweineSystemExpanderMessagesH

#include <Blocks/Sequencer.h>
#include <Midi/MidiCommon.h>

namespace SchweineSystem
{
   struct BusMidi
   {
      struct Channel
      {
         Sequencer::Track::NoteEvent::TimeMap noteOffEventMap;
         Sequencer::Track::NoteEvent::TimeMap noteOnEventMap;
         bool isMonophoic = false;
      };

      Sequencer::Tick startTick = 0;
      Sequencer::Tick endTick = 0;

      uint8_t noOfChannels = 0;
      Channel channels[16];
   };
} // namespace SchweineSystem

#endif // NOT SchweineSystemExpanderMessagesH
