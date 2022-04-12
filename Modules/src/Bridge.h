#ifndef BridgeH
#define BridgeH

#include <rack.hpp>
using namespace rack;

class Bridge : public Module
{
public:
   Bridge();
   ~Bridge();

public:
   void process(const ProcessArgs& args) override;
};

struct BridgeWidget : ModuleWidget
{
   BridgeWidget(Bridge* module);
};

#endif // BridgeH
