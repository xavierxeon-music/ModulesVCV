#include "RandomWalk.h"

#include "Schweinesystem.h"

RandomWalk::RandomWalk()
   : Module()
{
   config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);

   configParam(SPEED_PARAM, 0.f, 1.f, 0.f, "");
   configParam(CUTOFF_PARAM, 0.f, 1.f, 0.f, "");
   configOutput(RANDOM_OUTPUT, "");
}

void RandomWalk::process(const ProcessArgs& args)
{
   // The default pitch is C4 = 261.6256f
   float freq = 261.6256f;

   // Accumulate the phase
   phase += freq * args.sampleTime;
   if (phase >= 0.5f)
      phase -= 1.f;

   // Compute the sine output
   float sine = std::sin(2.f * M_PI * phase);
   // Audio signals are typically +/-5V
   // https://vcvrack.com/manual/VoltageStandards
   outputs[RANDOM_OUTPUT].setVoltage(5.f * sine);

   // Blink light at 1Hz
   blinkPhase += args.sampleTime;
   if (blinkPhase >= 1.f)
      blinkPhase -= 1.f;
   lights[BLINK_LIGHT].setBrightness(blinkPhase < 0.5f ? 1.f : 0.f);
}

RandomWalkWidget::RandomWalkWidget(RandomWalk* module)
   : ModuleWidget()
{
   setModule(module);
   setPanel(createPanel(asset::plugin(pluginInstance, "res/RandomWalk.svg")));

   // screws
   addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
   addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
   addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
   addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

   // function
   addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.24, 34.063)), module, RandomWalk::SPEED_PARAM));
   addParam(createParamCentered<VCVLatch>(mm2px(Vec(15.24, 64.063)), module, RandomWalk::CUTOFF_PARAM));
   addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 75.81)), module, RandomWalk::BLINK_LIGHT));
   addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(15.24, 103.2)), module, RandomWalk::RANDOM_OUTPUT));
}
