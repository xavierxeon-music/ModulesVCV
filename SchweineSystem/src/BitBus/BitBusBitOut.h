#ifndef BitBusBitOutH
#define BitBusBitOutH

#include "BitBusCommon.h"
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

#include <SchweineSystemCommon.h>

class BitBusBitOut : public SchweineSystem::Module, public BitBusCommon
{
public:
   struct Panel;

public:
   BitBusBitOut();
   ~BitBusBitOut();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup() override;
   void onAdd(const AddEvent& e) override;

private:
   SchweineSystem::Output::List outputList;
};

// widget

class BitBusBitOutWidget : public SchweineSystem::ModuleWidget
{
public:
   BitBusBitOutWidget(BitBusBitOut* module);

private:
   void setup();
};

#endif // BitBusBitOutH
