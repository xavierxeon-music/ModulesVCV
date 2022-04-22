#include "TimeLord.h"
#include "TimeLordPanel.h"

#include <Midi/MidiCommon.h>
#include <Tools/SevenBit.h>

#include "SchweineSystemJson.h"
#include "SchweineSystemLCDDisplay.h"
#include "SchweineSystemMaster.h"

// receiver

TimeLord::Majordomo* TimeLord::Majordomo::me = nullptr;

void TimeLord::Majordomo::hello(TimeLord* server)
{
   if (!me)
      me = new Majordomo();

   if (0 == me->instanceList.size())
      me->start();

   me->instanceList.push_back(server);
}

void TimeLord::Majordomo::bye(TimeLord* server)
{
   if (!me)
      me = new Majordomo();

   std::vector<TimeLord*>::iterator it = std::find(me->instanceList.begin(), me->instanceList.end(), server);
   if (it != me->instanceList.end())
      me->instanceList.erase(it);

   if (0 == me->instanceList.size())
      me->stop();
}

TimeLord::Majordomo::Majordomo()
   : midiInput()
   , instanceList()
{
}

void TimeLord::Majordomo::start()
{
   midiInput.openVirtualPort("TimeLord");

   midiInput.setErrorCallback(&Majordomo::midiError);
   midiInput.setCallback(&Majordomo::midiReceive, this);
   midiInput.ignoreTypes(false, false, false); // do not ignore anything
}

void TimeLord::Majordomo::stop()
{
   midiInput.closePort();
}

void TimeLord::Majordomo::midiReceive(double timeStamp, std::vector<unsigned char>* message, void* userData)
{
   (void)timeStamp;

   if (me != userData)
      return;

   if (!message)
      return;

   static Bytes buffer;
   auto maybeProcessBuffer = [&]()
   {
      if (0 == buffer.size())
         return;

      for (TimeLord* server : me->instanceList)
         server->dataFromMidiInput(buffer);
      buffer.clear();
   };

   static const uint8_t mask = 0x80;
   for (const uint8_t byte : *message)
   {
      const uint8_t test = byte & mask;
      if (test == mask) // new message start
         maybeProcessBuffer();

      buffer.push_back(byte);
   }
   maybeProcessBuffer();
}

void TimeLord::Majordomo::midiError(RtMidiError::Type type, const std::string& errorText, void* userData)
{
   if (me != userData)
      return;

   std::cout << "MIDI ERROR: " << type << ",  " << errorText << std::endl;
}

// server

const std::string TimeLord::keys = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

TimeLord::TimeLord()
   : Module()
   , ramps{}
   , clockTrigger()
   , resetTrigger()
   , tempo()
   , cvMapper(0.0, 255.0, 0.0, 10.0)
   , lightMeterList(lights)
   , outputList(outputs)
   , rampDisplayList(this)
   , displayMode(StageIndex)
   , displayModeLightList(lights)
   , displayTrigger()
   , modeColors{SchweineSystem::Color{255, 0, 0}, SchweineSystem::Color{100, 100, 255}, SchweineSystem::Color{0, 255, 0}}
   , bankDisplay(this, Panel::Value_Bank)
   , bankIndex(0)
   , bankTrigger()
   , receiveState(false)
   , applyPulse()
{
   setup();
   Majordomo::hello(this);

   lightMeterList.append({{Panel::Red_Channel1_Status1, Panel::Red_Channel1_Status2, Panel::Red_Channel1_Status3, Panel::Red_Channel1_Status4, Panel::Red_Channel1_Status5},
                          {Panel::Red_Channel2_Status1, Panel::Red_Channel2_Status2, Panel::Red_Channel2_Status3, Panel::Red_Channel2_Status4, Panel::Red_Channel2_Status5},
                          {Panel::Red_Channel3_Status1, Panel::Red_Channel3_Status2, Panel::Red_Channel3_Status3, Panel::Red_Channel3_Status4, Panel::Red_Channel3_Status5},
                          {Panel::Red_Channel4_Status1, Panel::Red_Channel4_Status2, Panel::Red_Channel4_Status3, Panel::Red_Channel4_Status4, Panel::Red_Channel4_Status5},
                          {Panel::Red_Channel5_Status1, Panel::Red_Channel5_Status2, Panel::Red_Channel5_Status3, Panel::Red_Channel5_Status4, Panel::Red_Channel5_Status5},
                          {Panel::Red_Channel6_Status1, Panel::Red_Channel6_Status2, Panel::Red_Channel6_Status3, Panel::Red_Channel6_Status4, Panel::Red_Channel6_Status5},
                          {Panel::Red_Channel7_Status1, Panel::Red_Channel7_Status2, Panel::Red_Channel7_Status3, Panel::Red_Channel7_Status4, Panel::Red_Channel7_Status5},
                          {Panel::Red_Channel8_Status1, Panel::Red_Channel8_Status2, Panel::Red_Channel8_Status3, Panel::Red_Channel8_Status4, Panel::Red_Channel8_Status5}});

   outputList.append({Panel::Channel1_Output,
                      Panel::Channel2_Output,
                      Panel::Channel3_Output,
                      Panel::Channel4_Output,
                      Panel::Channel5_Output,
                      Panel::Channel6_Output,
                      Panel::Channel7_Output,
                      Panel::Channel8_Output});

   rampDisplayList.append({Panel::Value_Channel1_Display,
                           Panel::Value_Channel2_Display,
                           Panel::Value_Channel3_Display,
                           Panel::Value_Channel4_Display,
                           Panel::Value_Channel5_Display,
                           Panel::Value_Channel6_Display,
                           Panel::Value_Channel7_Display,
                           Panel::Value_Channel8_Display});

   displayModeLightList.append({Panel::Red_Division, Panel::Red_Stage, Panel::Red_Current});
   for (uint8_t modeIndex = 0; modeIndex < 3; modeIndex++)
   {
      displayModeLightList[modeIndex]->setDefaultColor(modeColors[modeIndex]);
   }

   for (uint8_t rampIndex = 0; rampIndex < 8; rampIndex++)
   {
      lightMeterList[rampIndex]->setMaxValue(255);
   }
}

