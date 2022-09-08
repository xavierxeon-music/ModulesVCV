#include "MeshStack.h"
#include "MeshStackPanel.h"

#include <SvinOrigin.h>

MeshStack::MeshStack()
   : Svin::Module()
   , knob(this, Panel::Mode)
   , colorSliders(this)
   , colorLED(this, Panel::RGB_Color)
{
   setup();

   colorSliders.append({{Panel::Red, Panel::RGB_Red},
                        {Panel::Green, Panel::RGB_Green},
                        {Panel::Blue, Panel::RGB_Blue}});

   knob.setRange(0, 10);
   knob.enableSteps(true, 0.5);

   for (uint8_t index = 0; index < 3; index++)
   {
      colorSliders[index]->setRange(0, 10);
      colorSliders[index]->enableSteps(true, 0.5);
   }
}

void MeshStack::process(const ProcessArgs& args)
{
   Svin::Color ledColor = {0, 0, 0};

   for (uint8_t index = 0; index < 3; index++)
   {
      const float precentage = colorSliders[index]->getValue() / 10.0;
      const uint8_t value = static_cast<uint8_t>(255 * precentage);

      Svin::Color color{0, 0, 0};
      if (0 == index)
      {
         color.red = value;
         ledColor.red = value;
      }
      else if (1 == index)
      {
         color.green = value;
         ledColor.green = value;
      }
      else if (2 == index)
      {
         color.blue = value;
         ledColor.blue = value;
      }

      colorSliders[index]->setColor(color);
   }

   colorLED.setColor(ledColor);
}

void MeshStack::updateDisplays()
{
}

// widget

MeshStackWidget::MeshStackWidget(MeshStack* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

Model* modelMeshStack = Svin::Origin::the()->addModule<MeshStack, MeshStackWidget>("MeshStack");
