#include "ScionExciter.h"
#include "ScionExciterPanel.h"

#include <Sound/StandardTable.h>

#include <SvinOrigin.h>

ScionExciter::ScionExciter()
   : Svin::Module()
   // base
   , basePitchSlider(this, Panel::Base1_Pitch_Value, Panel::RGB_Base1_Pitch_Value)
   , basePitchModInput(this, Panel::Base1_Pitch_Modulate)
   , basePitchModAttenuator(this, Panel::Base1_Pitch_Attenuate)
   , baseAmplitudeSlider(this, Panel::Base1_Amplitude2_Value, Panel::RGB_Base1_Amplitude2_Value)
   , baseAmplitudehModInput(this, Panel::Base1_Amplitude2_Modulate)
   , baseAmplitudeModAttenuator(this, Panel::Base1_Amplitude2_Attenuate)
   , baseOscilator()
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

   basePitchSlider.setRange(45.0, 55.0, 50.0);
   basePitchModAttenuator.setRange(0.0, 1.0);

   Standard::Table* triangleTable = new Standard::Table();
   triangleTable->setWaveform(Standard::Waveform::Saw);
   baseOscilator.init(triangleTable, getSampleRate());
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
