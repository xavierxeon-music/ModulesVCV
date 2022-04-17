#include "VCMCReceiver.h"
#include "VCMCReceiverPanel.h"

#include <Midi/MidiCommon.h>
#include <Music/Note.h>

#include "SchweineSystemLCDDisplay.h"
#include "SchweineSystemMaster.h"

VCMCReceiver::VCMCReceiver()
   : Module()
   , bpm(12)
   , midiInput()
   , midiTickCounter(0)
   , doNotAdvanceTempo(false)
   , tempo()
   , clockTick()
   , clockReset()
   , connectionLight(lights)
   , gates{false, false, false, false, false, false, false, false}
   , lightListGate(lights)
   , gateList(outputs)
   , cvValues{0, 0, 0, 0, 0, 0, 0, 0}
   , lightMeterListCV(lights)
   , cvOutputList(outputs)
   , lightMeterListSlider(lights)
   , sliderOutputList(outputs)
   , connectTrigger()
   , ccValueToVoltage(0.0, 127, 0, 10.0)
{
   setup();

   lightListGate.append({Panel::Red_Channel1_Gate1_Status1,
                         Panel::Red_Channel2_Gate2_Status1,
                         Panel::Red_Channel3_Gate3_Status1,
                         Panel::Red_Channel4_Gate4_Status1,
                         Panel::Red_Channel5_Gate5_Status1,
                         Panel::Red_Channel6_Gate6_Status1,
                         Panel::Red_Channel7_Gate7_Status1,
                         Panel::Red_Channel8_Gate8_Status1});

   gateList.append({Panel::Channel1_Gate1_BitOut1,
                    Panel::Channel2_Gate2_BitOut1,
                    Panel::Channel3_Gate3_BitOut1,
                    Panel::Channel4_Gate4_BitOut1,
                    Panel::Channel5_Gate5_BitOut1,
                    Panel::Channel6_Gate6_BitOut1,
                    Panel::Channel7_Gate7_BitOut1,
                    Panel::Channel8_Gate8_BitOut1});

   lightMeterListCV.append({{Panel::Red_Channel1_CV1_Status1, Panel::Red_Channel1_CV1_Status2, Panel::Red_Channel1_CV1_Status3, Panel::Red_Channel1_CV1_Status4, Panel::Red_Channel1_CV1_Status5},
                            {Panel::Red_Channel2_CV2_Status1, Panel::Red_Channel2_CV2_Status2, Panel::Red_Channel2_CV2_Status3, Panel::Red_Channel2_CV2_Status4, Panel::Red_Channel2_CV2_Status5},
                            {Panel::Red_Channel3_CV3_Status1, Panel::Red_Channel3_CV3_Status2, Panel::Red_Channel3_CV3_Status3, Panel::Red_Channel3_CV3_Status4, Panel::Red_Channel3_CV3_Status5},
                            {Panel::Red_Channel4_CV4_Status1, Panel::Red_Channel4_CV4_Status2, Panel::Red_Channel4_CV4_Status3, Panel::Red_Channel4_CV4_Status4, Panel::Red_Channel4_CV4_Status5},
                            {Panel::Red_Channel5_CV5_Status1, Panel::Red_Channel5_CV5_Status2, Panel::Red_Channel5_CV5_Status3, Panel::Red_Channel5_CV5_Status4, Panel::Red_Channel5_CV5_Status5},
                            {Panel::Red_Channel6_CV6_Status1, Panel::Red_Channel6_CV6_Status2, Panel::Red_Channel6_CV6_Status3, Panel::Red_Channel6_CV6_Status4, Panel::Red_Channel6_CV6_Status5},
                            {Panel::Red_Channel7_CV7_Status1, Panel::Red_Channel7_CV7_Status2, Panel::Red_Channel7_CV7_Status3, Panel::Red_Channel7_CV7_Status4, Panel::Red_Channel7_CV7_Status5},
                            {Panel::Red_Channel8_CV8_Status1, Panel::Red_Channel8_CV8_Status2, Panel::Red_Channel8_CV8_Status3, Panel::Red_Channel8_CV8_Status4, Panel::Red_Channel8_CV8_Status5}});

   cvOutputList.append({Panel::Channel1_CV1_Output, Panel::Channel2_CV2_Output, Panel::Channel3_CV3_Output, Panel::Channel4_CV4_Output, Panel::Channel5_CV5_Output, Panel::Channel6_CV6_Output, Panel::Channel7_CV7_Output, Panel::Channel8_CV8_Output});

   lightMeterListSlider.append({{Panel::Red_Channel1_Slider1_Status1, Panel::Red_Channel1_Slider1_Status2, Panel::Red_Channel1_Slider1_Status3, Panel::Red_Channel1_Slider1_Status4, Panel::Red_Channel1_Slider1_Status5},
                                {Panel::Red_Channel2_Slider2_Status1, Panel::Red_Channel2_Slider2_Status2, Panel::Red_Channel2_Slider2_Status3, Panel::Red_Channel2_Slider2_Status4, Panel::Red_Channel2_Slider2_Status5},
                                {Panel::Red_Channel3_Slider3_Status1, Panel::Red_Channel3_Slider3_Status2, Panel::Red_Channel3_Slider3_Status3, Panel::Red_Channel3_Slider3_Status4, Panel::Red_Channel3_Slider3_Status5},
                                {Panel::Red_Channel4_Slider4_Status1, Panel::Red_Channel4_Slider4_Status2, Panel::Red_Channel4_Slider4_Status3, Panel::Red_Channel4_Slider4_Status4, Panel::Red_Channel4_Slider4_Status5},
                                {Panel::Red_Channel5_Slider5_Status1, Panel::Red_Channel5_Slider5_Status2, Panel::Red_Channel5_Slider5_Status3, Panel::Red_Channel5_Slider5_Status4, Panel::Red_Channel5_Slider5_Status5},
                                {Panel::Red_Channel6_Slider6_Status1, Panel::Red_Channel6_Slider6_Status2, Panel::Red_Channel6_Slider6_Status3, Panel::Red_Channel6_Slider6_Status4, Panel::Red_Channel6_Slider6_Status5},
                                {Panel::Red_Channel7_Slider7_Status1, Panel::Red_Channel7_Slider7_Status2, Panel::Red_Channel7_Slider7_Status3, Panel::Red_Channel7_Slider7_Status4, Panel::Red_Channel7_Slider7_Status5},
                                {Panel::Red_Channel8_Slider8_Status1, Panel::Red_Channel8_Slider8_Status2, Panel::Red_Channel8_Slider8_Status3, Panel::Red_Channel8_Slider8_Status4, Panel::Red_Channel8_Slider8_Status5}});

   sliderOutputList.append({Panel::Channel1_Slider1_Output, Panel::Channel2_Slider2_Output, Panel::Channel3_Slider3_Output, Panel::Channel4_Slider4_Output, Panel::Channel5_Slider5_Output, Panel::Channel6_Slider6_Output, Panel::Channel7_Slider7_Output, Panel::Channel8_Slider8_Output});

   for (uint8_t index = 0; index < 8; index++)
   {
      lightMeterListCV[index]->setMaxValue(127);
      lightMeterListSlider[index]->setMaxValue(127);
   }

   connectionLight.assign(Panel::Red_Connect);
   connectToMidiDevice();
}

