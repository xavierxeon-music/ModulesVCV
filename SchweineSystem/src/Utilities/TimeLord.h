#ifndef TimeLordH
#define TimeLordH

#include <rack.hpp>
using namespace rack;

#include <Blocks/PolyRamp.h>
#include <Music/Tempo.h>
#include <Tools/Range.h>

#include <SchweineSystemButton.h>
#include <SchweineSystemCommon.h>
#include <SchweineSystemDisplayLCD.h>
#include <SchweineSystemDisplayOLED.h>
#include <SchweineSystemJson.h>
#include <SchweineSystemLED.h>
#include <SchweineSystemLightMeter.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>
#include <SchweineSystemSwitch.h>

class TimeLord : public SchweineSystem::Module
{
public:
   struct Panel;

public:
   TimeLord();
   ~TimeLord();

public:
   void process(const ProcessArgs& args) override;
   void updateDisplays() override;

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

   void setOutputs(bool isReset, bool isClock);
   void setOperationLEDs();
   void dataFromMidiInput(const Bytes& message) override;

   json_t* dataToJson() override;
   void dataFromJson(json_t* rootJson) override;
   void loadInternal(const SchweineSystem::Json::Object& rootObject);

   void uploadToRemote();
   void loadRemote(const SchweineSystem::Json::Object& rootObject);

private:
   PolyRamp ramps[8];
   static const std::string keys;

   // midi
   MidiReceive receive;
   Bytes buffer;

   // clock
   dsp::BooleanTrigger clockTrigger;
   dsp::BooleanTrigger resetTrigger;
   Tempo tempo;

   // input
   SchweineSystem::Input::List inputList;
   SchweineSystem::DisplayLCD::Controller::List displayList;
   Range::Mapper voltageToValue;

   // upload
   dsp::BooleanTrigger uploadTrigger;
   bool uploadData;

   // outpt
   Range::Mapper valueToVoltage;
   SchweineSystem::LightMeter::Controller::List lightMeterList;
   SchweineSystem::Output::List outputList;

   // display
   DisplayMode displayMode;
   SchweineSystem::Button displayButton;
   SchweineSystem::DisplayOLED::Controller displayController;

   // bank
   uint8_t bankIndex;
   SchweineSystem::Button bankButton;
   dsp::PulseGenerator dataAppliedPulse;
   SchweineSystem::DisplayLCD::Controller bankDisplay;

   // mode
   OperationMode operationMode;
   dsp::BooleanTrigger operationTrigger;
   uint8_t remoteValues[8];
   SchweineSystem::LED modeInputLight;
   SchweineSystem::LED modeRemoteLight;
   SchweineSystem::LED modeInternalLight;

   // silence
   SchweineSystem::Switch::List silenceSwitches;
};

class TimeLordWidget : public SchweineSystem::ModuleWidget
{
public:
   TimeLordWidget(TimeLord* module);

private:
   void setup();
};

#endif // NOT TimeLordH
