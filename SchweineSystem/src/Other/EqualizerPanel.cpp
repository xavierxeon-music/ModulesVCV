#include "Equalizer.h"
#include "EqualizerPanel.h"

#include <SchweineSystemMaster.h>
#include <limits>

void Equalizer::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configParam(Panel::Knob_Smooth_Value, -1.f, 1.f, 0.f, "");
   configParam(Panel::Knob_Amount_Value, -1.f, 1.f, 0.f, "");
   configParam(Panel::Knob_Frequency_Value, -1.f, 1.f, 0.f, "");

   configInput(Panel::AudioInput, "AudioInput");
   configInput(Panel::Freqeuncy, "Freqeuncy");
   configInput(Panel::Amount, "Amount");
   configInput(Panel::Smooth, "Smooth");

   configOutput(Panel::AudioOutput, "AudioOutput");

   configDisplay(Panel::Text_Frequency_Display, "Frequency_Display");
}

void EqualizerWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/Equalizer.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeLEDButton(this, Vec(73.84, 43.31), Equalizer::Panel::Frequency_Quantize, Equalizer::Panel::RGB_Frequency_Quantize);

   makeKnob(this, Vec(41.23, 244.17), Equalizer::Panel::Knob_Smooth_Value, 2);
   makeKnob(this, Vec(63.52, 187.89), Equalizer::Panel::Knob_Amount_Value, 2);
   makeKnob(this, Vec(52.50, 117.62), Equalizer::Panel::Knob_Frequency_Value, 3);

   makeInput(this, Vec(24.17, 355.83),  Equalizer::Panel::AudioInput);
   makeInput(this, Vec(24.17, 308.71),  Equalizer::Panel::Freqeuncy);
   makeInput(this, Vec(52.50, 308.71),  Equalizer::Panel::Amount);
   makeInput(this, Vec(80.83, 308.71),  Equalizer::Panel::Smooth);

   makeOutput(this, Vec(80.83, 355.83), Equalizer::Panel::AudioOutput);

   makeDisplay(this, Vec(11.50, 57.49), 5, Equalizer::Panel::Text_Frequency_Display, Equalizer::Panel::RGB_Frequency_Display);
}

