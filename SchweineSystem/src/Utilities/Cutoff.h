#ifndef CutoffH
#define CutoffH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinSlider.h>
#include <SvinInput.h>
#include <SvinOutput.h>

class Cutoff : public Svin::Module
{
public:
   struct Panel;

public:
   Cutoff();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   Svin::Slider overSlider;
   Svin::Input input;
   Svin::Output output;
};

// widget

class CutoffWidget : public Svin::ModuleWidget
{
public:
   CutoffWidget(Cutoff* module);

private:
   inline void setup();
};

#ifndef CutoffHPP
#include "Cutoff.hpp"
#endif // NOT CutoffHPP

#endif // NOT CutoffH
