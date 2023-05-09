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
         Steady = 0,
         Flash = 1,
         Pulse = 2,
         Off = 4,
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
      void sendClock();
      Pad::List triggeredPads(); // return triggerd pads

      void showColorTest(bool firstPage);

      void disconnect();
      void connect(const uint8_t& deviceId);
      bool isConnected();

      void setAll(const uint8_t& paletteIndex = 0, bool gridOnly = true);
      void setPad(const uint8_t& row, const uint8_t& column, const Mode& mode, const Color& color);
      void setPad(const uint8_t& row, const uint8_t& column, const Mode& mode = Mode::Off, const uint8_t& paletteIndex = 0);
      void sendPowerSafe(bool enabled);

      static const std::vector<Color>& getPalette();

   private:
      using ColorMap = std::map<uint8_t, uint16_t>;
      using MidiMessage = std::vector<unsigned char>;

   private:
      void switchToProgramMode(bool on);

      void noteOn(const ::Midi::Channel& channel, const uint8_t& midiNote, const ::Midi::Velocity& velocity) override;
      void controllerChange(const ::Midi::Channel& channel, const ::Midi::ControllerMessage& controllerMessage, const uint8_t& value) override;
      void buttonActive(const uint8_t& midiNote, bool down);

      void sendSysEx(const uint8_t mode, const uint8_t& payload);
      void sendSysEx(const uint8_t mode, const MidiMessage& payload);

      uint8_t getClosestPaletteIndex(const Color& color) const;

   private:
      static const std::vector<Color> paletteList; // color vs palette index
      Pad::Map padCache;
      ColorMap colorMap;
   };
} // namespace Svin

#endif // NOT SvinLaunchpadClientH
