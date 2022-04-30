#include "TimeLord.h"
#include "TimeLordPanel.h"

#include <Midi/MidiCommon.h>
#include <Tools/SevenBit.h>

#include <SchweineSystemMaster.h>

// majordomo

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

      for (TimeLord* lord : me->instanceList)
         lord->dataFromMidiInput(buffer);
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

// lord

const std::string TimeLord::keys = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

TimeLord::TimeLord()
   : SchweineSystem::Module()
   , ramps{}
   , midiBuffer()
   , clockTrigger()
   , resetTrigger()
   , tempo()
   , cvMapper(0.0, 255.0, 0.0, 10.0)
   , lightMeterList(this)
   , outputList(outputs)
   , displayMode(StageIndex)
   , displayTrigger()
   , bankIndex(0)
   , bankTrigger()
   , dataReceive(false)
   , dataApply(false)
   , dataAppliedPulse()
   , displayController(this, Panel::Pixels_Display)
{
   setup();
   Majordomo::hello(this);

   lightMeterList.append({Panel::Value_Channel1_Strip,
                          Panel::Value_Channel2_Strip,
                          Panel::Value_Channel3_Strip,
                          Panel::Value_Channel4_Strip,
                          Panel::Value_Channel5_Strip,
                          Panel::Value_Channel6_Strip,
                          Panel::Value_Channel7_Strip,
                          Panel::Value_Channel8_Strip});

   outputList.append({Panel::Channel1_Output,
                      Panel::Channel2_Output,
                      Panel::Channel3_Output,
                      Panel::Channel4_Output,
                      Panel::Channel5_Output,
                      Panel::Channel6_Output,
                      Panel::Channel7_Output,
                      Panel::Channel8_Output});

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

   if (bankTrigger.process(params[Panel::Bank_Up].getValue()))
   {
      bankIndex++;
      if (bankIndex >= 10)
         bankIndex = 0;
   }

   dataApply = dataAppliedPulse.process(args.sampleTime);

   if (displayTrigger.process(params[Panel::Mode].getValue()))
   {
      if (Division == displayMode)
         displayMode = Length;
      else if (Length == displayMode)
         displayMode = StageCount;
      else if (StageCount == displayMode)
         displayMode = StageIndex;
      else
         displayMode = Division;
   }

   for (uint8_t rampIndex = 0; rampIndex < 8; rampIndex++)
   {
      PolyRamp* polyRamp = &ramps[rampIndex];

      if (isReset)
         polyRamp->clockReset();
      else if (isClock)
         polyRamp->clockTick();

      if (tempo.isRunningOrFirstTick())
      {
         const float perentageToNextTick = tempo.getPercentage(Tempo::Division::Sixteenth);
         const float value = polyRamp->getCurrentValue(perentageToNextTick);
         lightMeterList[rampIndex]->setValue(value);

         const float voltage = cvMapper(value);
         outputList[rampIndex]->setVoltage(voltage);
      }
      else
      {
         lightMeterList[rampIndex]->setValue(0);
         outputList[rampIndex]->setVoltage(0.0);
      }
   }
}

