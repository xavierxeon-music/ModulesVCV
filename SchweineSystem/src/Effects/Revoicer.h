#ifndef RevoicerH
#define RevoicerH

#include <rack.hpp>
using namespace rack;

#include <Effect/Revoice.h>

#include <SchweineSystemButton.h>
#include <SchweineSystemDisplayLCD.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class Revoicer : public SchweineSystem::Module
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
   json_t* dataToJson() override;
   void dataFromJson(json_t* rootJson) override;

private:
   uint8_t numberOfVocices;
   Revoice internal;
   SchweineSystem::Button upButton;
   SchweineSystem::Button downButton;
   SchweineSystem::DisplayLCD::Controller controller;
};

// widget

class RevoicerWidget : public SchweineSystem::ModuleWidget
{
public:
   RevoicerWidget(Revoicer* module);

private:
   void setup();
};

#endif // NOT RevoicerH
