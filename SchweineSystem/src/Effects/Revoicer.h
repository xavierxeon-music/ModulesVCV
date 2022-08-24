#ifndef RevoicerH
#define RevoicerH

#include <rack.hpp>
using namespace rack;

#include <Effect/Revoice.h>

#include <SyModule.h>
#include <SyModuleWidget.h>

#include <SyButton.h>
#include <SyDisplayLCD.h>
#include <SyInput.h>
#include <SyOutput.h>

class Revoicer : public Sy::Module
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

   void load(const Sy::Json::Object& rootObject) override;
   void save(Sy::Json::Object& rootObject) override;

private:
   uint8_t numberOfVoices;
   Revoice internal;
   Sy::Button upButton;
   Sy::Button downButton;
   Sy::DisplayLCD::Controller controller;
};

// widget

class RevoicerWidget : public Sy::ModuleWidget
{
public:
   RevoicerWidget(Revoicer* module);

private:
   void setup();
};

#endif // NOT RevoicerH
