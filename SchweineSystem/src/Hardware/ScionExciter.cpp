#include "ScionExciter.h"
#include "ScionExciterPanel.h"

#include <Sound/StandardTable.h>

#include <SvinOrigin.h>

// section

ScionExciter::Section::Section(ScionExciter* parent, const uint16_t sliderValueParam, const uint16_t& sliderColorParam, const uint16_t& modInputParam, const uint16_t& modAttenuatorParam, const uint16_t& modLFOParam)
   : parent(parent)
   , slider(parent, sliderValueParam, sliderColorParam)
   , modInput(parent, modInputParam)
   , modAttenuator(parent, modAttenuatorParam)
   , lfoPitchKnob(parent, modLFOParam)
   , modLFO()
{
}

void ScionExciter::Section::setup(const float& minValue, const float& maxValue, const float& defaultValue)
{
   slider.setRange(minValue, maxValue, defaultValue);
   modAttenuator.setRange(0.0, 1.0);

   modLFO.init(&parent->sineTable, parent->getSampleRate());
}

// main

ScionExciter::ScionExciter()
   : Svin::Module()
   , sections()
   , sineTable()
   // base
   , sawTable()
   , baseOscilator()
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
   , noiseGenerator()
   , nosieFilter()
   // master
   , masterSmoothSlider(this, Panel::Master_Smooth_Value, Panel::RGB_Master_Smooth_Value)
   , masterSmoothModInput(this, Panel::Master_Smooth_Modulate)
   , masterSmoothModAttenuator(this, Panel::Master_Amplitude_Attenuate)
   , masterAmplitudeSlider(this, Panel::Master_Amplitude_Value, Panel::RGB_Noise_Amplitude1_Value)
   , masterAmplitudeModInput(this, Panel::Master_Amplitude_Modulate)
   , masterAmplitudeModAttenuator(this, Panel::Master_Smooth_Attenuate)
   , exciterFilter()
   , exciterOutput(this, Panel::Master_Exciter_Out)
   , baseOutput(this, Panel::Master_Base_Out)
{
   setup();
   sineTable.setWaveform(Standard::Waveform::Sine);
   sawTable.setWaveform(Standard::Waveform::Saw);

   sections[Section::BasePitch] = new Section(this, Panel::Base1_Pitch_Value, Panel::RGB_Base1_Pitch_Value, Panel::Base1_Pitch_Modulate, Panel::Base1_Pitch_Attenuate, Panel::Base1_Pitch_LFO);
   sections[Section::BasePitch]->setup(45.0, 55.0, 50.0);

   /*
   sections[Section::BaseAmplitude]->setup();
   sections[Section::NoiseSmooth]->setup();
   sections[Section::NoiseAmplitude]->setup();
   sections[Section::MasterSmooth]->setup();
   sections[Section::MasterAmplitude]->setup();
*/

   basePitchSlider.setRange(45.0, 55.0, 50.0);
   basePitchModAttenuator.setRange(0.0, 1.0);

   baseOscilator.init(&sawTable, getSampleRate());
   baseOscilator.setFrequency(50.0);
}

void ScionExciter::process(const ProcessArgs& args)
{
   float basePitch = basePitchSlider.getValue();
   if (basePitchModInput.isConnected())
      basePitch += 0.5 * basePitchModInput.getVoltage() * basePitchModAttenuator.getValue();

   baseOscilator.setFrequency(basePitch);
   const float base = baseOscilator.createSound();
   baseOutput.setVoltage(base * 10);

   const float voltage = base * 10.0;
   exciterOutput.setVoltage(voltage);
}

// widget

ScionExciterWidget::ScionExciterWidget(ScionExciter* module)
: Svin::ModuleWidget(module)
{
   setup();
}

Model* modelScionExciter = Svin::Origin::the()->addModule<ScionExciter, ScionExciterWidget>("ScionExciter");
