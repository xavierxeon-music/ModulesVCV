#include "VCMCReceiver.h"

#include <Midi/MidiCommon.h>

#include <SvinMidi.h>
#include <SvinOrigin.h>

VCMCReceiver::VCMCReceiver()
   : Svin::Module()
   , Svin::MidiInput(Midi::Device::VCMC)
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
   , ccValueToVoltage(0.0, 127, 0, 10.0)
   , gates{false, false, false, false, false, false, false, false}
   , latches{false, false, false, false, false, false, false, false}
   , gateOutput(this, Panel::Gate)
   , gateLights(this)
   , latchLights(this)
   , latchReset(this, Panel::Reset)
   , cvValues{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
   , cvOutput(this, Panel::CV)
   , aOutput(this, Panel::External_A)
   , bOutput(this, Panel::External_B)
   , cvMeter(this)
   , aMeter(this, Panel::Value_External_A)
   , bMeter(this, Panel::Value_External_B)
{
   setup();

   gateLights.append({Panel::RGB_Gate_Channel1,
                      Panel::RGB_Gate_Channel2,
                      Panel::RGB_Gate_Channel3,
                      Panel::RGB_Gate_Channel4,
                      Panel::RGB_Gate_Channel5,
                      Panel::RGB_Gate_Channel6,
                      Panel::RGB_Gate_Channel7,
                      Panel::RGB_Gate_Channel8});

   latchLights.append({Panel::RGB_Latch_Channel1,
                       Panel::RGB_Latch_Channel2,
                       Panel::RGB_Latch_Channel3,
                       Panel::RGB_Latch_Channel4,
                       Panel::RGB_Latch_Channel5,
                       Panel::RGB_Latch_Channel6,
                       Panel::RGB_Latch_Channel7,
                       Panel::RGB_Latch_Channel8});

   cvMeter.append({Panel::Value_CV_Channel1,
                   Panel::Value_CV_Channel2,
                   Panel::Value_CV_Channel3,
                   Panel::Value_CV_Channel4,
                   Panel::Value_CV_Channel5,
                   Panel::Value_CV_Channel6,
                   Panel::Value_CV_Channel7,
                   Panel::Value_CV_Channel8,
                   Panel::Value_Slider_Channel1,
                   Panel::Value_Slider_Channel2,
                   Panel::Value_Slider_Channel3,
                   Panel::Value_Slider_Channel4,
                   Panel::Value_Slider_Channel5,
                   Panel::Value_Slider_Channel6,
                   Panel::Value_Slider_Channel7,
                   Panel::Value_Slider_Channel8});

   for (uint8_t index = 0; index < 8; index++)
   {
      gateLights[index]->setDefaultColor(Color::Predefined::White);
      latchLights[index]->setDefaultColor(Color::Predefined::Cyan);
   }

   for (uint8_t index = 0; index < 16; index++)
   {
      cvMeter[index]->setMaxValue(127);
      cvMeter[index]->setValue(0);
   }

   aMeter.setMaxValue(127);
   aMeter.setValue(0);

   bMeter.setMaxValue(127);
   bMeter.setValue(0);

   connectionButton.setDefaultColor(Color::Predefined::Green);
   connectToMidiDevice();
}

void VCMCReceiver::process(const ProcessArgs& args)
{
   if (connectionButton.isTriggered())
      connectToMidiDevice();

   if (latchReset.isTriggered())
   {
      for (uint8_t index = 0; index < 8; index++)
         latches[index] = false;
   }

   gateOutput.setNumberOfChannels(16);
   cvOutput.setNumberOfChannels(16);

   for (uint8_t index = 0; index < 8; index++)
   {
      gateLights[index]->setActive(gates[index]);
      gateOutput.setActive(gates[index], index);

      latchLights[index]->setActive(latches[index]);
      gateOutput.setActive(latches[index], index + 8);
   }

   for (uint8_t index = 0; index < 16; index++)
   {
      cvMeter[index]->setValue(cvValues[index]);

      const float cvVoltage = ccValueToVoltage(cvValues[index]);
      cvOutput.setVoltage(cvVoltage, index);
   }

   aMeter.setValue(cvValues[16]);
   const float aVoltage = ccValueToVoltage(cvValues[16]);
   aOutput.setVoltage(aVoltage);

   bMeter.setValue(cvValues[17]);
   const float bVoltage = ccValueToVoltage(cvValues[17]);
   bOutput.setVoltage(bVoltage);
}

void VCMCReceiver::connectToMidiDevice()
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

void VCMCReceiver::noteOn(const Midi::Channel& channel, const uint8_t& midiNote, const Midi::Velocity& velocity)
{
   if (Midi::Device::VCVRack != channel)
      return;

   // VCMC does not send note off, instead a second note on with velocity 0

   const uint8_t gateIndex = midiNote - 60;
   const bool on = (0 != velocity);
   gates[gateIndex] = on;
   if (on)
      latches[gateIndex] ^= true;
}

void VCMCReceiver::controllerChange(const Midi::Channel& channel, const Midi::ControllerMessage& controllerMessage, const uint8_t& value)
{
   if (Midi::Device::VCVRack != channel)
      return;

   const uint8_t index = static_cast<uint8_t>(controllerMessage);

   if (index >= 10)
      cvValues[index - 2] = value;
   else
      cvValues[index] = value;
}

void VCMCReceiver::load(const Svin::Json::Object& rootObject)
{
   Svin::Json::Array latchesArray = rootObject.get("latches").toArray();
   for (uint8_t index = 0; index < 8; index++)
      latches[index] = latchesArray.at(index).toBool();

   Svin::Json::Array cvValueArray = rootObject.get("cvValues").toArray();
   for (uint8_t index = 0; index < 18; index++)
      cvValues[index] = cvValueArray.at(index).toInt();
}

void VCMCReceiver::save(Svin::Json::Object& rootObject)
{
   Svin::Json::Array latchesArray;
   for (uint8_t index = 0; index < 8; index++)
      latchesArray.append(latches[index]);

   Svin::Json::Array cvValueArray;
   for (uint8_t index = 0; index < 18; index++)
      cvValueArray.append(cvValues[index]);

   rootObject.set("latches", latchesArray);
   rootObject.set("cvValues", cvValueArray);
}

// widget

VCMCReceiverWidget::VCMCReceiverWidget(VCMCReceiver* module)
   : Svin::ModuleWidget(module)
{
   setup();
}
// create module
Model* modelVCMCReceiver = Svin::Origin::the()->addModule<VCMCReceiver, VCMCReceiverWidget>("VCMCReceiver");
