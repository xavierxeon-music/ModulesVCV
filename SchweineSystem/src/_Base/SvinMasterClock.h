#ifndef SvinMasterClockH
#define SvinMasterClockH

#include <list>
#include <mutex>

#include <Music/Tempo.h>
#include <Music/TimeCode.h>

namespace Svin
{
   class MasterClock
   {
   public:
      class Client
      {
      public:
         using List = std::list<Client*>;

      protected:
         Client();
         ~Client();

      protected:
         bool hasTick(bool* isFirstTick);
         bool hasMidiSubTick();
         bool hasReset();
         Tempo getTempo() const;
         TimeCode::Duration getDuration() const;

      private:
         friend class MasterClock;

      private:
         mutable std::mutex mutex;
         bool firstTick;
         uint8_t tickCount;
         uint8_t midiSubTicks;
         bool reset;
      };

   protected:
      MasterClock();
      ~MasterClock();

   protected:
      bool iAmMasterClock() const;
      void tick();
      void addMidiSubTicks();
      void reset();
      void advance(const float& sampleRate);

      Tempo getTempo() const;
      const TimeCode::Duration& getDuration() const;

   private:
      static std::list<MasterClock*> instanceList;
      static MasterClock* masterInstance;
      static Client::List clientList;
      mutable std::mutex mutex;

      TempoControl tempo;
      TimeCode::Duration duration;
   };

} // namespace Svin

#endif // NOT SvinMasterClockH
