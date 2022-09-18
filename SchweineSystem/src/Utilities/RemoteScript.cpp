#include "RemoteScript.h"

#include <Tools/File.h>
#include <Tools/SevenBit.h>

#include <SvinOrigin.h>

RemoteScript::RemoteScript()
   : Svin::Module()
   , displayController(this, Panel::Pixels_Display)
   , restartButton(this, Panel::Restart)
   , killButton(this, Panel::Kill)
   , connectedLight(this, Panel::RGB_Connected)
   , fileName()
{
   setup();
   registerHubClient("RemoteScript");

   displayController.fill();
   displayController.onClickedOpenFileFunction(this, &RemoteScript::setScriptFileName, "Python:py");

   if (hubConnected())
      sendStart();
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

   connectedLight.setActive(hubConnected());
}

void RemoteScript::setScriptFileName(const std::string& newFileName)
{
   fileName = newFileName;
   sendStart();
}

bool RemoteScript::scriptExists() const
{
   return !fileName.empty();
}

void RemoteScript::updateDisplays()
{
   //displayController.fill();
}

void RemoteScript::load(const Svin::Json::Object& rootObject)
{
   fileName = rootObject.get("fileName").toString();

   sendStart();
}

void RemoteScript::save(Svin::Json::Object& rootObject)
{
   rootObject.set("fileName", fileName);
}

void RemoteScript::sendStart()
{
   if (!File::exists(fileName))
   {
      fileName = std::string();
      return;
   }

   using namespace Svin::Json;

   Object startObject;
   startObject.set("_Application", "RemoteScript");
   startObject.set("_Type", "Action");
   startObject.set("action", "launch");
   startObject.set("fileName", fileName);

   sendDocumentToHub(1, startObject);
}

void RemoteScript::sendKill()
{
   using namespace Svin::Json;

   Object killObject;
   killObject.set("_Application", "RemoteScript");
   killObject.set("_Type", "Action");
   killObject.set("action", "kill");

   sendDocumentToHub(1, killObject);
}

void RemoteScript::displayClicked(const float& x, const float& y)
{
   (void)x;
   (void)y;

   setScriptFileName(getOpenFileName("Python:py"));
}

// widget

RemoteScriptWidget::RemoteScriptWidget(RemoteScript* module)
   : Svin::ModuleWidget(module)
{
   setup();

   std::string logoPath = asset::plugin(Svin::Origin::the()->instance(), "res/Utilities/Python.svg");

   const float offset = 5.0;
   logoWidget = new Svin::SvgImage(rack::math::Vec(9.00 + offset, 62.34 + offset), module, logoPath, 0.3);
   addChild(logoWidget);

   logoWidget->visible = false;
}

void RemoteScriptWidget::preDraw()
{
   RemoteScript* myModule = dynamic_cast<RemoteScript*>(getSchweineModule());
   if (!myModule)
      return;

   logoWidget->visible = myModule->scriptExists();
}
// creete module
Model* modelRemoteScript = Svin::Origin::the()->addModule<RemoteScript, RemoteScriptWidget>("RemoteScript");

