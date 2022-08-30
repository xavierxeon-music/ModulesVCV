#ifndef SvinMasterClockH
#define SvinMasterClockH

#include <Music/Tempo.h>
#include <Music/TimeCode.h>

namespace Svin
{
   class MasterClock
   {
   public:
      enum class Signal
      {
         Reset,
         Tick,
         None
      };

   public:
      static const MasterClock* the();
      const Signal& getSignal() const;
      const Tempo& getTempo() const;
      const TimeCode::Duration& getDuration() const;

   protected:
      MasterClock();
      ~MasterClock();

   protected:
      bool iAmMasterClock() const;
      void reset();
      void tick();
      void advance(const float& sampleRate);

   private:
      static MasterClock* me;

      Signal signal;
      Tempo tempo;
      TimeCode::Duration duration;
   };
} // namespace Svin

#endif // NOT SvinMasterClockH
