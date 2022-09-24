#include "SixPack.h"

SixPack::SixPack()
   : Svin::Module()
   , panValueList(this)
   , panAttenuateList(this)
   , panPitchList(this)
   , panModInput(this, Panel::Pan_Modulate)
   , panModLFO{}
   , phaseValueList(this)
   , phaseAttenuateList(this)
   , phasePitchList(this)
   , phaseModInput(this, Panel::Phase_Modulate)
   , phaseModLFO{}
   , detuneValueList(this)
   , detuneAttenuateList(this)
   , detunePitchList(this)
   , detuneModInput(this, Panel::Detune_Modulate)
   , detuneModLFO{}
   , syncInput(this, Panel::Sync)
   , fmInput(this, Panel::FM)
   , fmAttenutate(this, Panel::FMAttenuate)
   , pitchInput(this, Panel::Pitch)
   , pitchKnob(this, Panel::Offset)
   , oscilator{}
   , stereoOutput(this, Panel::Out)
   , coreOscilator()
   , coreOutput(this, Panel::One)
   , sineTable()
   , sawTable()
   , squareTable()
{
   setup();

   panValueList.append({Panel::One_Pan6_Value,
                        Panel::Two_Pan5_Value,
                        Panel::Three_Pan4_Value,
                        Panel::Four_Pan3_Value,
                        Panel::Five_Pan2_Value,
                        Panel::Six_Pan1_Value});

   panAttenuateList.append({Panel::One_Pan6_Attenuate,
                            Panel::Two_Pan5_Attenuate,
                            Panel::Three_Pan4_Attenuate,
                            Panel::Four_Pan3_Attenuate,
                            Panel::Five_Pan2_Attenuate,
                            Panel::Six_Pan1_Attenuate});

   panPitchList.append({Panel::One_Pan6_LFO,
                        Panel::Two_Pan5_LFO,
                        Panel::Three_Pan4_LFO,
                        Panel::Four_Pan3_LFO,
                        Panel::Five_Pan2_LFO,
                        Panel::Six_Pan1_LFO});

   phaseValueList.append({Panel::One_Phase6_Value,
                          Panel::Two_Phase5_Value,
                          Panel::Three_Phase4_Value,
                          Panel::Four_Phase3_Value,
                          Panel::Five_Phase2_Value,
                          Panel::Six_Phase1_Value});

   phaseAttenuateList.append({Panel::One_Phase6_Attenuate,
                              Panel::Two_Phase5_Attenuate,
                              Panel::Three_Phase4_Attenuate,
                              Panel::Four_Phase3_Attenuate,
                              Panel::Five_Phase2_Attenuate,
                              Panel::Six_Phase1_Attenuate});

   phasePitchList.append({Panel::One_Phase6_LFO,
                          Panel::Two_Phase5_LFO,
                          Panel::Three_Phase4_LFO,
                          Panel::Four_Phase3_LFO,
                          Panel::Five_Phase2_LFO,
                          Panel::Six_Phase1_LFO});

   detuneValueList.append({Panel::One_Detune6_Value,
                           Panel::Two_Detune5_Value,
                           Panel::Three_Detune4_Value,
                           Panel::Four_Detune3_Value,
                           Panel::Five_Detune2_Value,
                           Panel::Six_Detune1_Value});

   detuneAttenuateList.append({Panel::One_Detune6_Attenuate,
                               Panel::Two_Detune5_Attenuate,
                               Panel::Three_Detune4_Attenuate,
                               Panel::Four_Detune3_Attenuate,
                               Panel::Five_Detune2_Attenuate,
                               Panel::Six_Detune1_Attenuate});

   detunePitchList.append({Panel::One_Detune6_LFO,
                           Panel::Two_Detune5_LFO,
                           Panel::Three_Detune4_LFO,
                           Panel::Four_Detune3_LFO,
                           Panel::Five_Detune2_LFO,
                           Panel::Six_Detune1_LFO});

   sineTable.setWaveform(Standard::Waveform::Sine);
   sawTable.setWaveform(Standard::Waveform::Saw);
   squareTable.setWaveform(Standard::Waveform::Square);

   fmAttenutate.setRange(-1.0, 1.0, 0.0);
   pitchKnob.setRange(0.0, 5.0);
   coreOscilator.init(&squareTable, getSampleRate());

   for (uint8_t voice = 0; voice < 6; voice++)
   {
      panValueList[voice]->setRange(-1.0, 1.0, 0.0);
      panAttenuateList[voice]->setRange(-1.0, 1.0, 0.0);
      panPitchList[voice]->setRange(0.1, 2.0, 1.0);
      panModLFO[voice].init(&sineTable, getSampleRate());

      phaseValueList[voice]->setRange(-1.0, 1.0, 0.0);
      phaseAttenuateList[voice]->setRange(-1.0, 1.0, 0.0);
      phasePitchList[voice]->setRange(0.1, 2.0, 1.0);
      phaseModLFO[voice].init(&sineTable, getSampleRate());

      detuneValueList[voice]->setRange(-1.0, 1.0, 0.0);
      detuneAttenuateList[voice]->setRange(-1.0, 1.0, 0.0);
      detunePitchList[voice]->setRange(0.1, 2.0, 1.0);
      detuneModLFO[voice].init(&sineTable, getSampleRate());

      oscilator[voice].init(&sawTable, getSampleRate());
   }
}

