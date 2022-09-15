#include "ScionExciter.h"
#include "ScionExciterPanel.h"

#include <Sound/StandardTable.h>

#include <SvinOrigin.h>

// dummy

// section

ScionExciter::Section::Section(ScionExciter* parent, const uint16_t sliderValueParam, const uint16_t& sliderColorParam, const uint16_t& modInputParam, const uint16_t& modAttenuatorParam, const uint16_t& modLFOParam)
   : parent(parent)
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

void ScionExciter::Section::process(const BioFeedbackDummy::FunctionId& id, const float& scale)
{
   lfo.setFrequency(lfoPitchKnob.getValue());

   const float mod = modInput.isConnected() ? 0.1 * modInput.getVoltage() : lfo.createSound();
   float value = slider.getValue() + (scale * mod * modAttenuator.getValue());
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

   sections[BioFeedbackDummy::BaseFrequency] = new Section(this, Panel::Base1_Pitch_Value, Panel::RGB_Base1_Pitch_Value, Panel::Base1_Pitch_Modulate, Panel::Base1_Pitch_Attenuate, Panel::Base1_Pitch_LFO);
   sections[BioFeedbackDummy::BaseFrequency]->setup(45.0, 55.0, 50.0);
   sections[BioFeedbackDummy::BaseAmplitude] = new Section(this, Panel::Base1_Amplitude2_Value, Panel::RGB_Base1_Amplitude2_Value, Panel::Base1_Amplitude2_Modulate, Panel::Base1_Amplitude2_Attenuate, Panel::Base1_Amplitude2_LFO);
   sections[BioFeedbackDummy::BaseAmplitude]->setup(0.0, 1.0, 0.5);

   // noise
   sections[BioFeedbackDummy::NoiseSmooth] = new Section(this, Panel::Noise_Smooth1_Value, Panel::RGB_Noise_Smooth1_Value, Panel::Noise_Smooth1_Modulate, Panel::Noise_Smooth1_Attenuate, Panel::Noise_Smooth1_LFO);
   sections[BioFeedbackDummy::NoiseSmooth]->setup(0.0, 1.0, 0.5);
   sections[BioFeedbackDummy::NoiseAmplitude] = new Section(this, Panel::Noise_Amplitude1_Value, Panel::RGB_Noise_Amplitude1_Value, Panel::Noise_Amplitude1_Modulate, Panel::Noise_Amplitude1_Attenuate, Panel::Noise_Amplitude1_LFO);
   sections[BioFeedbackDummy::NoiseAmplitude]->setup(0.0, 1.0, 0.5);

   // master
   sections[BioFeedbackDummy::MasterSmooth] = new Section(this, Panel::Master_Smooth_Value, Panel::RGB_Master_Smooth_Value, Panel::Master_Smooth_Modulate, Panel::Master_Amplitude_Attenuate, Panel::Master_Amplitude_LFO);
   sections[BioFeedbackDummy::MasterSmooth]->setup(0.0, 1.0, 0.5);
   sections[BioFeedbackDummy::MasterAmplitude] = new Section(this, Panel::Master_Amplitude_Value, Panel::RGB_Noise_Amplitude1_Value, Panel::Master_Amplitude_Modulate, Panel::Master_Smooth_Attenuate, Panel::Master_Amplitude_LFO);
   sections[BioFeedbackDummy::MasterAmplitude]->setup(0.0, 1.0, 0.5);
}

void ScionExciter::process(const ProcessArgs& args)
{
   for (const BioFeedbackDummy::FunctionId& id : {BioFeedbackDummy::BaseFrequency, BioFeedbackDummy::BaseAmplitude, BioFeedbackDummy::NoiseSmooth, BioFeedbackDummy::NoiseAmplitude, BioFeedbackDummy::MasterSmooth, BioFeedbackDummy::MasterAmplitude})
   {
      sections[id]->process(id);
   }

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
