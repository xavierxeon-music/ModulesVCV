#include "VCMCReceiver.h"
#include "VCMCReceiverPanel.h"

#include <Midi/MidiCommon.h>
#include <Music/Note.h>

#include <SyJson.h>
#include <SyDisplayLCD.h>
#include <SyMaster.h>

VCMCReceiver::VCMCReceiver()
   : Sy::Module()
   , midiInput()
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
   , ccValueToVoltage(0.0, 127, 0, 10.0)
   , gates{false, false, false, false, false, false, false, false}
   , lightListGate(this)
   , gateList(outputs)
   , sliderValues{0, 0, 0, 0, 0, 0, 0, 0}
   , lightMeterListSlider(this)
   , sliderOutputList(outputs)
   , cvValues{0, 0, 0, 0, 0, 0, 0, 0}
   , lightMeterListCV(this)
   , cvOutputList(outputs)
{
   setup();

   lightListGate.append({Panel::RGB_Channel1_Gate7_Status1,
                         Panel::RGB_Channel2_Gate6_Status1,
                         Panel::RGB_Channel3_Gate5_Status1,
                         Panel::RGB_Channel4_Gate4_Status1,
                         Panel::RGB_Channel5_Gate3_Status1,
                         Panel::RGB_Channel6_Gate2_Status1,
                         Panel::RGB_Channel7_Gate1_Status1,
                         Panel::RGB_Channel8_Gate_Status1});

   gateList.append({Panel::Channel1_Gate7_BitOut1,
                    Panel::Channel2_Gate6_BitOut1,
                    Panel::Channel3_Gate5_BitOut1,
                    Panel::Channel4_Gate4_BitOut1,
                    Panel::Channel5_Gate3_BitOut1,
                    Panel::Channel6_Gate2_BitOut1,
                    Panel::Channel7_Gate1_BitOut1,
                    Panel::Channel8_Gate_BitOut1});

   lightMeterListSlider.append({Panel::Value_Channel1_Slider7_Strip,
                                Panel::Value_Channel2_Slider6_Strip,
                                Panel::Value_Channel3_Slider5_Strip,
                                Panel::Value_Channel4_Slider4_Strip,
                                Panel::Value_Channel5_Slider3_Strip,
                                Panel::Value_Channel6_Slider2_Strip,
                                Panel::Value_Channel7_Slider1_Strip,
                                Panel::Value_Channel8_Slider_Strip});

   sliderOutputList.append({Panel::Channel1_Slider7_Output,
                            Panel::Channel2_Slider6_Output,
                            Panel::Channel3_Slider5_Output,
                            Panel::Channel4_Slider4_Output,
                            Panel::Channel5_Slider3_Output,
                            Panel::Channel6_Slider2_Output,
                            Panel::Channel7_Slider1_Output,
                            Panel::Channel8_Slider_Output});

   lightMeterListCV.append({Panel::Value_Channel1_CV7_Strip,
                            Panel::Value_Channel2_CV6_Strip,
                            Panel::Value_Channel3_CV5_Strip,
                            Panel::Value_Channel4_CV4_Strip,
                            Panel::Value_Channel5_CV3_Strip,
                            Panel::Value_Channel6_CV2_Strip,
                            Panel::Value_Channel7_CV1_Strip,
                            Panel::Value_Channel8_CV_Strip,
                            Panel::Value_External_A,
                            Panel::Value_External_B});

   cvOutputList.append({Panel::Channel1_CV7_Output,
                        Panel::Channel2_CV6_Output,
                        Panel::Channel3_CV5_Output,
                        Panel::Channel4_CV4_Output,
                        Panel::Channel5_CV3_Output,
                        Panel::Channel6_CV2_Output,
                        Panel::Channel7_CV1_Output,
                        Panel::Channel8_CV_Output,
                        Panel::External_A,
                        Panel::External_B});

   for (uint8_t index = 0; index < 10; index++)
   {
      lightListGate[index]->setDefaultColor(Sy::Color{255, 0, 255});
      lightMeterListCV[index]->setMaxValue(127);
      if (index < 8)
         lightMeterListSlider[index]->setMaxValue(127);
   }

   connectionButton.setDefaultColor(Sy::Color{0, 255, 0});
   connectToMidiDevice();
}

VCMCReceiver::~VCMCReceiver()
{
}

void VCMCReceiver::process(const ProcessArgs& args)
{
   if (connectionButton.isTriggered())
      connectToMidiDevice();

   midi::Message msg;
   while (midiInput.tryPop(&msg, args.frame))
      processMessage(msg);

   for (uint8_t index = 0; index < 10; index++)
   {
      if (index < 8)
      {
         if (gates[index])
         {
            lightListGate[index]->setOn();
            gateList[index]->setVoltage(10.0);
         }
         else
         {
            lightListGate[index]->setOff();
            gateList[index]->setVoltage(0.0);
         }

         lightMeterListSlider[index]->setValue(sliderValues[index]);
         const float sliderVoltage = ccValueToVoltage(sliderValues[index]);
         sliderOutputList[index]->setVoltage(sliderVoltage);
      }

      lightMeterListCV[index]->setValue(cvValues[index]);
      const float cvVoltage = ccValueToVoltage(cvValues[index]);
      cvOutputList[index]->setVoltage(cvVoltage);
   }
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
         sliderValues[index - 10] = value;
      else
         cvValues[index] = value;
   }
}

void VCMCReceiver::connectToMidiDevice()
{
   midiInput.reset();
   connectionButton.setOff();

   static const std::string targetDeviceName = Sy::Common::midiInterfaceMap.at(Midi::Device::VCMC);
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

void VCMCReceiver::load(const Sy::Json::Object& rootObject)
{
   Sy::Json::Array gateArray = rootObject.get("gates").toArray();
   Sy::Json::Array cvArray = rootObject.get("cvs").toArray();
   Sy::Json::Array sliderArray = rootObject.get("sliders").toArray();

   for (uint8_t index = 0; index < 8; index++)
   {
      gates[index] = gateArray.get(index).toBool();
      cvValues[index] = cvArray.get(index).toInt();
      sliderValues[index] = sliderArray.get(index).toInt();
   }
}

void VCMCReceiver::save(Sy::Json::Object& rootObject)
{
   Sy::Json::Array gateArray;
   Sy::Json::Array cvArray;
   Sy::Json::Array sliderArray;
   for (uint8_t index = 0; index < 8; index++)
   {
      gateArray.append(gates[index]);
      cvArray.append(cvValues[index]);
      sliderArray.append(sliderValues[index]);
   }

   rootObject.set("gates", gateArray);
   rootObject.set("cvs", cvArray);
   rootObject.set("sliders", sliderArray);
}

// widget

VCMCReceiverWidget::VCMCReceiverWidget(VCMCReceiver* module)
   : Sy::ModuleWidget(module)
{
   setup();
}

Model* modelVCMCReceiver = Sy::Master::the()->addModule<VCMCReceiver, VCMCReceiverWidget>("VCMCReceiver");
