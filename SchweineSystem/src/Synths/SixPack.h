#ifndef SixPackH
#define SixPackH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <Sound/StandardTable.h>
#include <Sound/WaveTableOscilator.h>

#include <SvinKnob.h>
#include <SvinLED.h>
#include <SvinSlider.h>
#include <SvinInput.h>
#include <SvinOutput.h>

class SixPack : public Svin::Module
{
public:
   struct Panel;

public:
   SixPack();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();

private:
   Svin::Knob::List panValueList;
   Svin::Knob::List panAttenuateList;
   Svin::Knob::List panPitchList;
   Svin::Input panModInput;
   WaveTable::Oscilator panModLFO[6];

   Svin::Knob::List phaseValueList;
   Svin::Knob::List phaseAttenuateList;
   Svin::Knob::List phasePitchList;
   Svin::Input phaseModInput;
   WaveTable::Oscilator phaseModLFO[6];

   Svin::Knob::List detuneValueList;
   Svin::Knob::List detuneAttenuateList;
   Svin::Knob::List detunePitchList;
   Svin::Input detuneModInput;
   WaveTable::Oscilator detuneModLFO[6];

   Svin::Input syncInput;
   Svin::Input fmInput;

   Svin::Input pitchInput;
   Svin::Knob pitchKnob;
   WaveTable::Oscilator oscilator[6];
   Svin::Output stereoOutput;

   WaveTable::Oscilator coreOscilator;
   Svin::Output coreOutput;

   Standard::Table sineTable;
   Standard::Table sawTable;
   Standard::Table squareTable;
};

// widget

class SixPackWidget : public Svin::ModuleWidget
{
public:
   SixPackWidget(SixPack* module);

private:
   inline void setup();
};

#ifndef SixPackHPP
#include "SixPack.hpp"
#endif // NOT SixPackHPP

#endif // NOT SixPackH
