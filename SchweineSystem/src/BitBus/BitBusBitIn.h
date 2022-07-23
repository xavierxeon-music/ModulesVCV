#ifndef BitBusBitInH
#define BitBusBitInH

#include "BitBusCommon.h"
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

#include <SchweineSystemCommon.h>

class BitBusBitIn : public SchweineSystem::Module, public BitBusCommon
{
public:
   struct Panel;

public:
   BitBusBitIn();
   ~BitBusBitIn();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup() override;
   void onAdd(const AddEvent& e) override;

private:
   SchweineSystem::Input::List inputList;
};

class BitBusBitInWidget : public SchweineSystem::ModuleWidget
{
public:
   BitBusBitInWidget(BitBusBitIn* module);

private:
   void setup();
};

#endif // BitBusBitInH
