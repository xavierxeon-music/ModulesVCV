#include "Cutoff.h"

Cutoff::Cutoff()
   : Svin::Module()
   , overSlider(this, Panel::Over, Panel::RGB_Over)
   , input(this, Panel::Input)
   , output(this, Panel::Output)
{
   setup();

   overSlider.setRange(0.1, 1.0);
   overSlider.setDefaultColor(Color(0, 255, 0));
   overSlider.setOff();
}

void Cutoff::process(const ProcessArgs& args)
{
   const float inVoltage = input.getVoltage();

   const bool over = (inVoltage > overSlider.getValue());
   overSlider.setActive(over);

   const float outVoltage = over ? inVoltage : 0.0;
   output.setVoltage(outVoltage);
}

void Cutoff::load(const Svin::Json::Object& rootObject)
{
   overSlider.setValue(rootObject.get("over").toReal());
}

void Cutoff::save(Svin::Json::Object& rootObject)
{
   rootObject.set("over", overSlider.getValue());
}

// widget

CutoffWidget::CutoffWidget(Cutoff* module)
: Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelCutoff = Svin::Origin::the()->addModule<Cutoff, CutoffWidget>("Cutoff");

