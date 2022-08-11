#ifndef RemoteScriptH
#define RemoteScriptH

#include <rack.hpp>
using namespace rack;

#include <SchweineSystemButtonLED.h>
#include <SchweineSystemDisplayOLED.h>
#include <SchweineSystemMidiOutput.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class RemoteScript : public SchweineSystem::Module, private SchweineSystem::MidiOutput
{
public:
   struct Panel;

public:
   RemoteScript();

public:
   void process(const ProcessArgs& args) override;
   void updateDisplays() override;
   void setScriptFileName(const std::string& newFileName);

private:
   void setup();
   void connectToMidiDevice();
   json_t* dataToJson() override;
   void dataFromJson(json_t* rootJson) override;
   void sendToRemote();

private:
   SchweineSystem::ButtonLED connectionButton;
   SchweineSystem::DisplayOLED::Controller displayController;

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
