#ifndef DoepferQuadH
#define DoepferQuadH

#include <rack.hpp>
using namespace rack;

#include <Midi/MidiCommon.h>
#include <Tools/Range.h>

#include <SchweineSystemCommon.h>
#include <SchweineSystemLight.h>

class DoepferQuad : public Module
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
      uint8_t prevNote = 0;
      uint8_t prevVelocity = 127;
      uint8_t prevControllerValue = 0;

      using Map = std::map<Midi::Channel, ChannelStore>;
   };

private:
   void setup();
   void connectToMidiDevice();

private:
   midi::Output midiOutput;
   dsp::BooleanTrigger connectTrigger;
   Range::Mapper voltageToCcValue;
   SchweineSystem::Light connectionLight;

   ChannelStore::Map channelMap;
};

class DoepferQuadWidget : public ModuleWidget
{
public:
   DoepferQuadWidget(DoepferQuad* module);

private:
   SvgPanel* setup(DoepferQuad* module);
};

#endif // NOT DoepferQuadH
