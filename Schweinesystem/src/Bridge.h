#ifndef BridgeH
#define BridgeH

#include <rack.hpp>
using namespace rack;

using InitFunction = void (*)(int argc, char **argv);
using LoopFunction = void (*)(int value);
using TerminateFunction = void (*)();

class Bridge : public Module
{
public:
   Bridge();
   ~Bridge();

public:
   void process(const ProcessArgs &args) override;

private:
   void *handle;
   InitFunction initFunction;
   LoopFunction loopFunction;
   TerminateFunction terminateFunction;
};

struct BridgeWidget : ModuleWidget
{
   BridgeWidget(Bridge *module);
};

#endif // BridgeH
