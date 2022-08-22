#ifndef RemoteScriptH
#define RemoteScriptH

#include "SyJson.h"
#include <rack.hpp>
using namespace rack;

#include <SyButton.h>
#include <SyButtonLED.h>
#include <SyDisplayOLED.h>
#include <SyJson.h>
#include <SyMidiOutput.h>
#include <SyModule.h>
#include <SyModuleWidget.h>

class RemoteScript : public Sy::Module, private Sy::MidiOutput
{
public:
   struct Panel;

public:
   RemoteScript();
   ~RemoteScript();

public:
   void process(const ProcessArgs& args) override;
   void updateDisplays() override;
   void setScriptFileName(const std::string& newFileName);

private:
   void setup();
   void connectToMidiDevice();

   void load(const Sy::Json::Object& rootObject) override;
   void save(Sy::Json::Object& rootObject) override;

   void sendStart();
   void sendKill();
   void sendToRemote(const Sy::Json::Object& object);

private:
   Sy::DisplayOLED::Controller displayController;
   Sy::Button restartButton;
   Sy::Button killButton;
   Sy::ButtonLED connectionButton;

   // file
   std::string fileName;
};

// widget

class RemoteScriptWidget : public Sy::ModuleWidget
{
public:
   RemoteScriptWidget(RemoteScript* module);

private:
   void setup();
   void displayClicked(const float& x, const float& y);
};

#endif // NOT RemoteScriptH
