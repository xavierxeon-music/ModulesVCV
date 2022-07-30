#ifndef BitBusCVInH
#define BitBusCVInH

#include "BitBusCommon.h"
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

#include <Tools/Range.h>


class BitBusCVIn : public SchweineSystem::Module, public BitBusCommon
{
public:
   struct Panel;

public:
   BitBusCVIn();
   ~BitBusCVIn();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup() override;
   void onAdd(const AddEvent& e) override;

private:
   Range::Mapper inputMapper;
};

// widget

class BitBusCVInWidget : public SchweineSystem::ModuleWidget
{
public:
   BitBusCVInWidget(BitBusCVIn* module);

private:
   void setup();
};

#endif // BitBusCVInH
