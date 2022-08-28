#ifndef TimeLordH
#define TimeLordH

#include <rack.hpp>
using namespace rack;

#include <Blocks/PolyRamp.h>
#include <Music/Tempo.h>
#include <Tools/Range.h>

#include <SvinExapnder.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButton.h>
#include <SvinCommon.h>
#include <SvinDisplayLCD.h>
#include <SvinDisplayOLED.h>
#include <SvinInput.h>
#include <SvinJson.h>
#include <SvinLED.h>
#include <SvinLightMeter.h>
#include <SvinOutput.h>
#include <SvinSvgImage.h>

struct BusTimeLord
{
   bool steady[8] = {false, false, false, false, false, false, false, false};
   bool silence[8] = {true, true, true, true, true, true, true, true};
};

class TimeLord : public Svin::Module, public Svin::Exapnder<BusTimeLord>
{
public:
   struct Panel;

public:
   TimeLord();
   ~TimeLord();

public:
   void process(const ProcessArgs& args) override;
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
   void updateDisplays() override;

   void setOutputs(bool isReset, bool isClock, const BusTimeLord& busMessage);
   void setOperationLEDs();
   void dataFromMidiInput(const Bytes& message) override;

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

   void uploadToRemote(const BusTimeLord& busMessage);
   void setFromRemote(const Svin::Json::Object& rootObject);

   void displayClicked(const float& x, const float& y);

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
   Svin::Input::List inputList;
   Svin::DisplayLCD::Controller::List displayList;
   Range::Mapper voltageToValue;

   // upload
   dsp::BooleanTrigger uploadTrigger;
   bool uploadData;

   // outpt
   Range::Mapper valueToVoltage;
   Svin::LightMeter::Controller::List lightMeterList;
   Svin::Output::List outputList;

   // display
   DisplayMode displayMode;
   Svin::Button displayButton;
   Svin::DisplayOLED::Controller displayController;

   // bank
   uint8_t bankIndex;
   Svin::Button bankButton;
   dsp::PulseGenerator dataAppliedPulse;
   Svin::DisplayLCD::Controller bankDisplay;

   // mode
   OperationMode operationMode;
   dsp::BooleanTrigger operationTrigger;
   uint8_t remoteValues[8];
   Svin::LED modeInputLight;
   Svin::LED modeRemoteLight;
   Svin::LED modeInternalLight;
};

class TimeLordWidget : public Svin::ModuleWidget
{
public:
   TimeLordWidget(TimeLord* module);

private:
   void setup();
   void preDraw() override;

private:
   Svin::SvgImage* logoWidget;
};

#endif // NOT TimeLordH
