#include "SvinMasterClock.h"

Svin::MasterClock* Svin::MasterClock::me = nullptr;

const Svin::MasterClock* Svin::MasterClock::the()
{
   return me;
}

const Svin::MasterClock::Signal& Svin::MasterClock::getSignal() const
{
   return signal;
}

const Tempo& Svin::MasterClock::getTempo() const
{
   return tempo;
}

const TimeCode::Duration& Svin::MasterClock::getDuration() const
{
   return duration;
}

Svin::MasterClock::MasterClock()
   : signal(Signal::None)
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
   signal = Signal::Reset;
   duration = 0;
   tempo.clockReset();
}

void Svin::MasterClock::tick()
{
   signal = Signal::Tick;
   duration++;
   tempo.clockTick();
}

void Svin::MasterClock::advance(const float& sampleRate)
{
   signal = Signal::None;
   tempo.advance(sampleRate);
}
