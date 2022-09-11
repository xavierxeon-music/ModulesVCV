#ifndef RemoteScriptH
#define RemoteScriptH

#include <rack.hpp>
using namespace rack;

#include <SvinButton.h>
#include <SvinButtonLED.h>
#include <SvinDisplayOLED.h>
#include <SvinJson.h>
#include <SvinMidi.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>
#include <SvinSvgImage.h>

class RemoteScript : public Svin::Module
{
public:
   struct Panel;

public:
   RemoteScript();
   ~RemoteScript();

public:
   void process(const ProcessArgs& args) override;
   void setScriptFileName(const std::string& newFileName);
   bool scriptExists() const;

private:
   void setup();
   void updateDisplays() override;

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

   void sendStart();
   void sendKill();

   void displayClicked(const float& x, const float& y);

private:
   Svin::DisplayOLED::Controller displayController;
   Svin::Button restartButton;
   Svin::Button killButton;

   // file
   std::string fileName;
};

// widget

class RemoteScriptWidget : public Svin::ModuleWidget
{
public:
   RemoteScriptWidget(RemoteScript* module);

private:
   void setup();
   void preDraw() override;

private:
   Svin::SvgImage* logoWidget;
};

#endif // NOT RemoteScriptH
