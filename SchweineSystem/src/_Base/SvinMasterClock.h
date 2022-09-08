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
         bool hasTick();
         bool hasMidiClock();
         bool hasReset();
         Tempo getTempo() const;
         TimeCode::Duration getDuration() const;

      private:
         friend class MasterClock;

      private:
         mutable std::mutex mutex;
         uint8_t tickCount;
         uint8_t midiClock;
         bool reset;
      };

   protected:
      MasterClock();
      ~MasterClock();

   protected:
      bool iAmMasterClock() const;
      void tick();
      void midiClock();
      void reset();
      void advance(const float& sampleRate);

      Tempo getTempo() const;
      const TimeCode::Duration& getDuration() const;

   private:
      static MasterClock* me;
      static Client::List clientList;
      mutable std::mutex mutex;

      Tempo::Control tempo;
      TimeCode::Duration duration;
   };

} // namespace Svin

#endif // NOT SvinMasterClockH
