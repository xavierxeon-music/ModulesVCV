#ifndef DoepferQuadCVH
#define DoepferQuadCVH

#include <rack.hpp>
using namespace rack;

#include <Tools/Range.h>

#include <SchweineSystemButtonLED.h>
#include <SchweineSystemCommon.h>
#include <SchweineSystemMidiOutput.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class DoepferQuadCV : public SchweineSystem::Module, private SchweineSystem::MidiOutput
{
public:
   struct Panel;

public:
   DoepferQuadCV();
   ~DoepferQuadCV();

public:
   void process(const ProcessArgs& args) override;

private:
   struct ChannelStore
   {
      std::vector<uint16_t> inputIdList;
      uint8_t note = 24;
      uint8_t velocity = 64;
      uint8_t controllerValue = 0;
      bool requestSendNote = false;

      using Map = std::map<Midi::Channel, ChannelStore>;
   };

private:
   void setup();
   void connectToMidiDevice();

private:
   SchweineSystem::ButtonLED connectionButton;
   Range::Mapper voltageToNote;
   Range::Mapper voltageToCcValue;

   ChannelStore::Map channelMap;
};

// widget

class DoepferQuadCVWidget : public SchweineSystem::ModuleWidget
{
public:
   DoepferQuadCVWidget(DoepferQuadCV* module);

private:
   void setup();
};

#endif // NOT DoepferQuadCVH
