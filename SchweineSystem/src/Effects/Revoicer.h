#ifndef RevoicerH
#define RevoicerH

#include <rack.hpp>
using namespace rack;

#include <Effect/Revoice.h>

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButton.h>
#include <SvinDisplayLCD.h>
#include <SvinInput.h>
#include <SvinOutput.h>

class Revoicer : public Svin::Module
{
public:
   struct Panel;

public:
   Revoicer();

public:
   void process(const ProcessArgs& args) override;
   void onSampleRateChange(const SampleRateChangeEvent& e) override;

private:
   void setup();

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   uint8_t numberOfVoices;
   Revoice internal;
   Svin::Button upButton;
   Svin::Button downButton;
   Svin::DisplayLCD::Controller controller;
};

// widget

class RevoicerWidget : public Svin::ModuleWidget
{
public:
   RevoicerWidget(Revoicer* module);

private:
   void setup();
};

#endif // NOT RevoicerH