TimeLord::~TimeLord()
{
   Majordomo::bye(this);
}

void TimeLord::process(const ProcessArgs& args)
{
   bool isClock = clockTrigger.process(inputs[Panel::Clock].getVoltage() > 3.0);
   bool isReset = resetTrigger.process(inputs[Panel::Reset].getVoltage() > 3.0);

   if (isReset)
      tempo.clockReset();
   else if (isClock)
      tempo.clockTick();
   else
      tempo.advance(args.sampleRate);

   if (bankTrigger.process(params[Panel::BankUp].getValue()))
   {
      bankIndex++;
      if (bankIndex >= 10)
         bankIndex = 0;
   }

   if (receiveState)
      bankDisplay.setColor(SchweineSystem::Color{255, 0, 0});
   else if (applyPulse.process(args.sampleTime))
      bankDisplay.setColor(SchweineSystem::Color{0, 255, 0});
   else
      bankDisplay.setColor(SchweineSystem::Color{255, 255, 0});

   bankDisplay.setValue(bankIndex);

   if (displayTrigger.process(params[Panel::Mode].getValue()))
   {
      if (Division == displayMode)
         displayMode = StageCount;
      else if (StageCount == displayMode)
         displayMode = StageIndex;
      else
         displayMode = Division;
   }

   for (uint8_t modeIndex = 0; modeIndex < 3; modeIndex++)
   {
      if (modeIndex == displayMode)
         displayModeLightList[modeIndex]->setOn();
      else
         displayModeLightList[modeIndex]->setOff();
   }

   for (uint8_t rampIndex = 0; rampIndex < 8; rampIndex++)
   {
      PolyRamp* polyRamp = &ramps[rampIndex];

      rampDisplayList[rampIndex]->setColor(modeColors[displayMode]);
      if (Division == displayMode)
         rampDisplayList[rampIndex]->setValue(polyRamp->getStepSize());
      else if (StageCount == displayMode)
         rampDisplayList[rampIndex]->setValue(polyRamp->getLength());
      else
         rampDisplayList[rampIndex]->setValue(polyRamp->getCurrentStageIndex());

      if (isReset)
         polyRamp->clockReset();
      else if (isClock)
         polyRamp->clockTick();

      const float perentageToNextTick = tempo.getPercentage(Tempo::Division::Sixteenth);
      const float value = polyRamp->getCurrentValue(perentageToNextTick);
      lightMeterList[rampIndex]->setMeter(value);

      const float voltage = cvMapper(value);
      outputList[rampIndex]->setVoltage(voltage);
   }
}

