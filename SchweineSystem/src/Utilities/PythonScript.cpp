#include "PythonScript.h"

#include <Tools/File.h>
#include <Tools/Text.h>

PythonScript::PythonScript()
   : Svin::Module()
   , displayController(this, Panel::Pixels_Display)
   , restartButton(this, Panel::Restart)
   , killButton(this, Panel::Kill)
   , connectedLight(this, Panel::RGB_Connected)
   , fileName()
{
   setup();
   registerHubClient("PythonScript");

   displayController.onClickedOpenFileFunction(this, &PythonScript::setScriptFileName, "Python:py");
   connectedLight.setDefaultColor(Color(0, 255, 0));

   if (hubConnected())
      sendStart();
}

PythonScript::~PythonScript()
{
   sendKill();
}

void PythonScript::process(const ProcessArgs& args)
{
   if (restartButton.isTriggered())
      sendStart();

   if (killButton.isTriggered())
      sendKill();

   connectedLight.setActive(hubConnected());
}

void PythonScript::setScriptFileName(const std::string& newFileName)
{
   fileName = newFileName;
   sendStart();
}

void PythonScript::updateDisplays()
{
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
}

void PythonScript::load(const Svin::Json::Object& rootObject)
{
   fileName = rootObject.get("fileName").toString();

   sendStart();
}

void PythonScript::save(Svin::Json::Object& rootObject)
{
   rootObject.set("fileName", fileName);
}

void PythonScript::sendStart()
{
   if (!File::exists(fileName))
   {
      fileName = std::string();
      return;
   }

   using namespace Svin::Json;

   Object startObject;
   startObject.set("_Application", "PythonScript");
   startObject.set("_Type", "Action");
   startObject.set("action", "launch");
   startObject.set("fileName", fileName);

   sendDocumentToHub(1, startObject);
}

void PythonScript::sendKill()
{
   using namespace Svin::Json;

   Object killObject;
   killObject.set("_Application", "PythonScript");
   killObject.set("_Type", "Action");
   killObject.set("action", "kill");

   sendDocumentToHub(1, killObject);
}

// widget

PythonScriptWidget::PythonScriptWidget(PythonScript* module)
   : Svin::ModuleWidget(module)
{
   setup();
}


// create module
Model* modelPythonScript = Svin::Origin::the()->addModule<PythonScript, PythonScriptWidget>("PythonScript");
