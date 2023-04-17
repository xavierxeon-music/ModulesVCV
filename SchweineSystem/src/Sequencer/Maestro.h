#ifndef MaestroConductorH
#define MaestroConductorH

#include <Blocks/Contour.h>
#include <Blocks/Grooves.h>
#include <Blocks/Melodies.h>.h>

class Conductor : public Contour::Poly, public Grooves, public Melodies

{
public:
   Conductor()
      : Abstract::SegmentCrawler()
      , Contour::Poly()
      , Grooves()
      , Melodies()
   {
   }

public:
   void update(const Tempo::Tick& newDefaultDivision, const uint32_t newSegmentCount) override
   {
      Contour::Poly::update(newDefaultDivision, newSegmentCount);
      Grooves::update(newDefaultDivision, newSegmentCount);
      Melodies::update(newDefaultDivision, newSegmentCount);
   }

   void setSegmentLength(const uint32_t segmentIndex, const Tempo::Tick& length) override
   {
      Contour::Poly::setSegmentLength(segmentIndex, length);
      Grooves::setSegmentLength(segmentIndex, length);
      Melodies::setSegmentLength(segmentIndex, length);
   }
};

enum class OperationMode
{
   Passthrough = 0,
   Remote = 1,
   Play = 2
};

#endif // NOT MaestroConductorH

#ifndef MaestroH
#define MaestroH

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
      Display(Maestro* gm);

   public:
      void update();

   private:
      void updatePassthrough();
      void updateRemote();
      void updatePlay();

      void displayStoped();
      bool displayGroove();
      void displayContours();

   private:
      Maestro* gm;
      Svin::DisplayLCD::Controller deviceIdDisplay;
      Svin::DisplayOLED::Controller controller;
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

private:
   inline void setup();

   void updateDisplays() override;

   void uploadToHub();
   void receivedDocumentFromHub(const ::Midi::Channel& channel, const Svin::Json::Object& object, const uint8_t docIndex) override;

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   std::string fileName;
   Conductor conductor;
   Grooves localGrooves;
   std::vector<float> voltages;
   BoolField8 tickTriggers;
   BoolField8 segmentGates;

   // control
   uint8_t deviceId;
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

   // mode
   Svin::ButtonLED loopButton;

   OperationMode operationMode;
   Svin::Button operationModeButton;

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
