#include "BarCounter.h"
#include "BarCounterPanel.h"

#include <SchweineSystemMaster.h>

BarCounter::BarCounter()
   : SchweineSystem::Module()
   , displayController(this, Panel::Pixels_Display, 64, 128)
   , tempo()
   , tempoController(this, Panel::Text_Tempo, Panel::RGB_Tempo)
{
   setup();

   tempoController.setColor(SchweineSystem::Color{0, 0, 255});
}

// widget

void BarCounter::process(const ProcessArgs& args)
{
   tempoController.setText("123");
}

void BarCounter::updateDisplays()
{
   displayController.fill();

   displayController.drawRect(0, 0, 63, 10, true);
}

BarCounterWidget::BarCounterWidget(BarCounter* module)
   : SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelBarCounter = SchweineSystem::Master::the()->addModule<BarCounter, BarCounterWidget>("BarCounter");
