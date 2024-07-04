#ifndef ScaleShowH
#define ScaleShowH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinLED.h>

class ScaleShow : public Svin::Module
{
public:
   struct Panel;

public:
   ScaleShow();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();

private:
   Svin::LED::List noteList;
};

// widget

class ScaleShowWidget : public Svin::ModuleWidget
{
public:
   ScaleShowWidget(ScaleShow* module);

private:
   inline void setup();
};

#ifndef ScaleShowHPP
#include "ScaleShow.hpp"
#endif // NOT ScaleShowHPP

#endif // NOT ScaleShowH
