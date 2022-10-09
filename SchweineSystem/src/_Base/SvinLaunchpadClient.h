#ifndef SvinLaunchpadClientH
#define SvinLaunchpadClientH

#include "SvinMasterClock.h"
#include "SvinMidi.h"

namespace Svin
{
   class LaunchpadClient : private Midi::Input, private Midi::Output, private MasterClock::Client
   {
   public:
      enum class Mode : uint8_t //
      {
         Off = 0,
         Steady = 1,
         Flash = 2,
         Pulse = 3
      };

      struct Pad
      {
         const uint8_t row;
         const uint8_t column;

         using List = std::vector<Pad>;
      };

   public:
      LaunchpadClient();
      ~LaunchpadClient();

   public:
      Pad::List update(); // send clock and return triggerd pads

      bool connect(const uint8_t& deviceId);
      void setPad(const uint8_t& row, const uint8_t& column, const Mode& mode = Mode::Off, const Color& color = Color());

   private:
      void switchToProgramMode();
      void switchToLiveMode();

      void noteOn(const ::Midi::Channel& channel, const Note& note, const ::Midi::Velocity& velocity) override;
      void controllerChange(const ::Midi::Channel& channel, const ::Midi::ControllerMessage& controllerMessage, const uint8_t& value) override;

   private:
      static const std::vector<std::string> hexColorsMk2;
      Pad::List triggerCache;
      Tempo::RunState oldRunState;
   };
} // namespace Svin

#endif // NOT SvinLaunchpadClientH
