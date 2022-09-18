#ifndef MapperH
#define MapperH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButton.h>
#include <SvinLED.h>
#include <SvinSwitch.h>
#include <SvinInput.h>
#include <SvinOutput.h>

class Mapper : public Svin::Module
{
public:
   struct Panel;

public:
   Mapper();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();
};

// widget

class MapperWidget : public Svin::ModuleWidget
{
public:
   MapperWidget(Mapper* module);

private:
   inline void setup();
};

#ifndef MapperHPP
#include "Mapper.hpp"
#endif // NOT MapperHPP

#endif // NOT MapperH
