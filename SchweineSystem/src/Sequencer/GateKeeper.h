#ifndef GateKeeperH
#define GateKeeperH

#include <rack.hpp>
using namespace rack;

#include <SvinMasterClock.h>
#include <SvinMidi.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <Blocks/Grooves.h>

#include <SvinButton.h>
#include <SvinButtonLED.h>
#include <SvinDisplayOLED.h>
#include <SvinSwitch.h>
#include <SvinInput.h>
#include <SvinOutput.h>

class GateKeeper : public Svin::Module, public Svin::MasterClock::Client, public Svin::Midi::Output
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
   void connectToMidiDevice();

   void updateDisplays() override;
   void updatePassthrough();
   void updateInternal();

   void receivedDocumentFromHub(const ::Midi::Channel& channel, const Svin::Json::Object& object, const uint8_t docIndex) override;

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   std::string fileName;
   Grooves grooves;
   BoolField8 spikes;
   BoolField8 state;

   // bank
   uint8_t bankIndex;
   Svin::Button bankUpButton;
   Svin::Button bankDownButton;

   // input
   Svin::Input passInput;
   Svin::Switch noOffsetSwitch;

   // output
   Svin::ButtonLED connectionButton;
   Svin::Output::List gateOutputList;
   dsp::PulseGenerator triggerGenerator;
   BoolField8 pulseActive;

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
