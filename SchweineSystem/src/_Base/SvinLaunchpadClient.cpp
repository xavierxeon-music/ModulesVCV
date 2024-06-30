#include "SvinLaunchpadClient.h"

#include <algorithm>

const std::vector<Color> Svin::LaunchpadClient::paletteList = []
{
   // from http://launchpaddr.com/mk2palette/
   const std::vector<std::string> hexColorsMk2 = {"000000", "1c1c1c", "7c7c7c", "fcfcfc", "ff4e48", "fe0a00", "5a0000", "180002",
                                                  "ffbc63", "ff5700", "5a1d00", "241802", "fdfd21", "fdfd00", "585800", "181800",
                                                  "81fd2b", "40fd01", "165800", "132801", "35fd2b", "00fe00", "005801", "001800",
                                                  "35fc47", "00fe00", "005801", "001800", "32fd7f", "00fd3a", "015814", "001c0e",
                                                  "2ffcb1", "00fb91", "015732", "011810", "39beff", "00a7ff", "014051", "001018",
                                                  "4186ff", "0050ff", "011a5a", "010619", "4747ff", "0000fe", "00005a", "000018",
                                                  "8347ff", "5000ff", "160067", "0a0032", "ff48fe", "ff00fe", "5a005a", "180018",
                                                  "fb4e83", "ff0753", "5a021b", "210110", "ff1901", "9a3500", "7a5101", "3e6500",
                                                  "013800", "005432", "00537f", "0000fe", "01444d", "1a00d1", "7c7c7c", "202020",
                                                  "ff0a00", "bafd00", "acec00", "56fd00", "008800", "01fc7b", "00a7ff", "021aff",
                                                  "3500ff", "7800ff", "b4177e", "412000", "ff4a01", "82e100", "66fd00", "00fe00",
                                                  "00fe00", "45fd61", "01fbcb", "5086ff", "274dc8", "847aed", "d30cff", "ff065a",
                                                  "ff7d01", "b8b100", "8afd00", "815d00", "3a2802", "0d4c05", "005037", "131429",
                                                  "101f5a", "6a3c18", "ac0401", "e15136", "dc6900", "fee100", "99e101", "60b500",
                                                  "1b1c31", "dcfd54", "76fbb9", "9698ff", "8b62ff", "404040", "747474", "defcfc",
                                                  "a20401", "340100", "00d201", "004101", "b8b100", "3c3000", "b45d00", "4c1300"};

   std::vector<Color> paletteList;
   for (uint8_t index = 0; index < hexColorsMk2.size(); index++)
   {
      const Color color(hexColorsMk2.at(index));
      paletteList.push_back(color);

      //mtDebug() << index << hexColorsMk2.at(index) << color.red() << color.green() << color.blue();
   }
   return paletteList;
}();

Svin::LaunchpadClient::LaunchpadClient()
   : MidiInput()
   , MidiOutput()
   , MasterClock::Client()
   , padCache()
   , colorMap()
{
}

Svin::LaunchpadClient::~LaunchpadClient()
{
   disconnect();
}

void Svin::LaunchpadClient::sendClock()
{
   if (hasReset())
   {
      std::vector<unsigned char> songPosMessage(3);
      songPosMessage[0] = ::Midi::Event::SongPositionPointer;
      songPosMessage[1] = 0;
      songPosMessage[2] = 0;
      sendMessage(songPosMessage);
   }
   else
   {
      while (hasMidiClock())
      {
         std::vector<unsigned char> clockMessage(1);
         clockMessage[0] = ::Midi::Event::Clock;
         sendMessage(clockMessage);
      }
   }
}

Svin::LaunchpadClient::Pad::List Svin::LaunchpadClient::triggeredPads()
{
   auto copyValue = [](const Pad::Map::value_type& pair)
   {
      return pair.second;
   };

   Pad::List padList;
   std::transform(padCache.begin(), padCache.end(), std::back_inserter(padList), copyValue);
   padCache.clear();

   return padList;
}

void Svin::LaunchpadClient::showColorTest(bool firstPage)
{
   uint8_t paletteIndex = firstPage ? 0 : 63;
   for (uint8_t row = 0; row < 8; row++)
   {
      for (uint8_t col = 0; col < 8; col++)
      {
         setPad(7 - row, col, Svin::LaunchpadClient::Mode::Steady, paletteList.at(paletteIndex));
         paletteIndex++;
      }
   }
}

void Svin::LaunchpadClient::disconnect()
{
   colorMap.clear();

   //sendPowerSafe(true);
   //switchToProgramMode(false);

   if (MidiOutput::connected())
      MidiOutput::close();

   if (MidiInput::connected())
      MidiInput::close();
}

void Svin::LaunchpadClient::connect(const uint8_t& deviceId)
{
   disconnect();

   static bool first = true;

   std::string deviceName = "LPMiniMK3 MIDI " + std::to_string(deviceId);
   if (0 == deviceId)
      deviceName = "Launchpad Mini MK3 LPMiniMK3 MIDI Out";

   MidiInput::setTargetDeviceName(deviceName);
   MidiInput::open(first);

   if (0 == deviceId)
      deviceName = "Launchpad Mini MK3 LPMiniMK3 MIDI In";

   MidiOutput::setTargetDeviceName(deviceName);
   MidiOutput::open(first);

   first = false;

   sendPowerSafe(false);
   switchToProgramMode(true);
}

bool Svin::LaunchpadClient::isConnected()
{
   return (MidiInput::connected() && MidiOutput::connected());
}

