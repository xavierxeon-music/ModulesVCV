#include "Spacer.h"

Spacer::Spacer()
   : Svin::Module()
   , input(this, Panel::In)
   , leftOutput(this, Panel::LeftOut)
   , rightOutput(this, Panel::RightOut)
   , cutoffKnob(this, Panel::Cutoff)
   , feedbackKnob(this, Panel::Feedback)
   , delayKnob(this, Panel::Delay)
   , sineTable(Standard::Waveform::Sine)
   , lines{}
{
   setup();

   cutoffKnob.setRange(50, 15000, 500);
   feedbackKnob.setRange(0.0, 0.99, 0.5);
   delayKnob.setRange(0.1, 10.0, 2.0);

   for (uint8_t index = 0; index < lineCount; index++)
   {
      Line& line = lines[index];
      line.filter.setFrequency(cutoffKnob.getValue());
      line.filter.init(getSampleRate(), FilterMode::BandPass);

      line.delay.setDelay(delayKnob.getValue() * (index + 1), getSampleRate());
      line.delay.setFeedback(feedbackKnob.getValue());
      line.delay.setFeedbackEffect(&line.filter);
      line.delay.setFeedfront(0.0);

      line.lfo.init(&sineTable, getSampleRate());
      line.lfo.setCycleDuration(0.1 * (index + 1));
   }
}

void Spacer::process(const ProcessArgs& args)
{
   const float in = input.getVoltage();
   float left = 0;
   float right = 0;

   for (uint8_t index = 0; index < lineCount; index++)
   {
      Line& line = lines[index];
      line.filter.setFrequency(cutoffKnob.getValue());
      line.delay.setFeedback(feedbackKnob.getValue());
      line.delay.setDelay(delayKnob.getValue() * (index + 1), getSampleRate());

      const float value = line.delay.changeSound(in);
      const float pan = 0.5 * (line.lfo.createSound() + 1.0);
      left += value * (1.0 - pan);
      right += value * pan;
   }

   const float norm = lineCount / 16;
   left /= norm;
   right /= norm;

   leftOutput.setVoltage(left);
   rightOutput.setVoltage(right);
}

// widget

SpacerWidget::SpacerWidget(Spacer* module)
: Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelSpacer = Svin::Origin::the()->addModule<Spacer, SpacerWidget>("Spacer");

