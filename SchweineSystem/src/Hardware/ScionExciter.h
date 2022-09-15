#ifndef ScionExciterH
#define ScionExciterH

#include <rack.hpp>
using namespace rack;

#include <map>

#include <Blocks/BioFeedbackDummy.h>
#include <Sound/StandardTable.h>
#include <Sound/WaveTable.h>

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinInput.h>
#include <SvinKnob.h>
#include <SvinOutput.h>
#include <SvinSlider.h>

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
      using Map = std::map<BioFeedbackDummy::FunctionId, Section*>;

   public:
      Section(ScionExciter* parent, const uint16_t sliderValueParam, const uint16_t& sliderColorParam, const uint16_t& modInputParam, const uint16_t& modAttenuatorParam, const uint16_t& modLFOParam);

   public:
      void setup(const float& minValue, const float& maxValue, const float& defaultValue);
      void updateSampleRate();
      void process(const BioFeedbackDummy::FunctionId& id, const float& scale = 1.0);

   public:
      ScionExciter* parent;
      Svin::Slider slider;
      Svin::Input modInput;
      Svin::Knob modAttenuator;
      Svin::Knob lfoPitchKnob;
      WaveTable::Oscilator lfo;
   };

private:
   void setup();

private:
   BioFeedbackDummy exciter;
   Standard::Table sineTable;
   Section::Map sections;
   // base
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
   // master
   Svin::Slider masterSmoothSlider;
   Svin::Input masterSmoothModInput;
   Svin::Knob masterSmoothModAttenuator;
   Svin::Slider masterAmplitudeSlider;
   Svin::Input masterAmplitudeModInput;
   Svin::Knob masterAmplitudeModAttenuator;
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
