#ifndef DoepferQuadH
#define DoepferQuadH

#include <rack.hpp>
using namespace rack;

#include <rtmidi/RtMidi.h>

#include <Midi/MidiCommon.h>
#include <Tools/Range.h>

#include <SchweineSystemCommon.h>
#include <SchweineSystemLight.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class DoepferQuad : public SchweineSystem::Module
{
public:
   struct Panel;

public:
   DoepferQuad();
   ~DoepferQuad();

public:
   void process(const ProcessArgs& args) override;

private:
   struct ChannelStore
   {
      std::vector<uint16_t> inputIdList;
      uint8_t note = 0;
      uint8_t velocity = 127;
      uint8_t controllerValue = 0;
      uint8_t sendNote = 0;

      using Map = std::map<Midi::Channel, ChannelStore>;
   };

private:
   void setup();
   void connectToMidiDevice();

private:
   RtMidiOut midiOutput;
   dsp::BooleanTrigger connectTrigger;
   Range::Mapper voltageToCcValue;
   SchweineSystem::Light connectionLight;

   ChannelStore::Map channelMap;
};

class DoepferQuadWidget : public SchweineSystem::ModuleWidget
{
public:
   DoepferQuadWidget(DoepferQuad* module);

private:
   void setup();
};

#endif // NOT DoepferQuadH