void TimeLord::dataFromMidiInput(const Bytes& message)
{
   static Bytes buffer;

   const bool isSystemEvent = (0xF0 == (message[0] & 0xF0));
   if (isSystemEvent)
      return;

   const Midi::Event event = static_cast<Midi::Event>(message[0] & 0xF0);
   const Midi::Channel channel = 1 + (message[0] & 0x0F);
   if (11 != channel)
      return;

   if (Midi::Event::ControlChange != event)
      return;

   const Midi::ControllerMessage controllerMessage = static_cast<Midi::ControllerMessage>(message[1]);

   if (Midi::ControllerMessage::RememberBlock == controllerMessage)
   {
      const uint8_t value = message[2];
      buffer << value;
      receiveState = true;
   }
   else if (Midi::ControllerMessage::RememberApply == controllerMessage)
   {
      const Bytes data = SevenBit::decode(buffer);
      buffer.clear();

      receiveState = false;

      const uint8_t value = message[2];
      if (value != bankIndex)
         return;

      json_error_t error;
      const char* cBuffer = (const char*)data.data();
      json_t* rootJson = json_loadb(cBuffer, data.size(), 0, &error);

      dataFromJson(rootJson);
      applyPulse.trigger(2.0);
   }
}

json_t* TimeLord::dataToJson()
{
   using namespace SchweineSystem::Json;

   Object rootObject;
   rootObject.set("bank", bankIndex);
   rootObject.set("mode", static_cast<uint8_t>(displayMode));

   for (uint8_t rampIndex = 0; rampIndex < 8; rampIndex++)
   {
      PolyRamp* polyRamp = &ramps[rampIndex];

      Object rampObject;

      const uint32_t length = polyRamp->getLength();
      rampObject.set("length", json_integer(length));

      const uint8_t stepSize = static_cast<uint8_t>(polyRamp->getStepSize());
      rampObject.set("stepSize", json_integer(stepSize));

      const bool loop = polyRamp->isLooping();
      rampObject.set("loop", json_boolean(loop));

      Array stagesArray;
      for (uint8_t stageIndex = 0; stageIndex < polyRamp->stageCount(); stageIndex++)
      {
         Object stageObject;

         const uint8_t stageLength = polyRamp->getStageLength(stageIndex);
         stageObject.set("length", json_integer(stageLength));

         const uint8_t startHeight = polyRamp->getStageStartHeight(stageIndex);
         stageObject.set("startHeight", json_integer(startHeight));

         stagesArray.append(stageObject);
      }
      rampObject.set("stages", stagesArray);

      rootObject.set(keys.substr(rampIndex, 1), rampObject);
   }

   return rootObject.toJson();
}

void TimeLord::dataFromJson(json_t* rootJson)
{
   using namespace SchweineSystem::Json;

   Object rootObject(rootJson);
   bankIndex = rootObject.get("bank").toInt();
   displayMode = static_cast<DisplayMode>(rootObject.get("mode").toInt());

   for (uint8_t rampIndex = 0; rampIndex < 8; rampIndex++)
   {
      PolyRamp* polyRamp = &ramps[rampIndex];
      polyRamp->clear();

      Object rampObject = rootObject.get(keys.substr(rampIndex, 1)).toObject();

      const uint32_t length = rampObject.get("length").toInt();
      polyRamp->setLength(length);

      const uint8_t stepSize = rampObject.get("stepSize").toInt();
      polyRamp->setStepSize(static_cast<Tempo::Division>(stepSize));

      const bool loop = rampObject.get("loop").toBool();
      polyRamp->setLooping(loop);

      Array stagesArray = rampObject.get("stages").toArray();
      const uint8_t stageCount = stagesArray.size();
      polyRamp->addStage(0, stageCount);

      for (uint8_t stageIndex = 0; stageIndex < stageCount; stageIndex++)
      {
         Object stageObject = stagesArray.get(stageIndex).toObject();

         const uint8_t stageLength = stageObject.get("length").toInt();
         polyRamp->setStageLength(stageIndex, stageLength);

         const uint8_t startHeight = stageObject.get("startHeight").toInt();
         polyRamp->setStageStartHeight(stageIndex, startHeight);
      }
   }
}

TimeLordWidget::TimeLordWidget(TimeLord* module)
   : ModuleWidget()
{
   SvgPanel* mainPanel = setup(module);
   (void)mainPanel;
}

Model* modelTimeLord = SchweineSystem::Master::the()->addModule<TimeLord, TimeLordWidget>("TimeLord");
