#ifndef TrackerWorkerH
#define TrackerWorkerH

#include <rack.hpp>
using namespace rack;

#include <Tools/Range.h>
#include <Tracker/TrackerProject.h>

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButton.h>
#include <SvinDisplayOLED.h>
#include <SvinInput.h>
#include <SvinOutput.h>

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
   enum class DisplayMode
   {
      Division,
      Length,
      StageCount,
      StageIndex
   };

   enum class OperationMode
   {
      Passthrough,
      Remote,
      Internal
   };

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

   void updateDisplayPassthrough();
   void updateDisplayRemote();
   void updateDisplayInternal();

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   std::string fileName;
   Tracker::Project project;

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

   // display
   DisplayMode displayMode;
   Svin::Button displayButton;
   Svin::DisplayOLED::Controller displayController;

   // mode
   OperationMode operationMode;
   Svin::Button operationModeButton;
   uint8_t remoteValues[32];
};

// widget

class TrackerWorkerWidget : public Svin::ModuleWidget
{
public:
   TrackerWorkerWidget(TrackerWorker* module);

private:
   void setup();
   void displayClicked(const float& x, const float& y);
};

#endif // NOT TrackerWorkerH
