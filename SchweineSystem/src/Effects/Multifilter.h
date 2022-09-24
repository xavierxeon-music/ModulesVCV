#ifndef MultifilterH
#define MultifilterH

#include <rack.hpp>
using namespace rack;

#include <Effect/StateVariableFilter.h>

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinKnob.h>
#include <SvinButtonLED.h>
#include <SvinSlider.h>
#include <SvinInput.h>
#include <SvinOutput.h>

class Multifilter : public Svin::Module
{
public:
   struct Panel;

public:
   Multifilter();

public:
   void process(const ProcessArgs& args) override;

private:
   class Voice
   {
   public:
      Voice();

   public:
      void init(const float& sampleRate, const FilterMode& filterMode);
      void update(const Svin::Input& pitchInput, const bool quantize, const float& offset, const float& resonance, const float& drive);
      float changeSound(const float& value);

   private:
      uint8_t noOfFilters;
      StateVariableFilter filters[16];
   };

private:
   inline void setup();
   void reinit();

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;
   void onSampleRateChange(const SampleRateChangeEvent& e) override;

private:
   Svin::Input resoModulateInput;
   Svin::Knob resoAttenuateKnob;
   Svin::Knob resoKnob;
   Svin::Input driveModulateInput;
   Svin::Knob driveAttenuateKnob;
   Svin::Knob driveKnob;
   Svin::Input offsetInput;
   Svin::Knob offsetKnob;
   Svin::Input pitchInput;
   Svin::ButtonLED quantizeButton;
   Svin::Input audioInput;
   Svin::Output audioOutput;
   Svin::Slider modeSlider;

   Voice voices[16];
   FilterMode filterMode;
};

// widget

class MultifilterWidget : public Svin::ModuleWidget
{
public:
   MultifilterWidget(Multifilter* module);

private:
   inline void setup();
};

#ifndef MultifilterHPP
#include "Multifilter.hpp"
#endif // NOT MultifilterHPP

#endif // NOT MultifilterH
