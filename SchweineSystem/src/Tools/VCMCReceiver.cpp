#include "VCMCReceiver.h"
#include "VCMCReceiverPanel.h"

#include <Midi/MidiCommon.h>
#include <Music/Note.h>

#include "SchweineSystemLCDDisplay.h"
#include "SchweineSystemMaster.h"

VCMCReceiver::VCMCReceiver()
   : Module()
   , bpm(12)
   , lightMeterListCV(lights)
   , lightMeterListSlider(lights)
   , lightListGate(lights)
   , connectionLight(lights)
   , midiInput()
   , midiTickCounter(0)
   , doNotAdvanceTempo(false)
   , tempo()
   , clockTick()
   , clockReset()
{
   setup();

   lightMeterListCV.append({{Panel::Red_Channel8_CV8_Status1, Panel::Red_Channel8_CV8_Status2, Panel::Red_Channel8_CV8_Status3, Panel::Red_Channel8_CV8_Status4, Panel::Red_Channel8_CV8_Status5},
                            {Panel::Red_Channel7_CV7_Status1, Panel::Red_Channel7_CV7_Status2, Panel::Red_Channel7_CV7_Status3, Panel::Red_Channel7_CV7_Status4, Panel::Red_Channel7_CV7_Status5},
                            {Panel::Red_Channel6_CV6_Status1, Panel::Red_Channel6_CV6_Status2, Panel::Red_Channel6_CV6_Status3, Panel::Red_Channel6_CV6_Status4, Panel::Red_Channel6_CV6_Status5},
                            {Panel::Red_Channel5_CV5_Status1, Panel::Red_Channel5_CV5_Status2, Panel::Red_Channel5_CV5_Status3, Panel::Red_Channel5_CV5_Status4, Panel::Red_Channel5_CV5_Status5},
                            {Panel::Red_Channel4_CV4_Status1, Panel::Red_Channel4_CV4_Status2, Panel::Red_Channel4_CV4_Status3, Panel::Red_Channel4_CV4_Status4, Panel::Red_Channel4_CV4_Status5},
                            {Panel::Red_Channel3_CV3_Status1, Panel::Red_Channel3_CV3_Status2, Panel::Red_Channel3_CV3_Status3, Panel::Red_Channel3_CV3_Status4, Panel::Red_Channel3_CV3_Status5},
                            {Panel::Red_Channel2_CV2_Status1, Panel::Red_Channel2_CV2_Status2, Panel::Red_Channel2_CV2_Status3, Panel::Red_Channel2_CV2_Status4, Panel::Red_Channel2_CV2_Status5},
                            {Panel::Red_Channel1_CV1_Status1, Panel::Red_Channel1_CV1_Status2, Panel::Red_Channel1_CV1_Status3, Panel::Red_Channel1_CV1_Status4, Panel::Red_Channel1_CV1_Status5}});

   lightMeterListSlider.append({{Panel::Red_Channel8_Slider8_Status1, Panel::Red_Channel8_Slider8_Status2, Panel::Red_Channel8_Slider8_Status3, Panel::Red_Channel8_Slider8_Status4, Panel::Red_Channel8_Slider8_Status5},
                                {Panel::Red_Channel7_Slider7_Status1, Panel::Red_Channel7_Slider7_Status2, Panel::Red_Channel7_Slider7_Status3, Panel::Red_Channel7_Slider7_Status4, Panel::Red_Channel7_Slider7_Status5},
                                {Panel::Red_Channel6_Slider6_Status1, Panel::Red_Channel6_Slider6_Status2, Panel::Red_Channel6_Slider6_Status3, Panel::Red_Channel6_Slider6_Status4, Panel::Red_Channel6_Slider6_Status5},
                                {Panel::Red_Channel5_Slider5_Status1, Panel::Red_Channel5_Slider5_Status2, Panel::Red_Channel5_Slider5_Status3, Panel::Red_Channel5_Slider5_Status4, Panel::Red_Channel5_Slider5_Status5},
                                {Panel::Red_Channel4_Slider4_Status1, Panel::Red_Channel4_Slider4_Status2, Panel::Red_Channel4_Slider4_Status3, Panel::Red_Channel4_Slider4_Status4, Panel::Red_Channel4_Slider4_Status5},
                                {Panel::Red_Channel3_Slider3_Status1, Panel::Red_Channel3_Slider3_Status2, Panel::Red_Channel3_Slider3_Status3, Panel::Red_Channel3_Slider3_Status4, Panel::Red_Channel3_Slider3_Status5},
                                {Panel::Red_Channel2_Slider2_Status1, Panel::Red_Channel2_Slider2_Status2, Panel::Red_Channel2_Slider2_Status3, Panel::Red_Channel2_Slider2_Status4, Panel::Red_Channel2_Slider2_Status5},
                                {Panel::Red_Channel1_Slider1_Status1, Panel::Red_Channel1_Slider1_Status2, Panel::Red_Channel1_Slider1_Status3, Panel::Red_Channel1_Slider1_Status4, Panel::Red_Channel1_Slider1_Status5}});

   lightListGate.append({Panel::Red_Channel8_Gate8_Status1, Panel::Red_Channel7_Gate7_Status1, Panel::Red_Channel6_Gate6_Status1, Panel::Red_Channel5_Gate5_Status1, Panel::Red_Channel4_Gate4_Status1, Panel::Red_Channel3_Gate3_Status1, Panel::Red_Channel2_Gate2_Status1, Panel::Red_Channel1_Gate1_Status1});

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
}
void VCMCReceiver::processMessage(const midi::Message& msg)
{
   //std::cout << msg.getFrame() << " " << msg.toString().c_str() << std::endl;

   const bool isSystemEvent = (0xF0 == (msg.bytes[0] & 0xF0));
   if (!isSystemEvent)
   {
      const Midi::Event event = static_cast<Midi::Event>(msg.bytes[0] & 0xF0);
      const Midi::Channel channel = 1 + (msg.bytes[0] & 0x0F);

      if (Midi::Event::NoteOn == event)
      {
         const Note note = Note::fromMidi(msg.bytes[1]);
         const Midi::Velocity velocity = msg.bytes[2];

         // TODO
      }
      else if (Midi::Event::NoteOff == event)
      {
         const Note note = Note::fromMidi(msg.bytes[1]);

         // TODO
      }
      else if (Midi::Event::ControlChange == event)
      {
         const Midi::ControllerMessage controllerMessage = static_cast<Midi::ControllerMessage>(msg.bytes[1]);
         const uint8_t value = msg.bytes[2];

         // TODO
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
   static const std::string targetDeviceName = "Metropolix";
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

