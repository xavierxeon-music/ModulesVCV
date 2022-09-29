#ifndef MaestroH
#define MaestroH

#include <rack.hpp>
using namespace rack;

#include <Blocks/TrackerProject.h>
#include <Tools/Range.h>

#include <SvinMasterClock.h>
#include <SvinMidi.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButton.h>
#include <SvinButtonLED.h>
#include <SvinDisplayOLED.h>
#include <SvinInput.h>
#include <SvinOutput.h>

class Maestro : public Svin::Module, public Svin::MasterClock::Client
{
public:
   struct Panel;

public:
   Maestro();

public:
   void process(const ProcessArgs& args) override;
   void loadProject(const std::string& newFileName);

private:
   enum class OperationMode
   {
      Passthrough = 0,
      Remote = 1,
      InternalOverview = 2,
      InternalCurrent = 3
   };

private:
   inline void setup();

   void processPassthrough();
   void proccessRemote();
   void processInternal();

   void updateDisplays() override;
   void updatePassthrough();
   void updateRemote();
   void updateInternalOverview();
   void updateInternalCurrent();

   void receivedDocumentFromHub(const ::Midi::Channel& channel, const Svin::Json::Object& object, const uint8_t docIndex) override;

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   std::string fileName;
   Tracker::Project project;
   std::vector<std::string> eventNameList;

   // bank
   uint8_t bankIndex;
   Svin::Button bankUpButton;
   Svin::Button bankDownButton;

   // midi
   std::string buffer;

   // input
   Svin::Input input;
   Range::Mapper voltageToValue;

   // upload
   Svin::Input uploadInput;

   // outpt
   Range::Mapper valueToVoltage;
   Svin::Output output;

   // mode
   Svin::ButtonLED loopButton;

   OperationMode operationMode;
   Svin::Button operationModeButton;
   uint8_t remoteValues[Tracker::Project::laneCount];

   // display
   Svin::DisplayOLED::Controller controller;
   std::string lastNamedSegement;
};

// widget

class MaestroWidget : public Svin::ModuleWidget
{
public:
   MaestroWidget(Maestro* module);

private:
   inline void setup();
};

#ifndef MaestroHPP
#include "Maestro.hpp"
#endif // NOT MaestroHPP

#endif // NOT MaestroH
