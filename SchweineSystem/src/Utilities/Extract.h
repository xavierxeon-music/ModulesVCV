#ifndef ExtractH
#define ExtractH

#include <rack.hpp>
using namespace rack;

#include <Abstract/AbstractEffect.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <Sound/Spectrum.h>

#include <SvinInput.h>
#include <SvinOutput.h>

class Extract : public Svin::Module, public Abstract::ThreadeBufferEffect
{
public:
   struct Panel;

public:
   Extract();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();
   Data proccessBuffer(const Data& input) override;
   void onSampleRateChange(const SampleRateChangeEvent& e) override;

private:
   Svin::Input audioInput;
   Svin::Output audioPassthrough;
   Svin::Output pitchOutput;

   Spectrum spectrum;
   float voltages[16];
   float sampleRate;
   uint8_t numberOfVoices;
};

// widget

class ExtractWidget : public Svin::ModuleWidget
{
public:
   ExtractWidget(Extract* module);

private:
   inline void setup();
};

#ifndef ExtractHPP
#include "Extract.hpp"
#endif // NOT ExtractHPP

#endif // NOT ExtractH
