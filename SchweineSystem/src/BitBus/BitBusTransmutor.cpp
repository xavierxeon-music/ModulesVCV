#include "BitBusTransmutor.h"
#include "BitBusTransmutorPanel.h"

#include <Maths.h>
#include <Sound/StandardTable.h>
#include <Tools/BoolField.h>

#include <SvinOrigin.h>

BitBusTransmutor::BitBusTransmutor()
   : Svin::Module()
   , Svin::Exapnder<BitBusMessage>(this)
   , displayButton(this, Panel::Display)
   , displayController(this, Panel::Pixels_Display)
   , busInIndicator(this, Panel::RGB_BusIn)
   , busOutIndicator(this, Panel::RGB_BusOut)
   , inputMapper(-1.0, 1.0, 0.0, 255.0)
   , table(nullptr)
{
   setup();

   Standard::Table* standardTable = new Standard::Table();
   standardTable->setWaveform(Standard::Waveform::SlopeDown);

   table = standardTable;

   allowExpanderOnLeft();
   allowExpanderOnRight();
}

void BitBusTransmutor::load(const Svin::Json::Object& rootObject)
{
}

void BitBusTransmutor::save(Svin::Json::Object& rootObject)
{
}

void BitBusTransmutor::process(const ProcessArgs& args)
{
   if (!canCommunicatWithLeft())
      return busInIndicator.setOff();
   else
      busInIndicator.setOn();

   if (!canCommunicatWithRight())
      return busOutIndicator.setOff();
   else
      busOutIndicator.setOn();

   const BoolField8 boolFieldIn = receiveFromLeft().byte;
   const float angle = static_cast<float>(boolFieldIn) * 2.0 * Maths::pi / 255.0;
   const float value = table->valueByAngle(angle);

   BoolField8 boolFieldOut = static_cast<uint8_t>(inputMapper(value));
   sendToRight(BitBusMessage{boolFieldOut});
}

void BitBusTransmutor::updateDisplays()
{
   displayController.fill();
}

// widget

BitBusTransmutorWidget::BitBusTransmutorWidget(BitBusTransmutor* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

Model* modelBitBusTransmutor = Svin::Origin::the()->addModule<BitBusTransmutor, BitBusTransmutorWidget>("BitBusTransmutor");
