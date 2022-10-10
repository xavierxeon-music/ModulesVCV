#ifndef GrooveMaestroConductorH
#define GrooveMaestroConductorH

#include <Blocks/Contour.h>
#include <Blocks/Grooves.h>

class Conductor : public Contour::Poly, public Grooves

{
public:
   Conductor()
      : Abstract::SegmentCrawler()
      , Contour::Poly()
      , Grooves()
   {
   }

public:
   void update(const uint8_t& newDefaultDivision, const uint32_t newSegmentCount) override
   {
      Contour::Poly::update(newDefaultDivision, newSegmentCount);
      Grooves::update(newDefaultDivision, newSegmentCount);
   }
};

#endif // NOT GrooveMaestroConductorH

#ifndef GrooveMaestroH
#define GrooveMaestroH

#include <rack.hpp>
using namespace rack;

#include <SvinMasterClock.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButton.h>
#include <SvinButtonLED.h>
#include <SvinDisplayLCD.h>
#include <SvinDisplayOLED.h>
#include <SvinInput.h>
#include <SvinLaunchpadClient.h>
#include <SvinOutput.h>
#include <SvinSwitch.h>

class GrooveMaestro : public Svin::Module, private Svin::MasterClock::Client
{
public:
   struct Panel;

public:
   GrooveMaestro();

public:
   void process(const ProcessArgs& args) override;
   void loadProject(const std::string& newFileName);

private:
   enum class OperationMode
   {
      Passthrough = 0,
      Remote = 1,
      Play = 2
   };

private:
   inline void setup();

   void updateDisplays() override;
   void updateDisplayPassthrough();
   void updateDisplayRemote();
   void updateDisplayPlay();

   void receivedDocumentFromHub(const ::Midi::Channel& channel, const Svin::Json::Object& object, const uint8_t docIndex) override;

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   std::string fileName;
   Conductor conductor;
   BoolField8 tickTriggers;
   BoolField8 segmentGates;

   // remote
   uint8_t deviceId;
   Svin::DisplayLCD::Controller deviceIdDisplay;
   Svin::Button deviceIdUpButton;
   Svin::Button deviceIdDownButton;
   Svin::LaunchpadClient launchpad;
   Svin::ButtonLED connectionButton;

   // input
   Svin::Input gatePassInput;
   Svin::Switch noOffsetSwitch;

   // output
   Svin::Output gateOutput;
   dsp::PulseGenerator triggerGenerator;

   // mode
   Svin::ButtonLED loopButton;

   OperationMode operationMode;
   Svin::Button operationModeButton;

   // display
   Svin::DisplayOLED::Controller controller;
};

// widget

class GrooveMaestroWidget : public Svin::ModuleWidget
{
public:
   GrooveMaestroWidget(GrooveMaestro* module);

private:
   inline void setup();
};

#ifndef GrooveMaestroHPP
#include "GrooveMaestro.hpp"
#endif // NOT GrooveMaestroHPP

#endif // NOT GrooveMaestroH
