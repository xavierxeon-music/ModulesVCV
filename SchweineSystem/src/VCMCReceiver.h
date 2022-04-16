#ifndef VCMCReceiverH
#define VCMCReceiverH

#include <rack.hpp>
using namespace rack;

class VCMCReceiver : public Module
{
public:
   struct Panel;

public:
   VCMCReceiver();
   ~VCMCReceiver();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
};

struct VCMCReceiverWidget : ModuleWidget
{
   VCMCReceiverWidget(VCMCReceiver* module);
};

#endif // NOT VCMCReceiverH
