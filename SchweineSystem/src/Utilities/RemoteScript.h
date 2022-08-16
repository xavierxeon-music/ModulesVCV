#ifndef RemoteScriptH
#define RemoteScriptH

#include "SchweineSystemJson.h"
#include <rack.hpp>
using namespace rack;

#include <SchweineSystemButton.h>
#include <SchweineSystemButtonLED.h>
#include <SchweineSystemDisplayOLED.h>
#include <SchweineSystemJson.h>
#include <SchweineSystemMidiOutput.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class RemoteScript : public SchweineSystem::Module, private SchweineSystem::MidiOutput
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

   void load(const SchweineSystem::Json::Object& rootObject) override;
   void save(SchweineSystem::Json::Object& rootObject) override;

   void sendStart();
   void sendKill();
   void sendToRemote(const SchweineSystem::Json::Object& object);

private:
   SchweineSystem::DisplayOLED::Controller displayController;
   SchweineSystem::Button restartButton;
   SchweineSystem::Button killButton;
   SchweineSystem::ButtonLED connectionButton;

   // file
   std::string fileName;
};

// widget

class RemoteScriptWidget : public SchweineSystem::ModuleWidget
{
public:
   RemoteScriptWidget(RemoteScript* module);

private:
   void setup();
   void displayClicked(const float& x, const float& y);
};

#endif // NOT RemoteScriptH
