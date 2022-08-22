#ifndef TimeLordH
#define TimeLordH

#include <rack.hpp>
using namespace rack;

#include <Blocks/PolyRamp.h>
#include <Music/Tempo.h>
#include <Tools/Range.h>

#include <SyButton.h>
#include <SyCommon.h>
#include <SyDisplayLCD.h>
#include <SyDisplayOLED.h>
#include <SyExapnder.h>
#include <SyJson.h>
#include <SyLED.h>
#include <SyLightMeter.h>
#include <SyModule.h>
#include <SyModuleWidget.h>
#include <SySvgImage.h>

struct BusTimeLord
{
   bool steady[8] = {false, false, false, false, false, false, false, false};
   bool silence[8] = {true, true, true, true, true, true, true, true};
};

class TimeLord : public Sy::Module, public Sy::Exapnder<BusTimeLord>
{
public:
   struct Panel;

public:
   TimeLord();
   ~TimeLord();

public:
   void process(const ProcessArgs& args) override;
   void updateDisplays() override;

   void loadRamps(const std::string& newFileName);

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
      Input,
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

   void setOutputs(bool isReset, bool isClock, const BusTimeLord& busMessage);
   void setOperationLEDs();
   void dataFromMidiInput(const Bytes& message) override;

   void load(const Sy::Json::Object& rootObject) override;
   void save(Sy::Json::Object& rootObject) override;

   void uploadToRemote(const BusTimeLord& busMessage);
   void setFromRemote(const Sy::Json::Object& rootObject);

private:
   std::string fileName;
   PolyRamp ramps[8];
   static const std::string keys;

   // midi
   MidiReceive receive;
   std::string buffer;

   // clock
   dsp::BooleanTrigger clockTrigger;
   dsp::BooleanTrigger resetTrigger;
   Tempo tempo;

   // input
   Sy::Input::List inputList;
   Sy::DisplayLCD::Controller::List displayList;
   Range::Mapper voltageToValue;

   // upload
   dsp::BooleanTrigger uploadTrigger;
   bool uploadData;

   // outpt
   Range::Mapper valueToVoltage;
   Sy::LightMeter::Controller::List lightMeterList;
   Sy::Output::List outputList;

   // display
   DisplayMode displayMode;
   Sy::Button displayButton;
   Sy::DisplayOLED::Controller displayController;

   // bank
   uint8_t bankIndex;
   Sy::Button bankButton;
   dsp::PulseGenerator dataAppliedPulse;
   Sy::DisplayLCD::Controller bankDisplay;

   // mode
   OperationMode operationMode;
   dsp::BooleanTrigger operationTrigger;
   uint8_t remoteValues[8];
   Sy::LED modeInputLight;
   Sy::LED modeRemoteLight;
   Sy::LED modeInternalLight;

};

class TimeLordWidget : public Sy::ModuleWidget
{
public:
   TimeLordWidget(TimeLord* module);

private:
   void setup();
   void displayClicked(const float& x, const float& y);
   void preDraw() override;

private:
   Sy::SvgImage* logoWidget;
};

#endif // NOT TimeLordH
