#include "ScionExciter.h"

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

   float mod = 0.0;
   if ((BioFeedbackDummy::BaseAmplitude == id || BioFeedbackDummy::NoiseAmplitude == id) && 0.0 == slider.getValue())
   {
      parent->exciter.setState(id, 0.0);
   }
   else
   {
      mod = modInput.isConnected() ? 0.1 * modInput.getVoltage() : lfo.createSound();
      mod *= modAttenuator.getValue();
      float value = slider.getValue() + (scale * mod);
      parent->exciter.setState(id, value);
   }

   if (0.0 <= mod)
   {
      const uint8_t green = static_cast<uint8_t>(255.0 * mod);
      slider.setColor(Svin::Color{0, green, 0});
   }
   else
   {
      const uint8_t red = static_cast<uint8_t>(-255.0 * mod);
      slider.setColor(Svin::Color{red, 0, 0});
   }
}

void ScionExciter::Section::load(const BioFeedbackDummy::FunctionId& id, const Svin::Json::Object& rootObject)
{
   const Svin::Json::Object object = rootObject.get(getName(id)).toObject();

   slider.setValue(object.get("value").toReal());
   modAttenuator.setValue(object.get("attenuate").toReal());
   lfoPitchKnob.setValue(object.get("lfoPitch").toReal());
}

void ScionExciter::Section::save(const BioFeedbackDummy::FunctionId& id, Svin::Json::Object& rootObject)
{
   Svin::Json::Object object;
   object.set("value", slider.getValue());
   object.set("attenuate", modAttenuator.getValue());
   object.set("lfoPitch", lfoPitchKnob.getValue());

   rootObject.set(getName(id), object);
}

std::string ScionExciter::Section::getName(const BioFeedbackDummy::FunctionId& id) const
{
   static const std::map<BioFeedbackDummy::FunctionId, std::string> nameMap = {{BioFeedbackDummy::BaseFrequency, "BaseFrequency"},
                                                                               {BioFeedbackDummy::BaseAmplitude, "BaseAmplitude"},
                                                                               {BioFeedbackDummy::NoiseSmooth, "NoiseSmooth"},
                                                                               {BioFeedbackDummy::NoiseAmplitude, "NoiseAmplitude"},
                                                                               {BioFeedbackDummy::MasterSmooth, "MasterSmooth"},
                                                                               {BioFeedbackDummy::MasterAmplitude, "MasterAmplitude"}};

   return nameMap.at(id);
}

// main

