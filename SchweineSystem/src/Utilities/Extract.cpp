#include "Extract.h"

static const Spectrum::Quality quality = Spectrum::Quality::Low;

Extract::Extract()
   : Svin::Module()
   , Abstract::ThreadeBufferEffect(Spectrum::compileBufferSize(quality))
   , audioInput(this, Panel::AudioInput)
   , audioPassthrough(this, Panel::AudioOutput)
   , pitchOutput(this, Panel::Pitch)
   , gateOutput(this, Panel::Gate)
   , spectrum(quality)
   , voltages{}
   , sampleRate(getSampleRate())
   , numberOfVoices(0)
{
   setup();

   for (uint8_t index = 0; index < 16; index++)
      voltages[index] = 0.0;
}

void Extract::process(const ProcessArgs& args)
{
   const float voltage = audioInput.getVoltage();
   audioPassthrough.setVoltage(voltage);

   changeSound(0.1 * voltage);

   pitchOutput.setNumberOfChannels(16);
   gateOutput.setNumberOfChannels(16);
   for (uint8_t index = 0; index < 16; index++)
   {
      if (index < numberOfVoices)
      {
         pitchOutput.setVoltage(voltages[index], index);
         gateOutput.setOn(index);
      }
      else
      {
         pitchOutput.setVoltage(0.0, index);
         gateOutput.setOff(index);
      }
   }
}

Data Extract::proccessBuffer(const Data& input)
{
   const Spectrum::Map spectrumMap = spectrum.analyse(input, sampleRate);

   std::map<float, float> amplitudeMap;
   Data amplitudeList;
   for (Spectrum::Map::const_iterator it = spectrumMap.cbegin(); it != spectrumMap.cend(); it++)
   {
      amplitudeMap[it->second] = it->first;
      amplitudeList.push_back(it->second);
   }

   std::sort(amplitudeList.begin(), amplitudeList.end(), std::greater<float>());

   numberOfVoices = 0;
   for (uint8_t index = 0; index < 16; index++)
   {
      const float amplitude = amplitudeList.at(index);
      if (10 > amplitude)
         continue;

      const float frequency = amplitudeMap[amplitude];
      const Note note = Note::fromFrequency(frequency);
      voltages[numberOfVoices] = note.voltage;
      numberOfVoices++;
   }

   return input; // will not be used, but must be same saize as input
}

void Extract::onSampleRateChange(const SampleRateChangeEvent& e)
{
   sampleRate = e.sampleRate;
}

// widget

ExtractWidget::ExtractWidget(Extract* module)
: Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelExtract = Svin::Origin::the()->addModule<Extract, ExtractWidget>("Extract");

