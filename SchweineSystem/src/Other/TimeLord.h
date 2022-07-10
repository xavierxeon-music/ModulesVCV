#ifndef TimeLordH
#define TimeLordH

#include <rack.hpp>
using namespace rack;

#include <Blocks/PolyRamp.h>
#include <Music/Tempo.h>
#include <Tools/Range.h>

#include <SchweineSystemCommon.h>
#include <SchweineSystemDisplayLCD.h>
#include <SchweineSystemDisplayOLED.h>
#include <SchweineSystemJson.h>
#include <SchweineSystemLED.h>
#include <SchweineSystemLightMeter.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

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
   Bytes rampBuffer;

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
   dsp::BooleanTrigger displayTrigger;
   SchweineSystem::DisplayOLED::Controller displayController;

   // bank
   uint8_t bankIndex;
   dsp::BooleanTrigger bankTrigger;
   bool dataReceive;
   dsp::PulseGenerator dataAppliedPulse;
   SchweineSystem::DisplayLCD::Controller bankDisplay;

   // mode
   OperationMode operationMode;
   dsp::BooleanTrigger operationTrigger;
   uint8_t remoteValues[8];
   Bytes remoteBuffer;
   SchweineSystem::LED modeInputLight;
   SchweineSystem::LED modeRemoteLight;
   SchweineSystem::LED modeInternalLight;
};

class TimeLordWidget : public SchweineSystem::ModuleWidget
{
public:
   TimeLordWidget(TimeLord* module);

private:
   void setup();
};

#endif // NOT TimeLordH
