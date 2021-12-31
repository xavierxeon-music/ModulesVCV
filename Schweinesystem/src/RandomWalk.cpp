#include "plugin.hpp"

struct RandomWalk : Module
{
   enum ParamId
   {
      SPEED_PARAM,
      PARAMS_LEN
   };
   enum InputId
   {
      PITCH_INPUT,
      INPUTS_LEN
   };
   enum OutputId
   {
      RANDOM_OUTPUT,
      OUTPUTS_LEN
   };
   enum LightId
   {
      BLINK_LIGHT,
      LIGHTS_LEN
   };

   RandomWalk()
   {
      config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
      configParam(SPEED_PARAM, 0.f, 1.f, 0.f, "");
      configInput(PITCH_INPUT, "");
      configOutput(RANDOM_OUTPUT, "");
   }

   void process(const ProcessArgs& args) override
   {
      // Compute the frequency from the pitch parameter and input
      float pitch = params[SPEED_PARAM].getValue();
      pitch += inputs[PITCH_INPUT].getVoltage();
      pitch = clamp(pitch, -4.f, 4.f);
      // The default pitch is C4 = 261.6256f
      float freq = dsp::FREQ_C4 * std::pow(2.f, pitch);

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

   float phase = 0.f;
   float blinkPhase = 0.f;
};

struct RandomWalkWidget : ModuleWidget
{
   RandomWalkWidget(RandomWalk* module)
   {
      setModule(module);
      setPanel(createPanel(asset::plugin(pluginInstance, "res/RandomWalk.svg")));

      addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
      addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
      addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
      addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

      addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.24, 34.063)), module, RandomWalk::SPEED_PARAM));

      addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(15.24, 108.2)), module, RandomWalk::RANDOM_OUTPUT));

      //VCVButton

      addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 15.81)), module, RandomWalk::BLINK_LIGHT));
   }
};

Model* modelRandomWalk = createModel<RandomWalk, RandomWalkWidget>("RandomWalk");