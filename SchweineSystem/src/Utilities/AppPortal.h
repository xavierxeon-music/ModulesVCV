#ifndef AppPortalH
#define AppPortalH

#include <rack.hpp>
using namespace rack;

#include <SvinMasterClock.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButton.h>
#include <SvinDisplayOLED.h>
#include <SvinInput.h>
#include <SvinLED.h>
#include <SvinOutput.h>
#include <SvinSwitch.h>

class AppPortal : public Svin::Module
{
public:
   struct Panel;

public:
   AppPortal();
   ~AppPortal();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();
   void updateDisplays() override;

   void sendStart();
   void sendKill();

   void displayClicked(const float& x, const float& y);

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   class MidiProvider : public Svin::Midi::Input, public Svin::Midi::Output, public Svin::MasterClock::Client
   {
   public:
      static void hello(AppPortal* portal);
      static void goobye(AppPortal* portal);
      static void proccess(const AppPortal* portal);

   private:
      MidiProvider(const AppPortal* creator);
      ~MidiProvider();

   private:
      void update();

   private:
      static MidiProvider* me;
      std::list<AppPortal*> portalList;
      const AppPortal* creator;
   };

private:
   Svin::DisplayOLED::Controller displayController;
   // id
   uint8_t deviceId;
   Svin::Button deviceIdUpButton;
   Svin::Button deviceIdDownButton;
   Svin::LED connectedLight;
   // file
   std::string fileName;
   Svin::Button restartButton;
   Svin::Button killButton;
   // mode
   bool modePython;
   Svin::Switch modeSwitch;
   // io
   Svin::Input pitchInput;
   Svin::Input gateInput;
   Svin::Output gateOutput;
};

// widget

class AppPortalWidget : public Svin::ModuleWidget
{
public:
   AppPortalWidget(AppPortal* module);

private:
   inline void setup();
};

#ifndef AppPortalHPP
#include "AppPortal.hpp"
#endif // NOT AppPortalHPP

#endif // NOT AppPortalH