void Svin::LaunchpadClient::setAll(const uint8_t& paletteIndex, bool gridOnly)
{
   // F0h 00h 20h 29h 02h 0Dh 03h <colourspec>  F7h

   const uint8_t numberOfPads = gridOnly ? 8 : 9;
   MidiMessage payload(3 * numberOfPads * numberOfPads);

   uint8_t messageIndex = 0;
   for (uint8_t row = 0; row < numberOfPads; row++)
   {
      for (uint8_t column = 0; column < numberOfPads; column++)
      {
         const uint8_t midiNote = (10 * (row + 1)) + (column + 1);
         payload[messageIndex] = 0; // static light
         messageIndex++;
         payload[messageIndex] = midiNote;
         messageIndex++;
         payload[messageIndex] = paletteIndex;
         messageIndex++;
      }
   }

   sendSysEx(0x03, payload);

   colorMap.clear();
}

void Svin::LaunchpadClient::setPad(const uint8_t& row, const uint8_t& column, const Mode& mode, const Color& color)
{
   const uint8_t paletteIndex = getClosestPaletteIndex(color);
   setPad(row, column, mode, paletteIndex);
}

void Svin::LaunchpadClient::setPad(const uint8_t& row, const uint8_t& column, const Mode& mode, const uint8_t& paletteIndex)
{
   const uint8_t channel = (Mode::Off == mode) ? 0 : static_cast<uint8_t>(mode);
   const uint8_t midiNote = (10 * (row + 1)) + (column + 1);
   const uint8_t velocity = (Mode::Off == mode) ? 0 : paletteIndex;

   const uint16_t test = (channel * 256) + velocity;
   auto sendColor = [&]()
   {
      MidiMessage colorMessage(3);
      colorMessage[0] = (::Midi::Event::NoteOn | channel);
      colorMessage[1] = midiNote;
      colorMessage[2] = velocity;

      sendMessage(colorMessage);
      colorMap[midiNote] = test;
   };

   if (colorMap.find(midiNote) == colorMap.end())
      sendColor();

   if (colorMap.at(midiNote) != test)
      sendColor();
}

void Svin::LaunchpadClient::sendPowerSafe(bool enabled)
{
   // F0h 00h 20h 29h 02h 0Dh 09h 0 F7h // on
   // F0h 00h 20h 29h 02h 0Dh 09h 1 F7h // off
   sendSysEx(0x09, enabled ? 0x00 : 0x01);
}

const std::vector<Color>& Svin::LaunchpadClient::getPalette()
{
   return paletteList;
}

void Svin::LaunchpadClient::switchToProgramMode(bool on)
{
   //F0h 00h 20h 29h 02h 0Dh 0Eh 1 F7h // program mode
   //F0h 00h 20h 29h 02h 0Dh 0Eh 0 F7h // =live mode
   sendSysEx(0x0E, on ? 0x01 : 0x00);
}

void Svin::LaunchpadClient::noteOn(const ::Midi::Channel& channel, const uint8_t& midiNote, const ::Midi::Velocity& velocity)
{
   // sent by 8x8 central grid
   if (1 != channel)
      return;

   buttonActive(midiNote, velocity != 0);
}

void Svin::LaunchpadClient::controllerChange(const ::Midi::Channel& channel, const ::Midi::ControllerMessage& controllerMessage, const uint8_t& value)
{
   // sent by outer controll buttons
   if (1 != channel)
      return;

   buttonActive(controllerMessage, value != 0);
}

void Svin::LaunchpadClient::buttonActive(const uint8_t& midiNote, bool down)
{
   if (padCache.find(midiNote) == padCache.end())
   {
      const uint8_t column = (midiNote % 10) - 1;
      const uint8_t row = ((midiNote - (midiNote % 10)) / 10) - 1;
      const Button button = down ? Button::On : Button::Off;
      padCache[midiNote] = {row, column, button};
   }
   else
   {
      Pad& pad = padCache[midiNote];
      if (down)
         pad.button = Button::On;
      else if (Button::On == pad.button)
         pad.button = Button::Triggerd;
   }
}

void Svin::LaunchpadClient::sendSysEx(const uint8_t mode, const uint8_t& payload)
{
   MidiMessage msg(1);
   msg[0] = payload;

   sendSysEx(mode, msg);
}

void Svin::LaunchpadClient::sendSysEx(const uint8_t mode, const MidiMessage& payload)
{
   std::vector<uint8_t> sysExMessage(8 + payload.size());

   sysExMessage[0] = static_cast<uint8_t>(::Midi::Event::System); // Exclusive Status
   sysExMessage[1] = 0x00;
   sysExMessage[2] = 0x20;
   sysExMessage[3] = 0x29;
   sysExMessage[4] = 0x02;
   sysExMessage[5] = 0x0D;

   sysExMessage[6] = mode;

   uint8_t messageIndex = 7;
   for (const uint8_t& byte : payload)
   {
      sysExMessage[messageIndex] = byte;
      messageIndex++;
   }

   sysExMessage[messageIndex] = static_cast<uint8_t>(::Midi::Event::SysExEnd); // End of Exclusive
   sendMessage(sysExMessage);
}

uint8_t Svin::LaunchpadClient::getClosestPaletteIndex(const Color& color) const
{
   using CacheMap = std::map<Color, uint8_t>;
   using DistanceMap = std::map<float, uint8_t>;

   static CacheMap cacheMap;
   if (cacheMap.find(color) != cacheMap.end())
      return cacheMap.at(color);

   DistanceMap distanceMap;
   std::vector<float> distanceList;
   for (uint8_t index = 0; index < paletteList.size(); index++)
   {
      const Color testColor = paletteList.at(index);
      const float distance = testColor.distance(color);
      distanceMap[distance] = index;
      distanceList.push_back(distance);
   }

   std::sort(distanceList.begin(), distanceList.end(), std::less<float>());
   const float minDistance = distanceList.at(0);

   uint8_t index = distanceMap.at(minDistance);
   cacheMap[color] = index;

   return index;
}
