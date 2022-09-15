#ifndef ScionExciterH
#define ScionExciterH

#include <rack.hpp>
using namespace rack;

#include <Effect/StateVariableFilter.h>
#include <Sound/WaveTable.h>
#include <Tools/FastRandom.h>

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinKnob.h>
#include <SvinSlider.h>
#include <SvinInput.h>
#include <SvinOutput.h>

class ScionExciter : public Svin::Module
{
public:
   struct Panel;

public:
   ScionExciter();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();

private:
   // base
   Svin::Slider basePitchSlider;
   Svin::Input basePitchModInput;
   Svin::Knob basePitchModAttenuator;
   Svin::Slider baseAmplitudeSlider;
   Svin::Input baseAmplitudehModInput;
   Svin::Knob baseAmplitudeModAttenuator;
   WaveTable::Oscilator baseOscilator;
   // noise
   Svin::Slider noiseSmoothSlider;
   Svin::Input noiseSmoothModInput;
   Svin::Knob noiseSmoothModAttenuator;
   Svin::Slider noiseAmplitudeSlider;
   Svin::Input noiseAmplitudeModInput;
   Svin::Knob noiseAmplitudeModAttenuator;
   FastRandom noiseGenerator;
   StateVariableFilter nosieFilter;
   // master
   Svin::Slider masterSmoothSlider;
   Svin::Input masterSmoothModInput;
   Svin::Knob masterSmoothModAttenuator;
   Svin::Slider masterAmplitudeSlider;
   Svin::Input masterAmplitudeModInput;
   Svin::Knob masterAmplitudeModAttenuator;
   StateVariableFilter exciterFilter;
   Svin::Output exciterOutput;
   Svin::Output baseOutput;
};

// widget

class ScionExciterWidget : public Svin::ModuleWidget
{
public:
   ScionExciterWidget(ScionExciter* module);

private:
   void setup();
};

#endif // NOT ScionExciterH
