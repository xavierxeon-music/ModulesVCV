#ifndef MaestroH
#define MaestroH

#include <Blocks/Contours.h>
#include <Blocks/Grooves.h>
#include <Blocks/Stages.h>

namespace Conductor
{
   class Core : public Contours, public Grooves, public Stages

   {
   public:
      Core()
         : Abstract::SegmentCrawler()
         , Contours()
         , Grooves()
         , Stages()
      {
      }

   public:
      void update(const Tempo::Tick& newDefaultDivision, const uint32_t newSegmentCount) override
      {
         Contours::update(newDefaultDivision, newSegmentCount);
         Grooves::update(newDefaultDivision, newSegmentCount);
         Stages::update(newDefaultDivision, newSegmentCount);
      }

      void setSegmentLength(const uint32_t segmentIndex, const Tempo::Tick& length) override
      {
         Contours::setSegmentLength(segmentIndex, length);
         Grooves::setSegmentLength(segmentIndex, length);
         Stages::setSegmentLength(segmentIndex, length);
      }

      void updateProxies() override
      {
         Contours::updateProxies();
         Grooves::updateProxies();
         Stages::updateProxies();
      }
   };
} // namespace Conductor

enum class OperationMode
{
   Passthrough = 0,
   Remote = 1,
   Play = 2
};

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

#include <Tools/Prompt.h>

class Maestro : public Svin::Module, private Svin::MasterClock::Client
{
public:
   struct Panel;

public:
   Maestro();

public:
   void process(const ProcessArgs& args) override;
   void loadProject(const std::string& newFileName);

private:
   class Display
   {
   public:
      enum class Mode
      {
         Overview,
         Groove,
         Melody,
         Contour
      };

   public:
      Display(Maestro* gm);

   public:
      void process();
      void update();

   public:
      Mode mode;

   private:
      using ModeMap = std::map<Mode, Svin::ButtonLED*>;

   private:
      void headerPassthrough();
      void headerRemote();
      void headerPlay();

      void displayOverview();
      void displayGroove();
      void displayMelody();
      void displayContours();

   private:
      Maestro* gm;
      Svin::DisplayOLED::Controller controller;
      Svin::ButtonLED modeButtonOverivew;
      Svin::ButtonLED modeButtonGroove;
      Svin::ButtonLED modeButtonMelody;
      Svin::ButtonLED modeButtonContour;
      ModeMap modeMap;
   };

   class Launchpad
   {
   public:
      enum class WantConnection
      {
         Maybe,
         Yes,
         No
      };

   public:
      Launchpad(Maestro* gm);

   public:
      void process();
      void updateButton();
      void read();
      void readStopped();
      void updateGrid();
      void updateHeader();

   private:
      void toggleConnection();

   public:
      Svin::LaunchpadClient client;
      WantConnection wantConnection;
      Prompt connectionPrompt;

   private:
      Maestro* gm;
      uint8_t offset;
      Svin::ButtonLED connectionButton;
   };

   struct UnitGuard
   {
      struct Lane
      {
         Stages::Unit unit;
         Midi::Event event = Midi::Event::NoteOff;
      };
      Lane lanes[Stages::laneCount];
      uint8_t tick = 255;
   };

   using OperationModeMap = std::map<OperationMode, Svin::ButtonLED*>;

private:
   inline void setup();

   void updateDisplays() override;

   void uploadToHub();
   void receivedDocumentFromHub(const ::Midi::Channel& channel, const Svin::Json::Object& object, const uint8_t docIndex) override;

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   std::string fileName;
   long timeStamp;
   Conductor::Core conductor;
   Grooves localGrooves;
   Stages localStages;
   std::vector<float> voltages;
   BoolField8 tickTriggers;
   BoolField8 segmentGates;
   UnitGuard unitGuard;

   // control
   Display display;
   Launchpad launchpad;

   // input
   Svin::Input uploadInput;
   Svin::Input contoutPassInput;
   Svin::Input gatePassInput;
   Svin::Switch noOffsetSwitch;

   // output
   Svin::Output contourOutput;
   Svin::Output gateOutput;
   Range::Mapper valueToVoltage;
   dsp::PulseGenerator triggerGenerator;
   Svin::Midi::Bus busMessage;

   // mode
   Svin::ButtonLED loopButton;

   OperationMode operationMode;
   Svin::ButtonLED modeButtonPass;
   Svin::ButtonLED modeButtonRemote;
   Svin::ButtonLED modeButtonReplay;
   OperationModeMap operationModeMap;

   // other
   Range::Mapper voltageToValue;
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