VCMCReceiver::~VCMCReceiver()
{
}

void VCMCReceiver::process(const ProcessArgs& args)
{
   if (connectTrigger.process(params[Panel::Connect].getValue() > 3.0))
      connectToMidiDevice();

   midi::Message msg;
   while (midiInput.tryPop(&msg, args.frame))
   {
      processMessage(msg);
   }

   if (doNotAdvanceTempo)
      doNotAdvanceTempo = false;
   else
      tempo.advance(args.sampleRate);

   bpm = tempo.getBeatsPerMinute();

   outputs[Panel::Clock].setVoltage(clockTick.process(args.sampleTime) ? 10.f : 0.f);
   outputs[Panel::Reset].setVoltage(clockReset.process(args.sampleTime) ? 10.f : 0.f);

   for (uint8_t index = 0; index < 8; index++)
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

      lightMeterListCV[index]->setMeter(cvValues[index]);
      const float cvVoltage = ccValueToVoltage(cvValues[index]);
      cvOutputList[index]->setVoltage(cvVoltage);

      lightMeterListSlider[index]->setMeter(sliderValues[index]);
      const float sliderVoltage = ccValueToVoltage(sliderValues[index]);
      sliderOutputList[index]->setVoltage(sliderVoltage);
   }
}
void VCMCReceiver::processMessage(const midi::Message& msg)
{

   const bool isSystemEvent = (0xF0 == (msg.bytes[0] & 0xF0));
   if (!isSystemEvent)
   {
      const Midi::Event event = static_cast<Midi::Event>(msg.bytes[0] & 0xF0);
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
   else
   {
      const Midi::Event event = static_cast<Midi::Event>(msg.bytes[0]);

      if (Midi::Event::Clock == event)
      {
         if (0 == midiTickCounter)
         {
            tempo.clockTick();
            clockTick.trigger();
            doNotAdvanceTempo = true;
         }

         midiTickCounter++;
         if (6 == midiTickCounter)
            midiTickCounter = 0;
      }
      else if (Midi::Event::Start == event)
      {
         midiTickCounter = 0;
         tempo.clockReset();
         clockReset.trigger();
         doNotAdvanceTempo = true;
      }
   }
}

void VCMCReceiver::connectToMidiDevice()
{
   static const std::string targetDeviceName = "VCMC";
   midiInput.reset();
   connectionLight.setColor(SchweineSystem::Color{255, 0, 0});

   for (const int& deviceId : midiInput.getDeviceIds())
   {
      const std::string deviceName = midiInput.getDeviceName(deviceId);
      if (targetDeviceName == deviceName)
      {
         std::cout << "connected to " << deviceName << " @ " << deviceId << std::endl;
         midiInput.setDeviceId(deviceId);
         connectionLight.setColor(SchweineSystem::Color{0, 255, 0});
         return;
      }
   }
}

json_t* VCMCReceiver::dataToJson()
{
   json_t* rootJson = json_object();
   for (uint8_t index = 0; index < 8; index++)
   {
      const std::string gateKey = "gate" + std::to_string(index);
      json_object_set_new(rootJson, gateKey.c_str(), json_boolean(gates[index]));

      const std::string cvKey = "cv" + std::to_string(index);
      json_object_set_new(rootJson, cvKey.c_str(), json_integer(cvValues[index]));

      const std::string sliderKey = "slider" + std::to_string(index);
      json_object_set_new(rootJson, sliderKey.c_str(), json_integer(sliderValues[index]));
   }

   return rootJson;
}

void VCMCReceiver::dataFromJson(json_t* rootJson)
{
   for (uint8_t index = 0; index < 8; index++)
   {
      const std::string gateKey = "gate" + std::to_string(index);
      json_t* gateJson = json_object_get(rootJson, gateKey.c_str());
      if (gateJson)
         gates[index] = json_boolean_value(gateJson);

      const std::string cvKey = "cv" + std::to_string(index);
      json_t* cvJson = json_object_get(rootJson, cvKey.c_str());
      if (cvJson)
         cvValues[index] = json_integer_value(cvJson);

      const std::string sliderKey = "slider" + std::to_string(index);
      json_t* sliderJson = json_object_get(rootJson, sliderKey.c_str());
      if (sliderJson)
         sliderValues[index] = json_integer_value(sliderJson);
   }
}

VCMCReceiverWidget::VCMCReceiverWidget(VCMCReceiver* module)
   : ModuleWidget()
{
   SvgPanel* mainPanel = setup(module);
   (void)mainPanel;

   SchweineSystem::LCDDisplay* bpmDisplay = new SchweineSystem::LCDDisplay();
   bpmDisplay->setPosition(90, 297);
   if (module) // will be zero in module browser
      bpmDisplay->setup(&(module->bpm), 3);
   bpmDisplay->setDigitColor(SchweineSystem::Color{0, 255, 255});

   addChild(bpmDisplay);
}

Model* modelVCMCReceiver = SchweineSystem::Master::the()->addModule<VCMCReceiver, VCMCReceiverWidget>("VCMCReceiver");

