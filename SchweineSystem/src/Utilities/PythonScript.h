#ifndef PythonScriptH
#define PythonScriptH

#include <rack.hpp>
using namespace rack;

#include <SvinButton.h>
#include <SvinDisplayOLED.h>
#include <SvinJson.h>
#include <SvinLED.h>
#include <SvinMidi.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>
#include <SvinSvgImage.h>

class PythonScript : public Svin::Module
{
public:
   struct Panel;

public:
   PythonScript();
   ~PythonScript();

public:
   void process(const ProcessArgs& args) override;
   void setScriptFileName(const std::string& newFileName);

private:
   inline void setup();
   void updateDisplays() override;

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

   void sendStart();
   void sendKill();

private:
   Svin::DisplayOLED::Controller displayController;
   Svin::Button restartButton;
   Svin::Button killButton;
   Svin::LED connectedLight;

   // file
   std::string fileName;
};

// widget

class PythonScriptWidget : public Svin::ModuleWidget
{
public:
   PythonScriptWidget(PythonScript* module);

private:
   inline void setup();

};

#ifndef PythonScriptHPP
#include "PythonScript.hpp"
#endif // NOT PythonScriptHPP

#endif // NOT PythonScriptH
