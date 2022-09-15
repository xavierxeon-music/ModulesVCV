#ifndef ScionExciterH
#define ScionExciterH

#include <rack.hpp>
using namespace rack;

#include <map>

#include <Effect/StateVariableFilter.h>
#include <Sound/StandardTable.h>
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
   class Section
   {
   public:
      enum ID
      {
         BasePitch,
         BaseAmplitude,
         NoiseSmooth,
         NoiseAmplitude,
         MasterSmooth,
         MasterAmplitude
      };
      using Map = std::map<ID, Section*>;

   public:
      Section(ScionExciter* parent, const uint16_t sliderValueParam, const uint16_t& sliderColorParam, const uint16_t& modInputParam, const uint16_t& modAttenuatorParam, const uint16_t& modLFOParam);

   public:
      void setup(const float& minValue, const float& maxValue, const float& defaultValue);

   public:
      ScionExciter* parent;
      Svin::Slider slider;
      Svin::Input modInput;
      Svin::Knob modAttenuator;
      Svin::Knob lfoPitchKnob;
      WaveTable::Oscilator modLFO;
   };

private:
   void setup();

private:
   Section::Map sections;
   Standard::Table sineTable;
   // base
   Standard::Table sawTable;
   WaveTable::Oscilator baseOscilator;

   Svin::Slider basePitchSlider;
   Svin::Input basePitchModInput;
   Svin::Knob basePitchModAttenuator;
   Svin::Slider baseAmplitudeSlider;
   Svin::Input baseAmplitudehModInput;
   Svin::Knob baseAmplitudeModAttenuator;
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
