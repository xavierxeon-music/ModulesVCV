#ifndef MidiReplayH
#define MidiReplayH

#include <rack.hpp>
using namespace rack;

#include <SchweineSystemDisplayOLED.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class MidiReplay : public SchweineSystem::Module
{
public:
   struct Panel;

public:
   MidiReplay();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();

private:
   SchweineSystem::DisplayOLED::Controller displayController;
};

// widget

class MidiReplayWidget : public SchweineSystem::ModuleWidget
{
public:
   MidiReplayWidget(MidiReplay* module);

private:
   void setup();
};

#endif // NOT MidiReplayH