ScionExciter::ScionExciter()
   : Svin::Module()
   , exciter(getSampleRate())
   , sections()
   , exciterOutput(this, Panel::Master_Exciter_Out)
   , baseOutput(this, Panel::Master_Base_Out)
{
   setup();

   sections[BioFeedbackDummy::BaseFrequency] = new Section(this,
                                                           Panel::Base1_Pitch_Value,
                                                           Panel::RGB_Base1_Pitch_Value,
                                                           Panel::Base1_Pitch_Modulate,
                                                           Panel::Base1_Pitch_Attenuate,
                                                           Panel::Base1_Pitch_LFO);
   sections[BioFeedbackDummy::BaseFrequency]->setup(45.0, 55.0, 50.0);

   sections[BioFeedbackDummy::BaseAmplitude] = new Section(this,
                                                           Panel::Base1_Amplitude2_Value,
                                                           Panel::RGB_Base1_Amplitude2_Value,
                                                           Panel::Base1_Amplitude2_Modulate,
                                                           Panel::Base1_Amplitude2_Attenuate,
                                                           Panel::Base1_Amplitude2_LFO);
   sections[BioFeedbackDummy::BaseAmplitude]->setup(0.0, 1.0, 0.5);

   // noise
   sections[BioFeedbackDummy::NoiseSmooth] = new Section(this,
                                                         Panel::Noise_Smooth1_Value,
                                                         Panel::RGB_Noise_Smooth1_Value,
                                                         Panel::Noise_Smooth1_Modulate,
                                                         Panel::Noise_Smooth1_Attenuate,
                                                         Panel::Noise_Smooth1_LFO);
   sections[BioFeedbackDummy::NoiseSmooth]->setup(0.7, 0.99, 0.7);

   sections[BioFeedbackDummy::NoiseAmplitude] = new Section(this,
                                                            Panel::Noise_Amplitude1_Value,
                                                            Panel::RGB_Noise_Amplitude1_Value,
                                                            Panel::Noise_Amplitude1_Modulate,
                                                            Panel::Noise_Amplitude1_Attenuate,
                                                            Panel::Noise_Amplitude1_LFO);
   sections[BioFeedbackDummy::NoiseAmplitude]->setup(0.0, 1.0, 0.5);

   // master
   sections[BioFeedbackDummy::MasterSmooth] = new Section(this,
                                                          Panel::Master_Smooth_Value,
                                                          Panel::RGB_Master_Smooth_Value,
                                                          Panel::Master_Smooth_Modulate,
                                                          Panel::Master_Smooth_Attenuate,
                                                          Panel::Master_Smooth_LFO);
   sections[BioFeedbackDummy::MasterSmooth]->setup(0.6, 0.99, 0.6);

   sections[BioFeedbackDummy::MasterAmplitude] = new Section(this,
                                                             Panel::Master_Amplitude_Value,
                                                             Panel::RGB_Master_Amplitude_Value,
                                                             Panel::Master_Amplitude_Modulate,
                                                             Panel::Master_Amplitude_Attenuate,
                                                             Panel::Master_Amplitude_LFO);
   sections[BioFeedbackDummy::MasterAmplitude]->setup(0.0, 1.0, 0.5);
}

void ScionExciter::process(const ProcessArgs& args)
{
   sections[BioFeedbackDummy::BaseFrequency]->process(BioFeedbackDummy::BaseFrequency, 2.0);

   for (const BioFeedbackDummy::FunctionId& id : {BioFeedbackDummy::BaseAmplitude, BioFeedbackDummy::NoiseAmplitude, BioFeedbackDummy::MasterAmplitude})
      sections[id]->process(id);

   for (const BioFeedbackDummy::FunctionId& id : {BioFeedbackDummy::NoiseSmooth, BioFeedbackDummy::MasterSmooth})
      sections[id]->process(id, 0.1);

   float baseSoundVoltage = 0;
   const float voltage = exciter.compileSignalVoltage(&baseSoundVoltage);
   baseOutput.setVoltage(baseSoundVoltage);
   exciterOutput.setVoltage(voltage);
}

void ScionExciter::load(const Svin::Json::Object& rootObject)
{
   for (const BioFeedbackDummy::FunctionId& id : {BioFeedbackDummy::BaseFrequency, BioFeedbackDummy::BaseAmplitude, BioFeedbackDummy::NoiseSmooth, BioFeedbackDummy::NoiseAmplitude, BioFeedbackDummy::MasterSmooth, BioFeedbackDummy::MasterAmplitude})
      sections[id]->load(id, rootObject);
}

void ScionExciter::save(Svin::Json::Object& rootObject)
{
   for (const BioFeedbackDummy::FunctionId& id : {BioFeedbackDummy::BaseFrequency, BioFeedbackDummy::BaseAmplitude, BioFeedbackDummy::NoiseSmooth, BioFeedbackDummy::NoiseAmplitude, BioFeedbackDummy::MasterSmooth, BioFeedbackDummy::MasterAmplitude})
      sections[id]->save(id, rootObject);
}

// widget

ScionExciterWidget::ScionExciterWidget(ScionExciter* module)
   : Svin::ModuleWidget(module)
{
   setup();
}
// creete module
Model* modelScionExciter = Svin::Origin::the()->addModule<ScionExciter, ScionExciterWidget>("ScionExciter");

