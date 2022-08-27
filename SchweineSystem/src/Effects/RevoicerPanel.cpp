#include "RevoicerPanel.h"
#include "Revoicer.h"

#include <SvinMaster.h>
#include <limits>

void Revoicer::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Quality_Down, "Quality_Down");
   configButton(Panel::Quality_Up, "Quality_Up");

   configInput(Panel::AudioInput, "AudioInput");

   configOutput(Panel::AudioOutput, "AudioOutput");

   configText(Panel::Text_Quality_Value, "Quality_Value");
}

void RevoicerWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Master::the()->instance(), "res/Effects/Revoicer.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(30.33, 183.71), Revoicer::Panel::Quality_Down);
   makeButton(this, Vec(30.33, 134.83), Revoicer::Panel::Quality_Up);

   makeInput(this, Vec(30.00, 300.34), Revoicer::Panel::AudioInput);

   makeOutput(this, Vec(30.68, 344.57), Revoicer::Panel::AudioOutput);

   makeLCD(this, Vec(11.00, 147.27), 2, Revoicer::Panel::Text_Quality_Value, Revoicer::Panel::RGB_Quality_Value);
}
