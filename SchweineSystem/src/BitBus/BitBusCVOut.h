#ifndef BitBusCVOutH
#define BitBusCVOutH

#include "BitBusCommon.h"
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

#include <Tools/Range.h>


class BitBusCVOut : public SchweineSystem::Module, public BitBusCommon
{
public:
   struct Panel;

public:
   BitBusCVOut();
   ~BitBusCVOut();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup() override;
   void onAdd(const AddEvent& e) override;

private:
   Range::Mapper outputMapper;
};

class BitBusCVOutWidget : public SchweineSystem::ModuleWidget
{
public:
   BitBusCVOutWidget(BitBusCVOut* module);

private:
   void setup();
};

#endif // BitBusCVOutH
