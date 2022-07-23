#ifndef HalfVoltH
#define HalfVoltH

#include <rack.hpp>
using namespace rack;

#include <SchweineSystemCommon.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class HalfVolt : public SchweineSystem::Module
{
public:
   struct Panel;

public:
   HalfVolt();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup() override;

private:
   SchweineSystem::Input::List inputList;
   SchweineSystem::Output::List outputList;
};

class HalfVoltWidget : public SchweineSystem::ModuleWidget
{
public:
   HalfVoltWidget(HalfVolt* module);

private:
   void setup();
};

#endif // NOT HalfVoltH
