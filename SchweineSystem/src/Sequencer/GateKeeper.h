#ifndef GateKeeperH
#define GateKeeperH

#include <rack.hpp>
using namespace rack;

#include <SvinMasterClock.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <Blocks/Grooves.h>

#include <SvinButton.h>
#include <SvinButtonLED.h>
#include <SvinDisplayOLED.h>
#include <SvinInput.h>
#include <SvinOutput.h>
#include <SvinSwitch.h>

class GateKeeper : public Svin::Module, public Svin::MasterClock::Client
{
public:
   struct Panel;

public:
   GateKeeper();

public:
   void process(const ProcessArgs& args) override;
   void loadProject(const std::string& newFileName);

private:
   enum class OperationMode
   {
      Passthrough = 0,
      Internal = 1
   };

private:
   inline void setup();

   void updateDisplays() override;
   void updatePassthrough();
   void updateInternal();

   void receivedDocumentFromHub(const ::Midi::Channel& channel, const Svin::Json::Object& object, const uint8_t docIndex) override;

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   std::string fileName;
   Grooves grooves;
   BoolField8 tickTriggers;
   BoolField8 segmentGates;

   // bank
   uint8_t bankIndex;
   Svin::Button bankUpButton;
   Svin::Button bankDownButton;

   // input
   Svin::Input passInput;
   Svin::Switch noOffsetSwitch;

   // output
   Svin::Output output;
   dsp::PulseGenerator triggerGenerator;

   // mode
   Svin::ButtonLED loopButton;

   OperationMode operationMode;
   Svin::Button operationModeButton;

   // display
   Svin::DisplayOLED::Controller controller;
   std::string lastNamedSegement;
};

// widget

class GateKeeperWidget : public Svin::ModuleWidget
{
public:
   GateKeeperWidget(GateKeeper* module);

private:
   inline void setup();
};

#ifndef GateKeeperHPP
#include "GateKeeper.hpp"
#endif // NOT GateKeeperHPP

#endif // NOT GateKeeperH
