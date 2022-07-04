#ifndef BarCounterH
#define BarCounterH

#include <rack.hpp>
using namespace rack;

#include <Music/Tempo.h>
#include <Tools/Counter.h>

#include <SchweineSystemDisplayLCD.h>
#include <SchweineSystemDisplayOLED.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class BarCounter : public SchweineSystem::Module
{
public:
   struct Panel;

public:
   BarCounter();

public:
   void process(const ProcessArgs& args) override;
   void updateDisplays() override;

private:
   void setup();

private:
   SchweineSystem::DisplayOLED::Controller displayController;
   // tempo
   Tempo tempo;
   SchweineSystem::DisplayLCD::Controller tempoController;
};

// widget

class BarCounterWidget : public SchweineSystem::ModuleWidget
{
public:
   BarCounterWidget(BarCounter* module);

private:
   void setup();
};

#endif // NOT BarCounterH