void SixPack::process(const ProcessArgs& args)
{
   if (syncInput.isTriggered())
   {
      coreOscilator.reset();
      for (uint8_t voice = 0; voice < 6; voice++)
         oscilator[voice].reset();
   }

   const float pitchVoltage = pitchInput.getVoltage() + pitchKnob.getValue();
   const float coreFrequency = Abstract::Oscilator::frequencyFromCV(pitchVoltage);

   coreOscilator.setFrequency(coreFrequency);
   const float core = coreOscilator.createSound();
   coreOutput.setVoltage(core * 10.0);

   float fmVoltage = fmInput.getVoltage() * fmAttenutate.getValue();

   float left = 0.0;
   float right = 0.0;

   for (uint8_t voice = 0; voice < 6; voice++)
   {
      float pan = panValueList[voice]->getValue();
      if (panModInput.isConnected())
      {
      }
      else
      {
         panModLFO[voice].setFrequency(panPitchList[voice]->getValue());
         pan += panModLFO[voice].createSound() * panAttenuateList[voice]->getValue();
      }
      pan += 1.0;
      pan /= 2.0;

      float phase = phaseValueList[voice]->getValue();
      if (phaseModInput.isConnected())
      {
      }
      else
      {
         phaseModLFO[voice].setFrequency(phasePitchList[voice]->getValue());
         phase += phaseModLFO[voice].createSound() * phaseAttenuateList[voice]->getValue();
      }
      oscilator[voice].setPhase(phase);

      float detune = detuneValueList[voice]->getValue();
      if (detuneModInput.isConnected())
      {
      }
      else
      {
         detuneModLFO[voice].setFrequency(detunePitchList[voice]->getValue());
         detune += detuneModLFO[voice].createSound() * detuneAttenuateList[voice]->getValue();
      }
      const float voltage = pitchVoltage + detune + fmVoltage;
      const float frequency = Abstract::Oscilator::frequencyFromCV(voltage);
      oscilator[voice].setFrequency(frequency);

      const float value = oscilator[voice].createSound();
      left += pan * value;
      right += (1.0 - pan) * value;
   }

   left /= 3.0;
   right /= 3.0;

   stereoOutput.setNumberOfChannels(2);
   stereoOutput.setVoltage(left * 10.0, 0);
   stereoOutput.setVoltage(right * 10.0, 1);
}

