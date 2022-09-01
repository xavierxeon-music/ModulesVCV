#include "SvinMasterClock.h"

// client

Svin::MasterClock::Client::Client()
   : mutex()
   , tickCount(0)
   , reset(false)
{
   MasterClock::clientList.push_back(this);
}

Svin::MasterClock::Client::~Client()
{
   MasterClock::clientList.remove(this);
}

bool Svin::MasterClock::Client::hasTick()
{
   std::lock_guard<std::mutex> guard(mutex);
   if (0 == tickCount)
      return false;

   tickCount--;
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
   if (!MasterClock::me)
      return Tempo();

   return MasterClock::me->tempo;
}

TimeCode::Duration Svin::MasterClock::Client::getDuration() const
{
   std::lock_guard<std::mutex> guard(mutex);
   if (!MasterClock::me)
      return 0;

   return MasterClock::me->duration;
}

// master clock

Svin::MasterClock* Svin::MasterClock::me = nullptr;
Svin::MasterClock::Client::List Svin::MasterClock::clientList = Client::List();

Svin::MasterClock::MasterClock()
   : mutex()
   , tempo()
   , duration(0)
{
   me = this;
}

Svin::MasterClock::~MasterClock()
{
   me = nullptr;
}

bool Svin::MasterClock::iAmMasterClock() const
{
   return (this == me);
}

void Svin::MasterClock::reset()
{
   duration = 0;
   tempo.clockReset();

   for (Client* client : clientList)
   {
      std::lock_guard<std::mutex> guard(client->mutex);
      client->reset = true;
   }
}

void Svin::MasterClock::tick()
{
   duration++;
   tempo.clockTick();

   for (Client* client : clientList)
   {
      std::lock_guard<std::mutex> guard(client->mutex);
      client->tickCount++;
   }
}

void Svin::MasterClock::advance(const float& sampleRate)
{
   tempo.advance(sampleRate);
}

Tempo Svin::MasterClock::getTempo() const
{
   return tempo;
}

const TimeCode::Duration& Svin::MasterClock::getDuration() const
{
   return duration;
}
