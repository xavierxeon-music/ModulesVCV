#include "RemoteScript.h"
#include "RemoteScriptPanel.h"

#include <osdialog.h>

#include <Tools/SevenBit.h>

#include <SchweineSystemMaster.h>

RemoteScript::RemoteScript()
   : SchweineSystem::Module()
   , SchweineSystem::MidiOutput("Trittbrettfahrer")
   , displayController(this, Panel::Pixels_Display)
   , restartButton(this, Panel::Restart)
   , killButton(this, Panel::Kill)
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
   , fileName()
{
   setup();

   connectionButton.setDefaultColor(SchweineSystem::Color{0, 255, 0});
   connectToMidiDevice(); // will try to send start
}

RemoteScript::~RemoteScript()
{
   sendKill();
}

void RemoteScript::process(const ProcessArgs& args)
{
   if (restartButton.isTriggered())
      sendStart();
   if (killButton.isTriggered())
      sendKill();

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
   sendStart();
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
   sendStart();
}

void RemoteScript::load(const SchweineSystem::Json::Object& rootObject)
{
   fileName = rootObject.get("fileName").toString();

   sendStart();
}

void RemoteScript::save(SchweineSystem::Json::Object& rootObject)
{
   rootObject.set("fileName", fileName);
}

void RemoteScript::sendStart()
{
   using namespace SchweineSystem::Json;

   Object startObject;
   startObject.set("action", Value(std::string("launch")));
   startObject.set("fileName", Value(fileName));

   sendToRemote(startObject);
}

void RemoteScript::sendKill()
{
   using namespace SchweineSystem::Json;

   Object killObject;
   killObject.set("action", Value(std::string("kill")));

   sendToRemote(killObject);
}

void RemoteScript::sendToRemote(const SchweineSystem::Json::Object& object)
{
   if (!connected())
      return;

   sendControllerChange(1, Midi::ControllerMessage::DataInit, 0);

   const Bytes content = object.toBytes();
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
