#include "BefacoACDC.h"

BefacoACDC::BefacoACDC()
   : Svin::Module()
   , Svin::Midi::Input(Midi::Device::ACDC)
   , cvOutList(this)
   , cvMeterList(this)
   , ccValues{0, 0, 0, 0}
   , ccValueToVoltage(0.0, 127, 0, 10.0)
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
{
   setup();

   cvOutList.append({Panel::A, Panel::B, Panel::C, Panel::D});
   cvMeterList.append({Panel::Value_A, Panel::Value_B, Panel::Value_C, Panel::Value_D});

   for (uint8_t index = 0; index < 4; index++)
   {
      cvMeterList[index]->setMaxValue(126);
      cvMeterList[index]->setValue(0);
   }

   connectionButton.setDefaultColor(Colour{0, 255, 0});
   connectToMidiDevice();
}

void BefacoACDC::process(const ProcessArgs& args)
{
   if (connectionButton.isTriggered())
      connectToMidiDevice();

   for (uint8_t index = 0; index < 4; index++)
   {
      cvMeterList[index]->setValue(ccValues[index]);

      const float cvVoltage = ccValueToVoltage(ccValues[index]);
      cvOutList[index]->setVoltage(cvVoltage);
   }
}

void BefacoACDC::connectToMidiDevice()
{
   if (connected())
   {
      connectionButton.setOn();
      return;
   }

   connectionButton.setOff();
   if (!open())
      return;

   connectionButton.setOn();
}

void BefacoACDC::controllerChange(const Midi::Channel& channel, const Midi::ControllerMessage& controllerMessage, const uint8_t& value)
{
   if (2 != channel) //?? should be 11
      return;

   const uint8_t ccIndex = static_cast<uint8_t>(controllerMessage);
   if (ccIndex < Midi::ControllerMessage::User01)
      return;

   const uint8_t index = ccIndex - static_cast<uint8_t>(Midi::ControllerMessage::User01);
   ccValues[index] = value;
}

void BefacoACDC::load(const Svin::Json::Object& rootObject)
{
   Svin::Json::Array ccValueArray = rootObject.get("ccValues").toArray();
   for (uint8_t index = 0; index < 4; index++)
      ccValues[index] = ccValueArray.at(index).toBool();
}

void BefacoACDC::save(Svin::Json::Object& rootObject)
{
   Svin::Json::Array ccValueArray;
   for (uint8_t index = 0; index < 4; index++)
      ccValueArray.append(ccValues[index]);

   rootObject.set("ccValues", ccValueArray);
}

// widget

BefacoACDCWidget::BefacoACDCWidget(BefacoACDC* module)
: Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelBefacoACDC = Svin::Origin::the()->addModule<BefacoACDC, BefacoACDCWidget>("BefacoACDC");

