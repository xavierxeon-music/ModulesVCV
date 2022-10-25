#include "AppPortal.h"

#include <Tools/File.h>
#include <Tools/Text.h>
#include <Tools/Variable.h>


// midi provider

AppPortal::MidiProvider* AppPortal::MidiProvider::me = nullptr;

void AppPortal::MidiProvider::hello(AppPortal* portal)
{
   if (!me)
      me = new MidiProvider(portal);

   me->portalList.push_back(portal);
}

void AppPortal::MidiProvider::goobye(AppPortal* portal)
{
   if (!me)
      return;

   me->portalList.remove(portal);
   if (me->portalList.empty())
   {
      delete me;
      me = nullptr;
   }
   else if (me->creator == portal)
   {
      me->creator = me->portalList.front();
   }
}

void AppPortal::MidiProvider::proccess(const AppPortal* portal)
{
   if (!me || me->creator != portal)
      return;

   me->update();
}

AppPortal::MidiProvider::MidiProvider(const AppPortal* creator)
   : Svin::Midi::Input("AppPortalVCV", true)
   , Svin::Midi::Output("AppPortalVCV", true)
   , Svin::MasterClock::Client()
   , creator(creator)
{
   // will open automatically
}

AppPortal::MidiProvider::~MidiProvider()
{
   Svin::Midi::Input::close();
   Svin::Midi::Output::close();
}

void AppPortal::MidiProvider::update()
{
   if (hasReset())
   {
      std::vector<unsigned char> songPosMessage(3);
      songPosMessage[0] = ::Midi::Event::SongPositionPointer;
      songPosMessage[1] = 0;
      songPosMessage[2] = 0;
      sendMessage(songPosMessage);
   }
   else
   {
      while (hasMidiClock())
      {
         std::vector<unsigned char> clockMessage(1);
         clockMessage[0] = ::Midi::Event::Clock;
         sendMessage(clockMessage);
      }
   }
}

// main class

AppPortal::AppPortal()
   : Svin::Module()
   , displayController(this, Panel::Pixels_Display)
   , deviceId(0)
   , deviceIdUpButton(this, Panel::DeviceIdUp)
   , deviceIdDownButton(this, Panel::DeviceIdDown)
   , connectedLight(this, Panel::RGB_Connected)
   , fileName()
   , restartButton(this, Panel::Restart)
   , killButton(this, Panel::Kill)
   , modePython(false)
   , modeSwitch(this, Panel::Mode)
   , pitchInput(this, Panel::PitchInput)
   , gateInput(this, Panel::GateInput)
   , gateOutput(this, Panel::GateOutput)
{
   setup();
   registerHubClient("AppPortal");

   MidiProvider::hello(this);

   displayController.onPressed(this, &AppPortal::displayClicked);
   connectedLight.setDefaultColor(Color::Predefined::Green);

   // start will be called by load!
}

AppPortal::~AppPortal()
{
   sendKill();

   MidiProvider::goobye(this);
}

void AppPortal::process(const ProcessArgs& args)
{
   if (restartButton.isTriggered())
      sendStart();

   if (killButton.isTriggered())
      sendKill();

   Variable::Integer<uint8_t> var(deviceId, 0, 15, true);
   if (deviceIdUpButton.isTriggered())
      var.increment();
   if (deviceIdDownButton.isTriggered())
      var.decrement();

   modePython = modeSwitch.isOn();
}

void AppPortal::updateDisplays()
{
   connectedLight.setActive(hubConnected());

   displayController.fill();

   for (uint8_t counter = 0; counter < 6; counter++)
   {
      const uint8_t row = 5 - counter;
      const uint8_t y = 1 + 10 * row;
      const int8_t index = fileName.length() - ((6 - row) * 6);
      if (index >= 0)
      {
         const std::string text = fileName.substr(index, 6);
         displayController.writeText(0, y, text, 10);
      }
      else
      {
         const std::string text = fileName.substr(0, 6 + index);
         displayController.writeText(0, y, Text::pad(text, 6, " "), 10);
         break;
      }
   }

   displayController.writeText(51, 15, std::to_string(deviceId + 1), Svin::DisplayOLED::Font::Huge, Svin::DisplayOLED::Alignment::Center);
}

void AppPortal::sendStart()
{
   if (!File::exists(fileName))
   {
      fileName = std::string();
      return;
   }

   Svin::Json::Object startObject;
   startObject.set("_Application", "AppPortal");
   startObject.set("_Type", "Action");
   startObject.set("action", "launch");
   startObject.set("mode", modePython ? "python" : "max");
   startObject.set("deviceId", deviceId);
   startObject.set("fileName", fileName);

   sendDocumentToHub(1, startObject);
}

void AppPortal::sendKill()
{
   Svin::Json::Object killObject;
   killObject.set("_Application", "AppPortal");
   killObject.set("_Type", "Action");
   killObject.set("action", "kill");
   killObject.set("mode", modePython ? "python" : "max");
   killObject.set("deviceId", deviceId);

   sendDocumentToHub(1, killObject);
}

void AppPortal::displayClicked(const float& x, const float& y)
{
   const std::string filter = modePython ? "Python:py" : "Max:maxpat";
   fileName = getOpenFileName(filter);

   sendStart();
}

void AppPortal::load(const Svin::Json::Object& rootObject)
{
   fileName = rootObject.get("fileName").toString();
   deviceId = rootObject.get("deviceId").toInt();
   modePython = rootObject.get("modePython").toBool();
   sendStart();
}

void AppPortal::save(Svin::Json::Object& rootObject)
{
   rootObject.set("fileName", fileName);
   rootObject.set("deviceId", deviceId);
   rootObject.set("modePython", modePython);
}

// widget

AppPortalWidget::AppPortalWidget(AppPortal* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelAppPortal = Svin::Origin::the()->addModule<AppPortal, AppPortalWidget>("AppPortal");
