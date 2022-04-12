#include "DemoDummy.h"
#include "DemoDummyData.h"

#include "Schweinesystem.h"

void DemoDummy::setup()
{
   config(Data::PARAMS_LEN, Data::INPUTS_LEN, Data::OUTPUTS_LEN, Data::LIGHTS_LEN);

   configParam(Data::KNOB, 0.f, 1.f, 0.f, "");

   configInput(Data::INPUT1, "");
   configInput(Data::INPUT2, "");

   configOutput(Data::OUTPUT1, "");
   configOutput(Data::OUTPUT2, "");

}

DemoDummyWidget::DemoDummyWidget(DemoDummy* module)
{
   setModule(module);
   std::string panelPath = asset::plugin(Schweinesystem::instance(), "res/DemoDummy.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(24.384, 95.791)), module, DemoDummy::Data::KNOB));

   addInput(createInputCentered<PJ301MPort>(mm2px(Vec(24.384, 23.386)), module, DemoDummy::Data::INPUT1));
   addInput(createInputCentered<PJ301MPort>(mm2px(Vec(24.384, 57.031)), module, DemoDummy::Data::INPUT2));

   addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(24.384, 36.801)), module, DemoDummy::Data::OUTPUT1));
   addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(24.384, 71.942)), module, DemoDummy::Data::OUTPUT2));

   addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(24.384, 13.285)), module, DemoDummy::Data::LIGHT));
}
