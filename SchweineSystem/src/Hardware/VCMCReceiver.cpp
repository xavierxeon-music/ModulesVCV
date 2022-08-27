#include "VCMCReceiver.h"
#include "VCMCReceiverPanel.h"

#include <Midi/MidiCommon.h>

#include <SvinMaster.h>
#include <SvinMidiOutput.h>

VCMCReceiver::VCMCReceiver()
   : Svin::Module()
   , midiInput()
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
   , ccValueToVoltage(0.0, 127, 0, 10.0)
   , gates{false, false, false, false, false, false, false, false}
   , latches{false, false, false, false, false, false, false, false}
   , gateOutput(this, Panel::Gate)
   , gateLights(this)
   , latchLights(this)
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
      gateLights[index]->setDefaultColor(Svin::Color{255, 255, 255});
      latchLights[index]->setDefaultColor(Svin::Color{0, 255, 255});
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

   connectionButton.setDefaultColor(Svin::Color{0, 255, 0});
   connectToMidiDevice();
}

void VCMCReceiver::process(const ProcessArgs& args)
{
   if (connectionButton.isTriggered())
      connectToMidiDevice();

   midi::Message msg;
   while (midiInput.tryPop(&msg, args.frame))
      processMessage(msg);

   if (16 != gateOutput.getNumberOfChannels())
      gateOutput.setNumberOfChannels(16);

   if (16 != cvOutput.getNumberOfChannels())
      cvOutput.setNumberOfChannels(16);

   for (uint8_t index = 0; index < 8; index++)
   {
      gateLights[index]->setActive(gates[index]);
      gateOutput.setActive(index, gates[index]);

      latchLights[index]->setActive(latches[index]);
      gateOutput.setActive(index + 8, latches[index]);
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

void VCMCReceiver::processMessage(const midi::Message& msg)
{
   const bool isSystemEvent = (0xF0 == (msg.bytes[0] & 0xF0));
   if (isSystemEvent)
      return;

   const Midi::Event event = static_cast<Midi::Event>(msg.bytes[0] & 0xF0);
   const Midi::Channel channel = 1 + (msg.bytes[0] & 0x0F);
   if (Midi::Device::VCVRack != channel)
      return;

   if (Midi::Event::NoteOn == event)
   {
      const uint8_t gateIndex = msg.bytes[1] - 60;
      const bool on = (0 != msg.bytes[2]);
      gates[gateIndex] = on;
      if (on)
         latches[gateIndex] ^= true;
   }
   else if (Midi::Event::NoteOff == event)
   {
      // VCMC does not send note off, instead a second note on with velocity 0
   }
   else if (Midi::Event::ControlChange == event)
   {
      const uint8_t index = msg.bytes[1];
      const uint8_t value = msg.bytes[2];

      if (index >= 10)
         cvValues[index - 2] = value;
      else
         cvValues[index] = value;
   }
}

void VCMCReceiver::connectToMidiDevice()
{
   midiInput.reset();
   connectionButton.setOff();

   static const std::string targetDeviceName = Svin::Common::midiInterfaceMap.at(Midi::Device::VCMC);
   std::cout << "TARGET = " << targetDeviceName << std::endl;

   for (const int& deviceId : midiInput.getDeviceIds())
   {
      const std::string deviceName = midiInput.getDeviceName(deviceId);
      //std::cout << deviceName << std::endl;

      if (targetDeviceName == deviceName)
      {
         std::cout << "connected to " << deviceName << " @ " << deviceId << std::endl;
         midiInput.setDeviceId(deviceId);
         connectionButton.setOn();
         return;
      }
   }
}

// widget

VCMCReceiverWidget::VCMCReceiverWidget(VCMCReceiver* module)
: Svin::ModuleWidget(module)
{
   setup();
}

Model* modelVCMCReceiver = Svin::Master::the()->addModule<VCMCReceiver, VCMCReceiverWidget>("VCMCReceiver");
