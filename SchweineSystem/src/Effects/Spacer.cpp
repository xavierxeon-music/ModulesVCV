#include "Spacer.h"

Spacer::Spacer()
   : Svin::Module()
   , input(this, Panel::In)
   , leftOutput(this, Panel::LeftOut)
   , rightOutput(this, Panel::RightOut)
   , lines{}
{
   setup();

   for (uint8_t index = 0; index < lineCount; index++)
   {
      lines[index].delay.setDelay(2.0 * (index + 1), getSampleRate());

      lines[index].filter.setFrequency(500);
      lines[index].filter.init(getSampleRate());
      lines[index].delay.setFeedback(0.6);
      lines[index].delay.setFeedbackEffect(&lines[index].filter);

      lines[index].delay.setFeedfront(0.0);
   }
}

void Spacer::process(const ProcessArgs& args)
{
   const float in = input.getVoltage();
   float left = 0;
   float right = 0;

   for (uint8_t index = 0; index < lineCount; index++)
   {
      const float value = lines[index].delay.changeSound(in);
      if (0 == (index % 2))
         left += value;
      else
         right += value;
   }

   const float norm = lineCount / 2;
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

