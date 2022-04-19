#include "TimeLordServer.h"
#include "TimeLordServerPanel.h"

#include <Midi/MidiCommon.h>
#include <Tools/SevenBit.h>

#include "SchweineSystemMaster.h"

const std::string TimeLordServer::keys = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

TimeLordServer::TimeLordServer()
   : Module()
   , midiInput()
   , ramps{}
   , clockTrigger()
   , resetTrigger()
   , tempo()
   , cvMapper(0.0, 255.0, 0.0, 10.0)
   , lightMeterList(lights)
   , outputList(outputs)
   , loadLightList(lights)
   , loadState(LoadState::Ready)
{
   setup();

   lightMeterList.append({{Panel::Red_Channel1_Status1, Panel::Red_Channel1_Status2, Panel::Red_Channel1_Status3, Panel::Red_Channel1_Status4, Panel::Red_Channel1_Status5},
                          {Panel::Red_Channel2_Status1, Panel::Red_Channel2_Status2, Panel::Red_Channel2_Status3, Panel::Red_Channel2_Status4, Panel::Red_Channel2_Status5},
                          {Panel::Red_Channel3_Status1, Panel::Red_Channel3_Status2, Panel::Red_Channel3_Status3, Panel::Red_Channel3_Status4, Panel::Red_Channel3_Status5},
                          {Panel::Red_Channel4_Status1, Panel::Red_Channel4_Status2, Panel::Red_Channel4_Status3, Panel::Red_Channel4_Status4, Panel::Red_Channel4_Status5},
                          {Panel::Red_Channel5_Status1, Panel::Red_Channel5_Status2, Panel::Red_Channel5_Status3, Panel::Red_Channel5_Status4, Panel::Red_Channel5_Status5},
                          {Panel::Red_Channel6_Status1, Panel::Red_Channel6_Status2, Panel::Red_Channel6_Status3, Panel::Red_Channel6_Status4, Panel::Red_Channel6_Status5},
                          {Panel::Red_Channel7_Status1, Panel::Red_Channel7_Status2, Panel::Red_Channel7_Status3, Panel::Red_Channel7_Status4, Panel::Red_Channel7_Status5},
                          {Panel::Red_Channel8_Status1, Panel::Red_Channel8_Status2, Panel::Red_Channel8_Status3, Panel::Red_Channel8_Status4, Panel::Red_Channel8_Status5},
                          {Panel::Red_Channel9_Status1, Panel::Red_Channel9_Status2, Panel::Red_Channel9_Status3, Panel::Red_Channel9_Status4, Panel::Red_Channel9_Status5},
                          {Panel::Red_Channel10_Status1, Panel::Red_Channel10_Status2, Panel::Red_Channel10_Status3, Panel::Red_Channel10_Status4, Panel::Red_Channel10_Status5},
                          {Panel::Red_Channel11_Status1, Panel::Red_Channel11_Status2, Panel::Red_Channel11_Status3, Panel::Red_Channel11_Status4, Panel::Red_Channel11_Status5},
                          {Panel::Red_Channel12_Status1, Panel::Red_Channel12_Status2, Panel::Red_Channel12_Status3, Panel::Red_Channel12_Status4, Panel::Red_Channel12_Status5},
                          {Panel::Red_Channel13_Status1, Panel::Red_Channel13_Status2, Panel::Red_Channel13_Status3, Panel::Red_Channel13_Status4, Panel::Red_Channel13_Status5},
                          {Panel::Red_Channel14_Status1, Panel::Red_Channel14_Status2, Panel::Red_Channel14_Status3, Panel::Red_Channel14_Status4, Panel::Red_Channel14_Status5},
                          {Panel::Red_Channel15_Status1, Panel::Red_Channel15_Status2, Panel::Red_Channel15_Status3, Panel::Red_Channel15_Status4, Panel::Red_Channel15_Status5},
                          {Panel::Red_Channel16_Status1, Panel::Red_Channel16_Status2, Panel::Red_Channel16_Status3, Panel::Red_Channel16_Status4, Panel::Red_Channel16_Status5}});

   for (uint8_t rampIndex = 0; rampIndex < 16; rampIndex++)
      lightMeterList[rampIndex]->setMaxValue(255);

   outputList.append({Panel::Channel1_Output,
                      Panel::Channel2_Output,
                      Panel::Channel3_Output,
                      Panel::Channel4_Output,
                      Panel::Channel5_Output,
                      Panel::Channel6_Output,
                      Panel::Channel7_Output,
                      Panel::Channel8_Output,
                      Panel::Channel9_Output,
                      Panel::Channel10_Output,
                      Panel::Channel11_Output,
                      Panel::Channel12_Output,
                      Panel::Channel13_Output,
                      Panel::Channel14_Output,
                      Panel::Channel15_Output,
                      Panel::Channel16_Output});

   loadLightList.append({Panel::Red_LoadA, Panel::Red_LoadB});

   midiInput.openVirtualPort("TimeLordServer");

   midiInput.setErrorCallback(&TimeLordServer::midiError);
   midiInput.setCallback(&TimeLordServer::midiReceive, this);
   midiInput.ignoreTypes(false, false, false); // do not ignore anything
}

TimeLordServer::~TimeLordServer()
{
   midiInput.closePort();
}

