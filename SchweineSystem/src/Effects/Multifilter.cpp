#include "Multifilter.h"

#include <Abstract/AbstractOscilator.h>
#include <Tools/Range.h>

#include <SvinOrigin.h>

// Voice

Multifilter::Voice::Voice()
   : noOfFilters(1)
   , filters{}
{
}

void Multifilter::Voice::init(const float& sampleRate, const FilterMode& filterMode)
{
   for (uint8_t channel = 0; channel < 16; channel++)
      filters[channel].init(sampleRate, filterMode);
}

void Multifilter::Voice::update(const Svin::Input& pitchInput, const bool quantize, const float& offset, const float& resonance, const float& drive)
{
   noOfFilters = pitchInput.isConnected() ? pitchInput.getNumberOfChannels() : 1;
   for (uint8_t channel = 0; channel < noOfFilters; channel++)
   {
      float voltage = pitchInput.getVoltage(channel);
      voltage = Range::clamp<float>(voltage, 0.0, 10.0);
      voltage += offset;

      float frequency = Abstract::Oscilator::frequencyFromCV(voltage);
      if (quantize)
      {
         const Note note = Note::fromFrequency(frequency);
         frequency = note.frequency;
      }
      filters[channel].setFrequency(frequency);
      filters[channel].setResonance(resonance);
      filters[channel].setDrive(drive);
   }
}

float Multifilter::Voice::changeSound(const float& value)
{
   float output = 0;
   for (uint8_t channel = 0; channel < noOfFilters; channel++)
      output += filters[channel].changeSound(value);

   output /= noOfFilters;
   return output;
}

// Multifilter

Multifilter::Multifilter()
   : Svin::Module()
   , resoModulateInput(this, Panel::ResoModulate)
   , resoAttenuateKnob(this, Panel::ResoAttenuator)
   , resoKnob(this, Panel::Reso)
   , driveModulateInput(this, Panel::DriveModulate)
   , driveAttenuateKnob(this, Panel::DriveAttenuate)
   , driveKnob(this, Panel::Drive)
   , offsetInput(this, Panel::OffsetOverride)
   , offsetKnob(this, Panel::Offset)
   , pitchInput(this, Panel::Pitch)
   , quantizeButton(this, Panel::Quantize, Panel::RGB_Quantize)
   , audioInput(this, Panel::In)
   , audioOutput(this, Panel::Out)
   , modeSlider(this, Panel::Mode, Panel::RGB_Mode)
   , voices{}
   , filterMode(FilterMode::LowPass)
{
   setup();
   resoKnob.setRange(0.0, 1.0);
   driveKnob.setRange(0.0, 1.0);
   quantizeButton.setDefaultColor(Color{0, 0, 255});

   offsetKnob.setRange(-2.0, 2.0, 0.0);

   modeSlider.setRange(0.0, 5.0, 1.0);
   modeSlider.enableSteps(true);
   modeSlider.setDefaultColor(Color{255, 255, 0});
   modeSlider.setOn();

   reinit();
}

void Multifilter::process(const ProcessArgs& args)
{
   const uint8_t noOfChannels = audioInput.getNumberOfChannels();
   audioOutput.setNumberOfChannels(noOfChannels);

   float resonance = resoKnob.getValue();
   if (resoModulateInput.isConnected())
   {
      resonance += 0.1 * resoModulateInput.getVoltage() * resoAttenuateKnob.getValue();
      resonance = Range::clamp<float>(resonance, 0.0, 1.0);
   }

   float drive = driveKnob.getValue();
   if (driveModulateInput.isConnected())
   {
      drive += 0.1 * driveModulateInput.getVoltage() * driveAttenuateKnob.getValue();
      drive = Range::clamp<float>(drive, 0.0, 1.0);
   }

   float offset = offsetKnob.getValue();
   if (offsetInput.isConnected())
   {
      offset = 0.1 * offsetInput.getVoltage() * offsetKnob.getValue();
   }

   const FilterMode sliderMode = static_cast<FilterMode>(modeSlider.getValue());
   if (sliderMode != filterMode)
   {
      filterMode = sliderMode;
      reinit();
   }
   modeSlider.setActive(filterMode != FilterMode::Off);

   const bool quantize = quantizeButton.isLatched();
   quantizeButton.setActive(quantize);

   for (uint8_t channel = 0; channel < 16; channel++)
   {
      if (channel >= noOfChannels)
      {
         audioOutput.setVoltage(0.0, channel);
         continue;
      }

      voices[channel].update(pitchInput, quantize, offset, resonance, drive);

      const float input = 0.1 * audioInput.getVoltage(channel);
      const float value = voices[channel].changeSound(input);
      const float output = 10.0 * value;
      audioOutput.setVoltage(output, channel);
   }
}

void Multifilter::reinit()
{
   for (uint8_t channel = 0; channel < 16; channel++)
   {
      voices[channel].init(getSampleRate(), filterMode);
   }
}

void Multifilter::load(const Svin::Json::Object& rootObject)
{
   resoAttenuateKnob.setValue(rootObject.get("resoAttenuate").toReal());
   resoKnob.setValue(rootObject.get("reso").toReal());

   driveAttenuateKnob.setValue(rootObject.get("driveAttenuate").toReal());
   driveKnob.setValue(rootObject.get("drive").toReal());

   offsetKnob.setValue(rootObject.get("offseet").toReal());
   quantizeButton.setLatched(rootObject.get("quantize").toBool());

   modeSlider.setValue(rootObject.get("mode").toReal());
}

void Multifilter::save(Svin::Json::Object& rootObject)
{
   rootObject.set("resoAttenuate", resoAttenuateKnob.getValue());
   rootObject.set("reso", resoKnob.getValue());

   rootObject.set("driveAttenuate", driveAttenuateKnob.getValue());
   rootObject.set("drive", driveKnob.getValue());

   rootObject.set("offseet", offsetKnob.getValue());
   rootObject.set("quantize", quantizeButton.isLatched());

   rootObject.set("mode", modeSlider.getValue());
}

void Multifilter::onSampleRateChange(const SampleRateChangeEvent& e)
{
   (void)e;
   reinit();
}

// widget

MultifilterWidget::MultifilterWidget(Multifilter* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelMultifilter = Svin::Origin::the()->addModule<Multifilter, MultifilterWidget>("Multifilter");

