#include "Revoicer.h"
#include "RevoicerPanel.h"

#include <SchweineSystemMaster.h>
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
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/Revoicer.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(30.33, 220.71), Revoicer::Panel::Quality_Down);
   makeButton(this, Vec(30.33, 171.83), Revoicer::Panel::Quality_Up);

   makeInput(this, Vec(30.00, 84.05),  Revoicer::Panel::AudioInput);

   makeOutput(this, Vec(30.68, 344.57), Revoicer::Panel::AudioOutput);

   makeLCD(this, Vec(11.00, 184.27), 2, Revoicer::Panel::Text_Quality_Value, Revoicer::Panel::RGB_Quality_Value);
}