void SixPack::load(const Svin::Json::Object& rootObject)
{
   pitchKnob.setValue(rootObject.get("offset").toReal());
   fmAttenutate.setValue(rootObject.get("fmAttenuate").toReal());

   const Svin::Json::Object panObject = rootObject.get("pan").toObject();
   const Svin::Json::Array panValueArray = panObject.get("value").toArray();
   const Svin::Json::Array panAttenuateArray = panObject.get("attenuate").toArray();
   const Svin::Json::Array panPitchArray = panObject.get("pitch").toArray();

   const Svin::Json::Object phaseObject = rootObject.get("phase").toObject();
   const Svin::Json::Array phaseValueArray = phaseObject.get("value").toArray();
   const Svin::Json::Array phaseAttenuateArray = phaseObject.get("attenuate").toArray();
   const Svin::Json::Array phasePitchArray = phaseObject.get("pitch").toArray();

   const Svin::Json::Object detuneObject = rootObject.get("detune").toObject();
   const Svin::Json::Array detuneValueArray = detuneObject.get("value").toArray();
   const Svin::Json::Array detuneAttenuateArray = detuneObject.get("attenuate").toArray();
   const Svin::Json::Array detunePitchArray = detuneObject.get("pitch").toArray();

   for (uint8_t voice = 0; voice < 6; voice++)
   {
      panValueList[voice]->setValue(panValueArray.at(voice).toReal());
      panAttenuateList[voice]->setValue(panAttenuateArray.at(voice).toReal());
      panPitchList[voice]->setValue(panPitchArray.at(voice).toReal());

      phaseValueList[voice]->setValue(phaseValueArray.at(voice).toReal());
      phaseAttenuateList[voice]->setValue(phaseAttenuateArray.at(voice).toReal());
      phasePitchList[voice]->setValue(phasePitchArray.at(voice).toReal());

      detuneValueList[voice]->setValue(detuneValueArray.at(voice).toReal());
      detuneAttenuateList[voice]->setValue(detuneAttenuateArray.at(voice).toReal());
      detunePitchList[voice]->setValue(detunePitchArray.at(voice).toReal());
   }
}

void SixPack::save(Svin::Json::Object& rootObject)
{
   Svin::Json::Array panValueArray;
   Svin::Json::Array panAttenuateArray;
   Svin::Json::Array panPitchArray;

   Svin::Json::Array phaseValueArray;
   Svin::Json::Array phaseAttenuateArray;
   Svin::Json::Array phasePitchArray;

   Svin::Json::Array detuneValueArray;
   Svin::Json::Array detuneAttenuateArray;
   Svin::Json::Array detunePitchArray;

   for (uint8_t voice = 0; voice < 6; voice++)
   {
      panValueArray.append(panValueList[voice]->getValue());
      panAttenuateArray.append(panAttenuateList[voice]->getValue());
      panPitchArray.append(panPitchList[voice]->getValue());

      phaseValueArray.append(phaseValueList[voice]->getValue());
      phaseAttenuateArray.append(phaseAttenuateList[voice]->getValue());
      phasePitchArray.append(phasePitchList[voice]->getValue());

      detuneValueArray.append(detuneValueList[voice]->getValue());
      detuneAttenuateArray.append(detuneAttenuateList[voice]->getValue());
      detunePitchArray.append(detunePitchList[voice]->getValue());
   }

   Svin::Json::Object panObject;
   panObject.set("value", panValueArray);
   panObject.set("attenuate", panAttenuateArray);
   panObject.set("pitch", panPitchArray);

   Svin::Json::Object phaseObject;
   phaseObject.set("value", phaseValueArray);
   phaseObject.set("attenuate", phaseAttenuateArray);
   phaseObject.set("pitch", phasePitchArray);

   Svin::Json::Object detuneObject;
   detuneObject.set("value", detuneValueArray);
   detuneObject.set("attenuate", detuneAttenuateArray);
   detuneObject.set("pitch", detunePitchArray);

   rootObject.set("offset", pitchKnob.getValue());
   rootObject.set("fmAttenuate", fmAttenutate.getValue());
   rootObject.set("pan", panObject);
   rootObject.set("phase", phaseObject);
   rootObject.set("detune", detuneObject);
}

void SixPack::onSampleRateChange(const SampleRateChangeEvent& event)
{
   const float sampleRate = event.sampleRate;
   for (uint8_t voice = 0; voice < 6; voice++)
      oscilator[voice].init(&sawTable, sampleRate);
}

// widget

SixPackWidget::SixPackWidget(SixPack* module)
: Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelSixPack = Svin::Origin::the()->addModule<SixPack, SixPackWidget>("SixPack");

