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

      enum class Button : uint8_t //
      {
         Off,
         On,
         Triggerd

      };

      struct Pad
      {
         uint8_t row;
         uint8_t column;
         Button button;

         using Map = std::map<uint8_t, Pad>; // midiNote vs Pad
         using List = std::vector<Pad>;
      };

   public:
      LaunchpadClient();
      ~LaunchpadClient();

   public:
      void update();             // send clock
      Pad::List triggeredPads(); // return triggerd pads

      void showColorTest(bool firstPage);

      void disconnect();
      void connect(const uint8_t& deviceId);
      bool isConnected();

      void setPad(const uint8_t& row, const uint8_t& column, const Mode& mode = Mode::Off, const Color& color = Color());
      void setPad(const uint8_t& row, const uint8_t& column, const Mode& mode = Mode::Off, const uint8_t& paletteIndex = 0);

      static const std::vector<Color>& getPalette();

   private:
      void switchToProgramMode();
      void switchToLiveMode();

      void noteOn(const ::Midi::Channel& channel, const uint8_t& midiNote, const ::Midi::Velocity& velocity) override;
      void controllerChange(const ::Midi::Channel& channel, const ::Midi::ControllerMessage& controllerMessage, const uint8_t& value) override;

      uint8_t getClosestPaletteIndex(const Color& color) const;

   private:
      static const std::vector<Color> paletteList; // color vs palette index
      Pad::Map padCache;
   };
} // namespace Svin

#endif // NOT SvinLaunchpadClientH
