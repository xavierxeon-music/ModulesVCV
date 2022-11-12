#ifndef SpacerH
#define SpacerH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinInput.h>
#include <SvinOutput.h>

#include <Effect/DelayLine.h>
#include <Effect/StateVariableFilter.h>

class Spacer : public Svin::Module
{
public:
   struct Panel;

public:
   Spacer();

public:
   void process(const ProcessArgs& args) override;

private:
   struct Line
   {
      DelayLineOne delay;
      StateVariableFilter filter;
   };

private:
   inline void setup();

private:
   Svin::Input input;
   Svin::Output leftOutput;
   Svin::Output rightOutput;

   static constexpr uint8_t lineCount = 64;
   Line lines[lineCount];
};

// widget

class SpacerWidget : public Svin::ModuleWidget
{
public:
   SpacerWidget(Spacer* module);

private:
   inline void setup();
};

#ifndef SpacerHPP
#include "Spacer.hpp"
#endif // NOT SpacerHPP

#endif // NOT SpacerH
