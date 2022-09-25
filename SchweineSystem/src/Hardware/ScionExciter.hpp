#ifndef ScionExciterHPP
#define ScionExciterHPP

#include "ScionExciter.h"

#include <SvinOrigin.h>

struct ScionExciter::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      // knobs
      Master_Amplitude_Attenuate = 0,
      Master_Amplitude_LFO = 1,
      Master_Smooth_Attenuate = 2,
      Master_Smooth_LFO = 3,
      Noise_Amplitude1_Attenuate = 4,
      Noise_Amplitude1_LFO = 5,
      Noise_Smooth1_Attenuate = 6,
      Noise_Smooth1_LFO = 7,
      Base1_Amplitude2_Attenuate = 8,
      Base1_Amplitude2_LFO = 9,
      Base1_Pitch_Attenuate = 10,
      Base1_Pitch_LFO = 11,
      // sliders
      Master_Amplitude_Value = 12,
      Master_Smooth_Value = 13,
      Noise_Amplitude1_Value = 14,
      Noise_Smooth1_Value = 15,
      Base1_Amplitude2_Value = 16,
      Base1_Pitch_Value = 17,
      PARAMS_LEN = 18
   };

   enum DisplayId
   {
      // lcd
      // oled
      DISPLAYS_LEN = 0
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      Master_Amplitude_Modulate = 0,
      Master_Smooth_Modulate = 1,
      Noise_Amplitude1_Modulate = 2,
      Noise_Smooth1_Modulate = 3,
      Base1_Amplitude2_Modulate = 4,
      Base1_Pitch_Modulate = 5,
      INPUTS_LEN = 6
   };

   enum OutputId
   {
      Master_Exciter_Out = 0,
      Master_Base_Out = 1,
      OUTPUTS_LEN = 2
   };

   enum LightId
   {
      // leds
      // ledbuttons
      // sliders
      RGB_Master_Amplitude_Value = 0,
      RGB_Master_Smooth_Value = 3,
      RGB_Noise_Amplitude1_Value = 6,
      RGB_Noise_Smooth1_Value = 9,
      RGB_Base1_Amplitude2_Value = 12,
      RGB_Base1_Pitch_Value = 15,
      LIGHTS_LEN = 18
   };

};

void ScionExciter::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configSwitch(Panel::Master_Amplitude_Value, 0.0f, 1.0f, 0.0f, "Master_Amplitude_Value");
   configSwitch(Panel::Master_Smooth_Value, 0.0f, 1.0f, 0.0f, "Master_Smooth_Value");
   configSwitch(Panel::Noise_Amplitude1_Value, 0.0f, 1.0f, 0.0f, "Noise_Amplitude1_Value");
   configSwitch(Panel::Noise_Smooth1_Value, 0.0f, 1.0f, 0.0f, "Noise_Smooth1_Value");
   configSwitch(Panel::Base1_Amplitude2_Value, 0.0f, 1.0f, 0.0f, "Base1_Amplitude2_Value");
   configSwitch(Panel::Base1_Pitch_Value, 0.0f, 1.0f, 0.0f, "Base1_Pitch_Value");

   configParam(Panel::Master_Amplitude_Attenuate, -1.f, 1.f, 0.f, "Master_Amplitude_Attenuate");
   configParam(Panel::Master_Amplitude_LFO, -1.f, 1.f, 0.f, "Master_Amplitude_LFO");
   configParam(Panel::Master_Smooth_Attenuate, -1.f, 1.f, 0.f, "Master_Smooth_Attenuate");
   configParam(Panel::Master_Smooth_LFO, -1.f, 1.f, 0.f, "Master_Smooth_LFO");
   configParam(Panel::Noise_Amplitude1_Attenuate, -1.f, 1.f, 0.f, "Noise_Amplitude1_Attenuate");
   configParam(Panel::Noise_Amplitude1_LFO, -1.f, 1.f, 0.f, "Noise_Amplitude1_LFO");
   configParam(Panel::Noise_Smooth1_Attenuate, -1.f, 1.f, 0.f, "Noise_Smooth1_Attenuate");
   configParam(Panel::Noise_Smooth1_LFO, -1.f, 1.f, 0.f, "Noise_Smooth1_LFO");
   configParam(Panel::Base1_Amplitude2_Attenuate, -1.f, 1.f, 0.f, "Base1_Amplitude2_Attenuate");
   configParam(Panel::Base1_Amplitude2_LFO, -1.f, 1.f, 0.f, "Base1_Amplitude2_LFO");
   configParam(Panel::Base1_Pitch_Attenuate, -1.f, 1.f, 0.f, "Base1_Pitch_Attenuate");
   configParam(Panel::Base1_Pitch_LFO, -1.f, 1.f, 0.f, "Base1_Pitch_LFO");

   configInput(Panel::Master_Amplitude_Modulate, "Master_Amplitude_Modulate");
   configInput(Panel::Master_Smooth_Modulate, "Master_Smooth_Modulate");
   configInput(Panel::Noise_Amplitude1_Modulate, "Noise_Amplitude1_Modulate");
   configInput(Panel::Noise_Smooth1_Modulate, "Noise_Smooth1_Modulate");
   configInput(Panel::Base1_Amplitude2_Modulate, "Base1_Amplitude2_Modulate");
   configInput(Panel::Base1_Pitch_Modulate, "Base1_Pitch_Modulate");

   configOutput(Panel::Master_Exciter_Out, "Master_Exciter_Out");
   configOutput(Panel::Master_Base_Out, "Master_Base_Out");
}

