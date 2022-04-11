#ifndef BridgeH
#define BridgeH

#include <rack.hpp>
using namespace rack;

using InitFunction = void (*)(int argc, char** argv);
using LoopFunction = void (*)(int value);
using TerminateFunction = void (*)();

class Bridge : public Module
{
public:
   enum InputId
   {
      INPUT_1,
      INPUT_2,
      INPUT_3,
      INPUT_4,
      INPUT_5,
      INPUT_6,
      INPUT_7,
      INPUT_8,
      INPUTS_LEN
   };

   enum OutputId
   {
      OUTPUT_1,
      OUTPUT_2,
      OUTPUT_3,
      OUTPUT_4,
      OUTPUT_5,
      OUTPUT_6,
      OUTPUT_7,
      OUTPUT_8,
      OUTPUTS_LEN
   };

public:
   Bridge();
   ~Bridge();

public:
   void process(const ProcessArgs& args) override;

private:
   void* handle;
   InitFunction initFunction;
   LoopFunction loopFunction;
   TerminateFunction terminateFunction;
};

struct BridgeWidget : ModuleWidget
{
   BridgeWidget(Bridge* module);
};

#endif // BridgeH
