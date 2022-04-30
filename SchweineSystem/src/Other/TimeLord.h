#ifndef TimeLord2H
#define TimeLord2H

#include <rack.hpp>
using namespace rack;

#include <rtmidi/RtMidi.h>

#include <Blocks/PolyRamp.h>
#include <Music/Tempo.h>
#include <Tools/Range.h>

#include <SchweineSystemCommon.h>
#include <SchweineSystemJson.h>
#include <SchweineSystemLightMeter.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>
#include <SchweineSystemOLEDDisplay.h>

class TimeLord2 : public SchweineSystem::Module
{
public:
   struct Panel;

public:
   TimeLord2();
   ~TimeLord2();

public:
   void process(const ProcessArgs& args) override;
   void updateDisplays() override;

private:
   using Bytes = std::vector<uint8_t>;

   enum DisplayMode
   {
      Division,
      Length,
      StageCount,
      StageIndex
   };

   class Majordomo
   {
   public:
      static void hello(TimeLord2* server);
      static void bye(TimeLord2* server);

   private:
      Majordomo();
      void start();
      void stop();
      static void midiReceive(double timeStamp, std::vector<unsigned char>* message, void* userData);
      static void midiError(RtMidiError::Type type, const std::string& errorText, void* userData);

   private:
      static Majordomo* me;
      RtMidiIn midiInput;
      std::vector<TimeLord2*> instanceList;
   };

private:
   void setup();
   void dataFromMidiInput(const Bytes& message);

   json_t* dataToJson() override;
   void dataFromJson(json_t* rootJson) override;
   void loadInternal(const SchweineSystem::Json::Object& rootObject);

private:
   PolyRamp ramps[8];
   static const std::string keys;
   Bytes midiBuffer;

   dsp::BooleanTrigger clockTrigger;
   dsp::BooleanTrigger resetTrigger;
   Tempo tempo;

   Range::Mapper cvMapper;
   SchweineSystem::LightMeter::Controller::List lightMeterList;
   SchweineSystem::Output::List outputList;

   DisplayMode displayMode;
   dsp::BooleanTrigger displayTrigger;

   uint8_t bankIndex;
   dsp::BooleanTrigger bankTrigger;
   bool dataReceive;
   bool dataApply;
   dsp::PulseGenerator dataAppliedPulse;

   SchweineSystem::OLEDDisplay::Controller displayController;
};

class TimeLord2Widget : public SchweineSystem::ModuleWidget
{
public:
   TimeLord2Widget(TimeLord2* module);

private:
   void setup();
};

#endif // NOT TimeLord2H
