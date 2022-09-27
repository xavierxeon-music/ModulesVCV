#ifndef BoilerplateH
#define BoilerplateH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <Sound/StandardTable.h>
#include <Sound/WaveTableOscilator.h>

#include <SvinButtonLED.h>
#include <SvinInput.h>
#include <SvinKnob.h>
#include <SvinOutput.h>
#include <SvinSlider.h>

class Boilerplate : public Svin::Module
{
public:
   struct Panel;

public:
   Boilerplate();

public:
   void process(const ProcessArgs& args) override;

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

   void onSampleRateChange(const SampleRateChangeEvent& event) override;

private:
   inline void setup();

private:
   Svin::Slider shapeSlider;

   Svin::Input syncInput;
   Svin::Input fmInput;
   Svin::Knob fmAttenutate;

   Svin::Input pitchInput;
   Svin::Knob pitchKnob;
   Svin::Input gateInput;

   Svin::Output output;
   Svin::ButtonLED polyButton;
   WaveTable::Oscilator oscilator[16];
   Standard::Table table;
};

// widget

class BoilerplateWidget : public Svin::ModuleWidget
{
public:
   BoilerplateWidget(Boilerplate* module);

private:
   inline void setup();
};

#ifndef BoilerplateHPP
#include "Boilerplate.hpp"
#endif // NOT BoilerplateHPP

#endif // NOT BoilerplateH
