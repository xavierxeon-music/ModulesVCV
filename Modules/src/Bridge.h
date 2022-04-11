#ifndef BridgeH
#define BridgeH

#include <rack.hpp>
using namespace rack;

#include "../../LibBridge/Interface.h"

class Bridge : public Module
{
public:
   Bridge();
   ~Bridge();

public:
   void process(const ProcessArgs& args) override;

private:
   void* libHandle;
   CreateFunction createFunction;
   InitFunction initFunction;
   ProcessFunction processFunction;
   TerminateFunction terminateFunction;
};

struct BridgeWidget : ModuleWidget
{
   BridgeWidget(Bridge* module);
};

#endif // BridgeH
