#include "RemoteScript.h"
#include "RemoteScriptPanel.h"

#include <osdialog.h>

#include <Tools/SevenBit.h>

#include <SchweineSystemJson.h>
#include <SchweineSystemMaster.h>

RemoteScript::RemoteScript()
   : SchweineSystem::Module()
   , SchweineSystem::MidiOutput("Trittbrettfahrer")
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
   , displayController(this, Panel::Pixels_Display)
   , fileName()
{
   setup();

   connectionButton.setDefaultColor(SchweineSystem::Color{0, 255, 0});
   connectToMidiDevice();
}

void RemoteScript::process(const ProcessArgs& args)
{
   if (connectionButton.isTriggered())
      connectToMidiDevice();
}

void RemoteScript::updateDisplays()
{
   displayController.fill();

   if (!fileName.empty())
   {
      displayController.setColor(SchweineSystem::Color{255, 255, 255});
      displayController.writeText(1, 1, "P", SchweineSystem::DisplayOLED::Font::Huge);
      displayController.writeText(20, 10, "Y", SchweineSystem::DisplayOLED::Font::Huge);
   }
}

void RemoteScript::setScriptFileName(const std::string& newFileName)
{
   fileName = newFileName;
   sendToRemote();
}

void RemoteScript::connectToMidiDevice()
{
   if (connected())
   {
      connectionButton.setOn();
      return;
   }

   connectionButton.setOff();
   if (!open())
      return;

   connectionButton.setOn();
   sendToRemote();
}

json_t* RemoteScript::dataToJson()
{
   using namespace SchweineSystem::Json;

   Object rootObject;
   rootObject.set("fileName", Value(fileName));

   return rootObject.toJson();
}

void RemoteScript::dataFromJson(json_t* rootJson)
{
   using namespace SchweineSystem::Json;

   Object rootObject(rootJson);

   fileName = rootObject.get("fileName").toString();

   sendToRemote();
}

void RemoteScript::sendToRemote()
{
   if (!connected())
      return;

   using namespace SchweineSystem::Json;

   Object rootObject;
   rootObject.set("action", Value(std::string("launch")));
   rootObject.set("fileName", Value(fileName));

   sendControllerChange(1, Midi::ControllerMessage::DataInit, 0);

   const Bytes content = rootObject.toBytes();
   const std::string data = SevenBit::encode(content);
   for (const char& byte : data)
      sendControllerChange(1, Midi::ControllerMessage::DataBlock, byte);

   sendControllerChange(1, Midi::ControllerMessage::DataApply, 0);
}

// widget

RemoteScriptWidget::RemoteScriptWidget(RemoteScript* module)
: SchweineSystem::ModuleWidget(module)
{
   setup();

   using OLEDWidget = SchweineSystem::DisplayOLED::Widget;

   OLEDWidget* oled = OLEDWidget::find(module, RemoteScript::Panel::Pixels_Display);
   if (oled)
      oled->onClicked(this, &RemoteScriptWidget::displayClicked);
}

void RemoteScriptWidget::displayClicked(const float& x, const float& y)
{
   (void)x;
   (void)y;

   RemoteScript* myModule = dynamic_cast<RemoteScript*>(getSchweineModule());
   if (!myModule)
      return;

   const char* path = osdialog_file(OSDIALOG_OPEN, nullptr, NULL, osdialog_filters_parse("Python:py"));
   if (path)
      myModule->setScriptFileName(std::string(path));
}

Model* modelRemoteScript = SchweineSystem::Master::the()->addModule<RemoteScript, RemoteScriptWidget>("RemoteScript");
