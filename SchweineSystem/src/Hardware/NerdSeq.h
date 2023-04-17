#ifndef NerdSeqH
#define NerdSeqH

#include <rack.hpp>
using namespace rack;

#include <SvinMidi.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButtonLED.h>

class NerdSeq : public Svin::Module, public Svin::Midi::Input
{
public:
   struct Panel;

public:
   NerdSeq();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();
   void connectToMidiDevice();
   void processMessage(const Bytes& message) override;

private:
   Svin::ButtonLED connectionButton;
   Svin::Midi::Bus busMessage;
};

// widget

class NerdSeqWidget : public Svin::ModuleWidget
{
public:
   NerdSeqWidget(NerdSeq* module);

private:
   inline void setup();
};

#ifndef NerdSeqHPP
#include "NerdSeq.hpp"
#endif // NOT NerdSeqHPP

#endif // NOT NerdSeqH
