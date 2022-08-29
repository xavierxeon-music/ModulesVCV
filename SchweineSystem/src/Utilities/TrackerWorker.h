#ifndef TrackerWorkerH
#define TrackerWorkerH

#include <rack.hpp>
using namespace rack;

#include <Blocks/TrackerProject.h>
#include <Tools/Range.h>

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButton.h>
#include <SvinButtonLED.h>
#include <SvinInput.h>
#include <SvinOutput.h>

#include "TrackerWorker/Display.h"
//#include "TrackerWorker/Midi.h"

class TrackerWorker : public Svin::Module
{
public:
   struct Panel;

public:
   TrackerWorker();

public:
   void process(const ProcessArgs& args) override;
   void loadProject(const std::string& newFileName);

private:
   enum class OperationMode
   {
      Passthrough,
      Remote,
      InternalOverview,
      InternalCurrent
   };

   friend class Display;

   enum class MidiReceive
   {
      None,
      Remember,
      Data
   };

private:
   void setup();

   void processPassthrough();
   void proccessRemote();
   void processInternal();

   void updateDisplays() override;

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   std::string fileName;
   Tracker::Project project;
   std::vector<std::string> eventNameList;

   // midi
   MidiReceive receive;
   std::string buffer;

   // clock
   Svin::Input clockInput;
   Svin::Input resetInput;
   Tempo tempo;

   // input
   Svin::Input::List inputList;
   Range::Mapper voltageToValue;

   // upload
   Svin::Input uploadInput;

   // outpt
   Range::Mapper valueToVoltage;
   Svin::Output::List outputList;

   // mode
   Svin::ButtonLED loopButton;

   OperationMode operationMode;
   Svin::Button operationModeButton;
   uint8_t remoteValues[32];

   Display display;
};

// widget

class TrackerWorkerWidget : public Svin::ModuleWidget
{
public:
   TrackerWorkerWidget(TrackerWorker* module);

private:
   void setup();
};

#endif // NOT TrackerWorkerH