void ScionExciterWidget::setup()
{
   makePanel("res/Hardware/ScionExciter.svg");

   makeSlider(this, Vec(164.00, 288.78), ScionExciter::Panel::Master_Amplitude_Value, ScionExciter::Panel::RGB_Master_Amplitude_Value);
   makeSlider(this, Vec(87.17, 288.78), ScionExciter::Panel::Master_Smooth_Value, ScionExciter::Panel::RGB_Master_Smooth_Value);
   makeSlider(this, Vec(164.00, 172.19), ScionExciter::Panel::Noise_Amplitude1_Value, ScionExciter::Panel::RGB_Noise_Amplitude1_Value);
   makeSlider(this, Vec(87.17, 172.19), ScionExciter::Panel::Noise_Smooth1_Value, ScionExciter::Panel::RGB_Noise_Smooth1_Value);
   makeSlider(this, Vec(164.00, 80.17), ScionExciter::Panel::Base1_Amplitude2_Value, ScionExciter::Panel::RGB_Base1_Amplitude2_Value);
   makeSlider(this, Vec(87.17, 80.17), ScionExciter::Panel::Base1_Pitch_Value, ScionExciter::Panel::RGB_Base1_Pitch_Value);

   makeKnob(this, Vec(136.00, 277.76), ScionExciter::Panel::Master_Amplitude_Attenuate, 3);
   makeKnob(this, Vec(107.54, 266.14), ScionExciter::Panel::Master_Amplitude_LFO, 1);
   makeKnob(this, Vec(59.17, 277.76), ScionExciter::Panel::Master_Smooth_Attenuate, 3);
   makeKnob(this, Vec(30.71, 266.14), ScionExciter::Panel::Master_Smooth_LFO, 1);
   makeKnob(this, Vec(136.00, 161.17), ScionExciter::Panel::Noise_Amplitude1_Attenuate, 3);
   makeKnob(this, Vec(107.54, 149.55), ScionExciter::Panel::Noise_Amplitude1_LFO, 1);
   makeKnob(this, Vec(59.17, 161.17), ScionExciter::Panel::Noise_Smooth1_Attenuate, 3);
   makeKnob(this, Vec(30.71, 149.55), ScionExciter::Panel::Noise_Smooth1_LFO, 1);
   makeKnob(this, Vec(136.00, 69.15), ScionExciter::Panel::Base1_Amplitude2_Attenuate, 3);
   makeKnob(this, Vec(107.54, 57.53), ScionExciter::Panel::Base1_Amplitude2_LFO, 1);
   makeKnob(this, Vec(59.17, 69.15), ScionExciter::Panel::Base1_Pitch_Attenuate, 3);
   makeKnob(this, Vec(30.71, 57.53), ScionExciter::Panel::Base1_Pitch_LFO, 1);

   makeInput(this, Vec(136.00, 314.61),  ScionExciter::Panel::Master_Amplitude_Modulate, false);
   makeInput(this, Vec(59.17, 314.61),  ScionExciter::Panel::Master_Smooth_Modulate, false);
   makeInput(this, Vec(136.00, 198.01),  ScionExciter::Panel::Noise_Amplitude1_Modulate, false);
   makeInput(this, Vec(59.17, 198.01),  ScionExciter::Panel::Noise_Smooth1_Modulate, false);
   makeInput(this, Vec(136.00, 106.00),  ScionExciter::Panel::Base1_Amplitude2_Modulate, false);
   makeInput(this, Vec(59.17, 106.00),  ScionExciter::Panel::Base1_Pitch_Modulate, false);

   makeOutput(this, Vec(136.17, 355.83), ScionExciter::Panel::Master_Exciter_Out, false);
   makeOutput(this, Vec(58.44, 355.83), ScionExciter::Panel::Master_Base_Out, false);
}

#endif // NOT ScionExciterHPP
