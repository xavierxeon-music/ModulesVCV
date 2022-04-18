#ifndef TimeLordServerH
#define TimeLordServerH

#include <rack.hpp>
using namespace rack;

#include <rtmidi/RtMidi.h>

#include <Blocks/PolyRamp.h>

class TimeLordServer : public Module
{
public:
   struct Panel;

public:
   TimeLordServer();
   ~TimeLordServer();

public:
   void process(const ProcessArgs& args) override;

private:
   using Bytes = std::vector<uint8_t>;

private:
   void setup();
   void dataFromInput(const Bytes& message);
   static void midiError(RtMidiError::Type type, const std::string& errorText, void* userData);
   static void midiReceive(double timeStamp, std::vector<unsigned char>* message, void* userData);

private:
   RtMidiIn input;
};

class TimeLordServerWidget : public ModuleWidget
{
public:
   TimeLordServerWidget(TimeLordServer* module);

private:
   SvgPanel* setup(TimeLordServer* module);
};

#endif // NOT TimeLordServerH