void TimeLord::updateDisplays()
{
   displayController.fill();

   displayController.drawRect(0, 0, 127, 10, true);

   if (dataReceive)
      displayController.writeText(5, 25, "?", SchweineSystem::OLEDDisplay::Font::Huge, true);
   else if (dataApply)
      displayController.writeText(5, 25, "@", SchweineSystem::OLEDDisplay::Font::Huge, true);
   else
      displayController.writeText(5, 25, std::to_string(bankIndex), SchweineSystem::OLEDDisplay::Font::Huge, true);

   if (Division == displayMode)
      displayController.writeText(30, 1, "Division", SchweineSystem::OLEDDisplay::Font::Normal, false);
   else if (Length == displayMode)
      displayController.writeText(30, 1, "Length", SchweineSystem::OLEDDisplay::Font::Normal, false);
   else if (StageCount == displayMode)
      displayController.writeText(30, 1, "Stage Count", SchweineSystem::OLEDDisplay::Font::Normal, false);
   else
      displayController.writeText(30, 1, "Current Stage", SchweineSystem::OLEDDisplay::Font::Normal, false);

   for (uint8_t rampIndex = 0; rampIndex < 8; rampIndex++)
   {
      PolyRamp* polyRamp = &ramps[rampIndex];

      const bool even = (0 == (rampIndex % 2));
      const uint8_t x = even ? 30 : 80;

      const uint8_t yIndex = even ? rampIndex / 2 : (rampIndex - 1) / 2;
      const uint8_t y = 14 + yIndex * 13;

      std::string text = std::to_string(rampIndex + 1) + ": ";
      if (Division == displayMode)
         text += Tempo::getName(polyRamp->getStepSize());
      else if (Length == displayMode)
         text += std::to_string(polyRamp->getLength());
      else if (StageCount == displayMode)
         text += std::to_string(polyRamp->getStageCount());
      else
         text += std::to_string(polyRamp->getCurrentStageIndex());

      displayController.writeText(x, y, text, SchweineSystem::OLEDDisplay::Font::Normal, true);
   }
}

void TimeLord::dataFromMidiInput(const Bytes& message)
{
   const bool isSystemEvent = (0xF0 == (message[0] & 0xF0));
   if (isSystemEvent)
      return;

   const Midi::Event event = static_cast<Midi::Event>(message[0] & 0xF0);
   const Midi::Channel channel = 1 + (message[0] & 0x0F);
   if (11 != channel)
      return;

   if (Midi::Event::ControlChange != event)
   {
      if (Midi::Event::NoteOn == event)
         std::cout << " note on" << std::endl;
      else if (Midi::Event::NoteOff == event)
         std::cout << " note off" << std::endl;
      else
         std::cout << " ???" << (uint16_t)event << std::endl;

      std::cout << (uint16_t)message[1] << " " << (uint16_t)message[2] << std::endl;
      return;
   }

   const Midi::ControllerMessage controllerMessage = static_cast<Midi::ControllerMessage>(message[1]);

   if (Midi::ControllerMessage::RememberBlock == controllerMessage)
   {
      const uint8_t value = message[2];
      midiBuffer << value;
      dataReceive = true;
   }
   else if (Midi::ControllerMessage::RememberApply == controllerMessage)
   {
      const Bytes data = SevenBit::decode(midiBuffer);
      midiBuffer.clear();

      dataReceive = false;

      const uint8_t value = message[2];
      if (value != bankIndex)
         return;

      const char* cBuffer = (const char*)data.data();
      auto printIncomingData = [&]()
      {
         for (uint8_t byte : data)
            std::cout << byte;
         std::cout << std::endl;
      };
      printIncomingData();

      json_error_t error;
      json_t* rootJson = json_loadb(cBuffer, data.size(), 0, &error);

      SchweineSystem::Json::Object rootObject(rootJson);
      loadInternal(rootObject);

      dataAppliedPulse.trigger(2.0);
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
      rampObject.set("length", Value(length));

      const uint8_t stepSize = static_cast<uint8_t>(polyRamp->getStepSize());
      rampObject.set("stepSize", Value(stepSize));

      const bool loop = polyRamp->isLooping();
      rampObject.set("loop", Value(loop));

      Array stagesArray;
      for (uint8_t stageIndex = 0; stageIndex < polyRamp->getStageCount(); stageIndex++)
      {
         Object stageObject;

         const uint8_t stageLength = polyRamp->getStageLength(stageIndex);
         stageObject.set("length", Value(stageLength));

         const uint8_t startHeight = polyRamp->getStageStartHeight(stageIndex);
         stageObject.set("startHeight", Value(startHeight));

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

   loadInternal(rootObject);
}

void TimeLord::loadInternal(const SchweineSystem::Json::Object& rootObject)
{
   using namespace SchweineSystem::Json;

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

// widget

TimeLordWidget::TimeLordWidget(TimeLord* module)
   : SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelTimeLord = SchweineSystem::Master::the()->addModule<TimeLord, TimeLordWidget>("TimeLord");
