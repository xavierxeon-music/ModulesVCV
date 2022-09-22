#include "NosferatuAcolyte.h"

Nosferatu::Acolyte::Acolyte()
   : Svin::Module()
{
   setup();

   registerAsBusModule<NosferatuBus>();

   display.setColor(Svin::Color{255, 255, 0});
}

void Nosferatu::Acolyte::process(const ProcessArgs& args)
{
   uint8_t counter = 0;
   Module* module = nullptr;

   for (module = busModule<NosferatuBus>(Side::Left); module != nullptr; module = module->busModule<NosferatuBus>(Side::Left))
   {
      counter++;
      if (dynamic_cast<Nosferatu*>(module))
         break;
   }
   if (!module)
      counter = 0;

   display.setText(std::to_string(counter));
}

// widget

Nosferatu::AcolyteWidget::AcolyteWidget(Acolyte* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelNosferatuAcolyte = Svin::Origin::the()->addModule<Nosferatu::Acolyte, Nosferatu::AcolyteWidget>("NosferatuAcolyte");
