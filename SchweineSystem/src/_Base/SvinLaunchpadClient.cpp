#include "SvinLaunchpadClient.h"

// from http://launchpaddr.com/mk2palette/
const std::vector<std::string> Svin::LaunchpadClient::hexColorsMk2 = {"000000", "1c1c1c", "7c7c7c", "fcfcfc", "ff4e48", "fe0a00", "5a0000", "180002",
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

Svin::LaunchpadClient::LaunchpadClient()
   : Midi::Input(false)
   , Midi::Output(false)
   , MasterClock::Client()
   , triggerCache()
   , oldRunState(Tempo::Off)
{
}

Svin::LaunchpadClient::~LaunchpadClient()
{
   // TODO if connected
   switchToLiveMode();
}

Svin::LaunchpadClient::Pad::List Svin::LaunchpadClient::update()
{
   Pad::List triggerLsit = triggerCache;
   triggerCache.clear();

   const Tempo::RunState runState = getTempo().getRunState();
   if (runState != oldRunState)
   {
      std::vector<unsigned char> clockMessage(1);
      if (Tempo::Off == runState)
         clockMessage[0] = ::Midi::Event::Stop;
      else if (Tempo::FirstTick == runState || Tempo::Running == runState)
         clockMessage[0] = ::Midi::Event::Continue;

      sendMessage(clockMessage);
      oldRunState = runState;
   }

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

   return triggerLsit;
}

bool Svin::LaunchpadClient::connect(const uint8_t& deviceId)
{
   // TODO check if connected
   switchToProgramMode();

   return true;
}

void Svin::LaunchpadClient::setPad(const uint8_t& row, const uint8_t& column, const Mode& mode, const Color& color)
{
   const uint8_t channel = static_cast<uint8_t>(mode);
   const uint8_t midiNote = (10 * (row + 1)) + (column + 1);
   const uint8_t velocity = 0;

   std::vector<unsigned char> onMessage(3);
   onMessage[0] = (::Midi::Event::NoteOn | channel);
   onMessage[1] = midiNote;
   onMessage[2] = velocity;
   sendMessage(onMessage);
}

void Svin::LaunchpadClient::switchToProgramMode()
{
   //F0h 00h 20h 29h 02h 0Dh 0Eh 1 F7h

   std::vector<uint8_t> sysExMessage(9);

   sysExMessage[0] = static_cast<uint8_t>(::Midi::Event::System); // Exclusive Status
   sysExMessage[1] = 0x00;
   sysExMessage[2] = 0x20;
   sysExMessage[3] = 0x29;
   sysExMessage[4] = 0x02;
   sysExMessage[5] = 0x0D;
   sysExMessage[6] = 0x0E;

   sysExMessage[7] = 1;

   sysExMessage[8] = static_cast<uint8_t>(::Midi::Event::SysExEnd); // End of Exclusive
   sendMessage(sysExMessage);
}

void Svin::LaunchpadClient::switchToLiveMode()
{
   //F0h 00h 20h 29h 02h 0Dh 0Eh 0 F7h

   std::vector<uint8_t> sysExMessage(9);

   sysExMessage[0] = static_cast<uint8_t>(::Midi::Event::System); // Exclusive Status
   sysExMessage[1] = 0x00;
   sysExMessage[2] = 0x20;
   sysExMessage[3] = 0x29;
   sysExMessage[4] = 0x02;
   sysExMessage[5] = 0x0D;
   sysExMessage[6] = 0x0E;

   sysExMessage[7] = 0;

   sysExMessage[8] = static_cast<uint8_t>(::Midi::Event::SysExEnd); // End of Exclusive
   sendMessage(sysExMessage);
}

void Svin::LaunchpadClient::noteOn(const ::Midi::Channel& channel, const Note& note, const ::Midi::Velocity& velocity)
{
}

void Svin::LaunchpadClient::controllerChange(const ::Midi::Channel& channel, const ::Midi::ControllerMessage& controllerMessage, const uint8_t& value)
{
}
