#include "SvinMasterClock.h"

// client

Svin::MasterClock::Client::Client()
   : mutex()
   , tickCount(0)
   , midiClock(0)
   , reset(false)
{
   MasterClock::clientList.push_back(this);
}

Svin::MasterClock::Client::~Client()
{
   MasterClock::clientList.remove(this);
}

bool Svin::MasterClock::Client::hasTick(bool* isFirstTick)
{
   std::lock_guard<std::mutex> guard(mutex);
   if (0 == tickCount)
      return false;

   if (isFirstTick)
      *isFirstTick = firstTick;
   firstTick = false;

   tickCount--;
   return true;
}

bool Svin::MasterClock::Client::hasMidiClock()
{
   std::lock_guard<std::mutex> guard(mutex);
   if (0 == midiClock)
      return false;

   midiClock--;
   return true;
}

bool Svin::MasterClock::Client::hasReset()
{
   std::lock_guard<std::mutex> guard(mutex);
   if (!reset)
      return false;

   reset = false;
   return true;
}

Tempo Svin::MasterClock::Client::getTempo() const
{
   std::lock_guard<std::mutex> guard(mutex);
   if (!MasterClock::masterInstance)
      return Tempo();

   const Tempo tempo = MasterClock::masterInstance->tempo;
   //debug() << __FUNCTION__ << tempo.getRunState();
   return tempo;
}

TimeCode::Duration Svin::MasterClock::Client::getDuration() const
{
   std::lock_guard<std::mutex> guard(mutex);
   if (!MasterClock::masterInstance)
      return 0;

   return MasterClock::masterInstance->duration;
}

// master clock
std::list<Svin::MasterClock*> Svin::MasterClock::instanceList = std::list<Svin::MasterClock*>();
Svin::MasterClock* Svin::MasterClock::masterInstance = nullptr;
Svin::MasterClock::Client::List Svin::MasterClock::clientList = Client::List();

Svin::MasterClock::MasterClock()
   : Svin::Midi::Output(true)
   , mutex()
   , tempo()
   , duration(0)
   , oldRunState(Tempo::Off)
{
   if (instanceList.empty())
   {
      masterInstance = this;

      setTargetDeviceName("ClockVCV");
      open();
   }

   instanceList.push_back(this);
}

Svin::MasterClock::~MasterClock()
{
   instanceList.remove(this);

   if (instanceList.empty())
   {
      masterInstance = nullptr;
      close();
   }
   else if (iAmMasterClock())
   {
      masterInstance = instanceList.front();
   }
}

bool Svin::MasterClock::iAmMasterClock() const
{
   return (this == masterInstance);
}

void Svin::MasterClock::tick()
{
   duration++;
   tempo.clockTick();

   if (!iAmMasterClock())
      return;

   for (Client* client : clientList)
   {
      std::lock_guard<std::mutex> guard(client->mutex);
      client->tickCount++;

      if (Tempo::FirstTick == tempo.getRunState())
         client->firstTick = true;
   }
}

void Svin::MasterClock::midiClock()
{
   if (!iAmMasterClock())
      return;

   std::vector<unsigned char> clockMessage(1);
   clockMessage[0] = ::Midi::Event::Clock;
   sendMessage(clockMessage);

   for (Client* client : clientList)
   {
      std::lock_guard<std::mutex> guard(client->mutex);
      client->midiClock++;
   }
}

void Svin::MasterClock::reset()
{
   duration = 0;
   tempo.clockReset();

   if (!iAmMasterClock())
      return;

   oldRunState = Tempo::Off;

   std::vector<unsigned char> songPosMessage(3);
   songPosMessage[0] = ::Midi::Event::SongPositionPointer;
   songPosMessage[1] = 0;
   songPosMessage[2] = 0;
   sendMessage(songPosMessage);

   for (Client* client : clientList)
   {
      std::lock_guard<std::mutex> guard(client->mutex);
      client->firstTick = false;
      client->reset = true;
   }
}

void Svin::MasterClock::advance(const float& sampleRate)
{
   tempo.advance(sampleRate, 3.0);

   if (!iAmMasterClock())
      return;

   const Tempo::RunState runState = tempo.getRunState();
   if (runState == oldRunState)
      return;

   std::vector<unsigned char> clockMessage(1);
   if (Tempo::Off == runState)
      clockMessage[0] = ::Midi::Event::Stop;
   else if (Tempo::FirstTick == runState || Tempo::Running == runState)
      clockMessage[0] = ::Midi::Event::Continue;

   sendMessage(clockMessage);
   oldRunState = runState;
}

Tempo Svin::MasterClock::getTempo() const
{
   return tempo;
}

const TimeCode::Duration& Svin::MasterClock::getDuration() const
{
   return duration;
}
