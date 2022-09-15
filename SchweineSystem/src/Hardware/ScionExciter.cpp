#include "ScionExciter.h"
#include "ScionExciterPanel.h"

#include <Sound/StandardTable.h>

#include <SvinOrigin.h>

// dummy

// section

ScionExciter::Section::Section(ScionExciter* parent, const BioFeedbackDummy::FunctionId& id, const uint16_t sliderValueParam, const uint16_t& sliderColorParam, const uint16_t& modInputParam, const uint16_t& modAttenuatorParam, const uint16_t& modLFOParam)
   : parent(parent)
   , id(id)
   , slider(parent, sliderValueParam, sliderColorParam)
   , modInput(parent, modInputParam)
   , modAttenuator(parent, modAttenuatorParam)
   , lfoPitchKnob(parent, modLFOParam)
   , lfo()
{
   updateSampleRate();
}

void ScionExciter::Section::setup(const float& minValue, const float& maxValue, const float& defaultValue)
{
   slider.setRange(minValue, maxValue, defaultValue);
   modAttenuator.setRange(0.0, 1.0);
   lfoPitchKnob.setRange(0.1, 2.0, 1.0);
}

void ScionExciter::Section::updateSampleRate()
{
   lfo.init(&parent->sineTable, parent->getSampleRate());
}

void ScionExciter::Section::process()
{
   lfo.setFrequency(lfoPitchKnob.getValue());

   const float mod = modInput.isConnected() ? 0.1 * modInput.getVoltage() : lfo.createSound();
   float value = slider.getValue() + mod * modAttenuator.getValue();
   parent->exciter.setState(id, value);
}

// main

ScionExciter::ScionExciter()
   : Svin::Module()
   , exciter(getSampleRate())
   , sections()
   // base
   , basePitchSlider(this, Panel::Base1_Pitch_Value, Panel::RGB_Base1_Pitch_Value)
   , basePitchModInput(this, Panel::Base1_Pitch_Modulate)
   , basePitchModAttenuator(this, Panel::Base1_Pitch_Attenuate)
   , baseAmplitudeSlider(this, Panel::Base1_Amplitude2_Value, Panel::RGB_Base1_Amplitude2_Value)
   , baseAmplitudehModInput(this, Panel::Base1_Amplitude2_Modulate)
   , baseAmplitudeModAttenuator(this, Panel::Base1_Amplitude2_Attenuate)
   // noise
   , noiseSmoothSlider(this, Panel::Noise_Smooth1_Value, Panel::RGB_Noise_Smooth1_Value)
   , noiseSmoothModInput(this, Panel::Noise_Smooth1_Modulate)
   , noiseSmoothModAttenuator(this, Panel::Noise_Smooth1_Attenuate)
   , noiseAmplitudeSlider(this, Panel::Noise_Amplitude1_Value, Panel::RGB_Noise_Amplitude1_Value)
   , noiseAmplitudeModInput(this, Panel::Noise_Amplitude1_Modulate)
   , noiseAmplitudeModAttenuator(this, Panel::Noise_Amplitude1_Attenuate)
   // master
   , masterSmoothSlider(this, Panel::Master_Smooth_Value, Panel::RGB_Master_Smooth_Value)
   , masterSmoothModInput(this, Panel::Master_Smooth_Modulate)
   , masterSmoothModAttenuator(this, Panel::Master_Amplitude_Attenuate)
   , masterAmplitudeSlider(this, Panel::Master_Amplitude_Value, Panel::RGB_Noise_Amplitude1_Value)
   , masterAmplitudeModInput(this, Panel::Master_Amplitude_Modulate)
   , masterAmplitudeModAttenuator(this, Panel::Master_Smooth_Attenuate)
   , exciterOutput(this, Panel::Master_Exciter_Out)
   , baseOutput(this, Panel::Master_Base_Out)
{
   setup();

   sections[BioFeedbackDummy::BaseFrequency] = new Section(this, BioFeedbackDummy::BaseFrequency, Panel::Base1_Pitch_Value, Panel::RGB_Base1_Pitch_Value, Panel::Base1_Pitch_Modulate, Panel::Base1_Pitch_Attenuate, Panel::Base1_Pitch_LFO);
   sections[BioFeedbackDummy::BaseFrequency]->setup(45.0, 55.0, 50.0);

   /*
   sections[Section::BaseAmplitude]->setup();
   sections[Section::NoiseSmooth]->setup();
   sections[Section::NoiseAmplitude]->setup();
   sections[Section::MasterSmooth]->setup();
   sections[Section::MasterAmplitude]->setup();
*/
}

void ScionExciter::process(const ProcessArgs& args)
{
   sections[BioFeedbackDummy::BaseFrequency]->process();

   float baseSoundVoltage = 0;
   const float voltage = exciter.compileSignalVoltage(&baseSoundVoltage);
   baseOutput.setVoltage(baseSoundVoltage);
   exciterOutput.setVoltage(voltage);
}

// widget

ScionExciterWidget::ScionExciterWidget(ScionExciter* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

Model* modelScionExciter = Svin::Origin::the()->addModule<ScionExciter, ScionExciterWidget>("ScionExciter");