void TimeLordServer::process(const ProcessArgs& args)
{
   bool isClock = clockTrigger.process(inputs[Panel::Clock].getVoltage() > 3.0);
   bool isReset = resetTrigger.process(inputs[Panel::Reset].getVoltage() > 3.0);

   if (isReset)
      tempo.clockReset();
   else if (isClock)
      tempo.clockTick();
   else
      tempo.advance(args.sampleRate);

   for (uint8_t rampIndex = 0; rampIndex < 16; rampIndex++)
   {
      PolyRamp* polyRamp = &ramps[rampIndex];

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

   for (const uint8_t loadLightIndex : {0, 1})
   {
      loadLightList[loadLightIndex]->setColor(SchweineSystem::Color{50, 50, 0});
   }
}

void TimeLordServer::dataFromInput(const Bytes& message)
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
      loadState = LoadState::Receive;
   }
   else if (Midi::ControllerMessage::RememberApply == controllerMessage)
   {
      const Bytes data = SevenBit::decode(buffer);
      buffer.clear();

      for (uint8_t byte : data)
         std::cout << (char)byte;
      std::cout << std::endl;

      json_error_t error;
      const char* cBuffer = (const char*)data.data();
      json_t* rootJson = json_loadb(cBuffer, data.size(), 0, &error);

      dataFromJson(rootJson);
      loadState = LoadState::Apply;
   }
}

void TimeLordServer::midiReceive(double timeStamp, std::vector<unsigned char>* message, void* userData)
{
   (void)timeStamp;

   if (!message || !userData)
      return;

   TimeLordServer* me = reinterpret_cast<TimeLordServer*>(userData);
   if (!me)
      return;

   static Bytes buffer;
   auto maybeProcessBuffer = [&]()
   {
      if (0 == buffer.size())
         return;

      me->dataFromInput(buffer);
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

void TimeLordServer::midiError(RtMidiError::Type type, const std::string& errorText, void* userData)
{
   (void)userData;
   std::cout << "MIDI ERROR: " << type << ",  " << errorText << std::endl;
}

json_t* TimeLordServer::dataToJson()
{
   json_t* rootJson = json_object();
   for (uint8_t rampIndex = 0; rampIndex < 16; rampIndex++)
   {
      PolyRamp* polyRamp = &ramps[rampIndex];

      json_t* rampJson = json_object();

      const uint32_t length = polyRamp->getLength();
      json_object_set_new(rampJson, "length", json_integer(length));

      const uint8_t stepSize = static_cast<uint8_t>(polyRamp->getStepSize());
      json_object_set_new(rampJson, "stepSize", json_integer(stepSize));

      const bool loop = polyRamp->isLooping();
      json_object_set_new(rampJson, "loop", json_boolean(loop));

      json_t* stagesArrayJson = json_array();
      for (uint8_t stageIndex = 0; stageIndex < polyRamp->stageCount(); stageIndex++)
      {
         json_t* stageJson = json_object();

         const uint8_t stageLength = polyRamp->getStageLength(stageIndex);
         json_object_set_new(stageJson, "length", json_integer(stageLength));

         const uint8_t startHeight = polyRamp->getStageStartHeight(stageIndex);
         json_object_set_new(stageJson, "startHeight", json_integer(startHeight));

         json_array_append_new(stagesArrayJson, stageJson);
      }
      json_object_set_new(rampJson, "stages", stagesArrayJson);

      json_object_set_new(rootJson, keys.substr(rampIndex, 1).c_str(), rampJson);
   }
   return rootJson;
}

void TimeLordServer::dataFromJson(json_t* rootJson)
{
   for (uint8_t rampIndex = 0; rampIndex < 16; rampIndex++)
   {
      PolyRamp* polyRamp = &ramps[rampIndex];
      polyRamp->clear();

      json_t* rampJson = json_object_get(rootJson, keys.substr(rampIndex, 1).c_str());
      if (!rampJson)
         continue;

      json_t* lengthJson = json_object_get(rampJson, "length");
      if (lengthJson)
      {
         const uint32_t length = json_integer_value(lengthJson);
         polyRamp->setLength(length, true);
      }

      json_t* stepSizeJson = json_object_get(rampJson, "stepSize");
      if (stepSizeJson)
      {
         const Tempo::Division stepSize = static_cast<Tempo::Division>(json_integer_value(stepSizeJson));
         polyRamp->setStepSize(stepSize);
      }

      json_t* loopJson = json_object_get(rampJson, "loop");
      if (loopJson)
      {
         const bool loop = json_boolean_value(loopJson);
         polyRamp->setLooping(loop);
      }

      json_t* stagesArrayObject = json_object_get(rampJson, "stages");
      if (!stagesArrayObject)
         continue;

      const uint8_t stageCount = json_array_size(stagesArrayObject);
      polyRamp->addStage(0, stageCount);

      for (uint8_t stageIndex = 0; stageIndex < stageCount; stageIndex++)
      {
         json_t* stageJson = json_array_get(stagesArrayObject, stageIndex);

         json_t* stageLengthJson = json_object_get(stageJson, "length");
         if (stageLengthJson)
         {
            const uint8_t stageLength = json_integer_value(stageLengthJson);
            polyRamp->setStageLength(stageIndex, stageLength);
         }

         json_t* stageHeightJson = json_object_get(stageJson, "startHeight");
         if (stageHeightJson)
         {
            const uint8_t startHeight = json_integer_value(stageHeightJson);
            polyRamp->setStageStartHeight(stageIndex, startHeight);
         }
      }
   }
}

TimeLordServerWidget::TimeLordServerWidget(TimeLordServer* module)
   : ModuleWidget()
{
   SvgPanel* mainPanel = setup(module);
   (void)mainPanel;
}

Model* modelTimeLordServer = SchweineSystem::Master::the()->addModule<TimeLordServer, TimeLordServerWidget>("TimeLordServer");

