#ifndef RandomWalkH
#define RandomWalkH

#include <rack.hpp>
using namespace rack;

struct RandomWalk : Module
{
   enum ParamId
   {
      SPEED_PARAM,
      CUTOFF_PARAM,
      PARAMS_LEN
   };
   enum InputId
   {
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

   RandomWalk();
   void process(const ProcessArgs& args) override;

   float phase = 0.f;
   float blinkPhase = 0.f;
};

struct RandomWalkWidget : ModuleWidget
{
   RandomWalkWidget(RandomWalk* module);
};

#endif // RandomWalkH
