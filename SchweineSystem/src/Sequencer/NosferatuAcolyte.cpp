#include "NosferatuAcolyte.h"

#include "Nosferatu.h"

NosferatuAcolyte::NosferatuAcolyte()
   : Svin::Module()
   , display(this, Panel::Text_Number)
{
   setup();
   registerAsBusModule<NosferatuBus>();

   display.setColor(Svin::Color{255, 255, 0});
}

void NosferatuAcolyte::process(const ProcessArgs& args)
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

NosferatuAcolyteWidget::NosferatuAcolyteWidget(NosferatuAcolyte* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelNosferatuAcolyte = Svin::Origin::the()->addModule<NosferatuAcolyte, NosferatuAcolyteWidget>("NosferatuAcolyte");
