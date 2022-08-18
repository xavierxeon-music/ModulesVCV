#ifndef DoepferQuadMidiH
#define DoepferQuadMidiH

#include <rack.hpp>
using namespace rack;

#include <SchweineSystemButtonLED.h>
#include <SchweineSystemExapnder.h>
#include <SchweineSystemMidiOutput.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

#include <SchweineSystemExpanderMessages.h>

class DoepferQuadMidi : public SchweineSystem::Module, private SchweineSystem::MidiOutput, public SchweineSystem::Exapnder<SchweineSystem::BusMidi>
{
public:
   struct Panel;

public:
   DoepferQuadMidi();

public:
   void process(const ProcessArgs& args) override;

private:
   struct NoteBuffer
   {
      uint8_t index = 0;
      uint8_t channel = 0;
      uint8_t key = 0;

      NoteBuffer(uint8_t index, uint8_t channel, uint8_t key);
      bool operator==(const NoteBuffer& other) const;

      using List = std::list<NoteBuffer>;
   };

   friend std::ostream& operator<<(std::ostream& os, const NoteBuffer& buffer);

private:
   void setup();
   void connectToMidiDevice();
   void processBusMessage(const SchweineSystem::BusMidi& busMessage);

private:
   SchweineSystem::ButtonLED connectionButton;
   NoteBuffer::List bufferList;
   bool wasRunning;
};

// widget

class DoepferQuadMidiWidget : public SchweineSystem::ModuleWidget
{
public:
   DoepferQuadMidiWidget(DoepferQuadMidi* module);

private:
   void setup();
};

#endif // NOT DoepferQuadMidiH
