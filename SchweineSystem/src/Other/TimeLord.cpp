#include "TimeLord.h"
#include "TimeLordPanel.h"

#include <Midi/MidiCommon.h>
#include <SchweineSystemMaster.h>
#include <Tools/SevenBit.h>
#include <Tools/Variable.h>

// lord

const std::string TimeLord::keys = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

TimeLord::TimeLord()
   : SchweineSystem::Module()
   , ramps{}
   // midi
   , receive(MidiReceive::None)
   , buffer()
   // clock
   , clockTrigger()
   , resetTrigger()
   , tempo()
   // input
   , inputList(inputs)
   , displayList(this)
   , voltageToValue(0.0, 10.0, 0, 255)
   // upload
   , uploadTrigger()
   , uploadData(false)
   // outout
   , valueToVoltage(0.0, 255.0, 0.0, 10.0)
   , lightMeterList(this)
   , outputList(outputs)
   // display
   , displayMode(DisplayMode::StageIndex)
   , displayButton(this, Panel::Display)
   , displayController(this, Panel::Pixels_Display, 80, 120)
   // bank
   , bankIndex(0)
   , bankButton(this, Panel::BankUp)
   , dataAppliedPulse()
   , bankDisplay(this, Panel::Text_Bank, Panel::RGB_Bank)
   // mode
   , operationMode(OperationMode::Input)
   , operationTrigger()
   , remoteValues{0, 0, 0, 0, 0, 0, 0, 0}
   , modeInputLight(this, Panel::RGB_Input_Status)
   , modeRemoteLight(this, Panel::RGB_Remote_Status)
   , modeInternalLight(this, Panel::RGB_Internal_Status)
   // silence
   , silenceOnStop(false)
   , silenceButton(this, Panel::Silence, Panel::RGB_Silence)
{
   setup();
   Majordomo::hello(this);

   inputList.append({Panel::Channel1_Pass,
                     Panel::Channel2_Pass,
                     Panel::Channel3_Pass,
                     Panel::Channel4_Pass,
                     Panel::Channel5_Pass,
                     Panel::Channel6_Pass,
                     Panel::Channel7_Pass,
                     Panel::Channel8_Pass});

   displayList.append({{Panel::Text_Channel1_Value, Panel::RGB_Channel1_Value},
                       {Panel::Text_Channel2_Value, Panel::RGB_Channel2_Value},
                       {Panel::Text_Channel3_Value, Panel::RGB_Channel3_Value},
                       {Panel::Text_Channel4_Value, Panel::RGB_Channel4_Value},
                       {Panel::Text_Channel5_Value, Panel::RGB_Channel5_Value},
                       {Panel::Text_Channel6_Value, Panel::RGB_Channel6_Value},
                       {Panel::Text_Channel7_Value, Panel::RGB_Channel7_Value},
                       {Panel::Text_Channel8_Value, Panel::RGB_Channel8_Value}});

   outputList.append({Panel::Channel1_Output,
                      Panel::Channel2_Output,
                      Panel::Channel3_Output,
                      Panel::Channel4_Output,
                      Panel::Channel5_Output,
                      Panel::Channel6_Output,
                      Panel::Channel7_Output,
                      Panel::Channel8_Output});

   lightMeterList.append({Panel::Value_Channel1_Strip,
                          Panel::Value_Channel2_Strip,
                          Panel::Value_Channel3_Strip,
                          Panel::Value_Channel4_Strip,
                          Panel::Value_Channel5_Strip,
                          Panel::Value_Channel6_Strip,
                          Panel::Value_Channel7_Strip,
                          Panel::Value_Channel8_Strip});

   for (uint8_t rampIndex = 0; rampIndex < 8; rampIndex++)
   {
      lightMeterList[rampIndex]->setMaxValue(255);
      displayList[rampIndex]->setColor(SchweineSystem::Color{255, 255, 0});
      displayList[rampIndex]->setText("ABC");
   }

   silenceButton.setDefaultColor(SchweineSystem::Color{100, 100, 100});
   silenceButton.setOn();

   modeInputLight.setDefaultColor(SchweineSystem::Color{255, 255, 0});
   modeRemoteLight.setDefaultColor(SchweineSystem::Color{0, 0, 255});
   modeInternalLight.setDefaultColor(SchweineSystem::Color{0, 255, 0});
   setOperationLEDs();
}

TimeLord::~TimeLord()
{
   Majordomo::bye(this);
}

void TimeLord::process(const ProcessArgs& args)
{
   Majordomo::process();

   // clock
   const bool isClock = clockTrigger.process(inputs[Panel::Clock].getVoltage() > 3.0);
   const bool isReset = resetTrigger.process(inputs[Panel::Reset].getVoltage() > 3.0);

   if (isReset)
      tempo.clockReset();
   else if (isClock)
      tempo.clockTick();
   else
      tempo.advance(args.sampleRate);

   // operation mode
   auto advanceOperationMode = [&]()
   {
      static const std::vector<OperationMode> order = {OperationMode::Input, OperationMode::Remote, OperationMode::Internal};
      Variable::Enum<OperationMode> variable(operationMode, order, true);
      variable.increment();
   };

   if (inputs[Panel::ModeCV].isConnected())
   {
      if (operationTrigger.process(inputs[Panel::ModeCV].getVoltage() > 3))
         advanceOperationMode();
   }
   else
   {
      if (operationTrigger.process(params[Panel::ModeManual].getValue()))
         advanceOperationMode();
   }
   setOperationLEDs();

   // silence
   if (silenceButton.isTriggered())
      silenceOnStop ^= true;
   silenceButton.setActive(silenceOnStop);

   // screen mode
   if (displayButton.isTriggered())
   {
      static const std::vector<DisplayMode> order = {DisplayMode::Division, DisplayMode::Length, DisplayMode::StageCount, DisplayMode::StageIndex};
      Variable::Enum<DisplayMode> variable(displayMode, order, true);
      variable.increment();
   }

   // bank display
   if (bankButton.isTriggered())
   {
      bankIndex++;
      if (bankIndex >= 10)
         bankIndex = 0;
   }

   const bool dataApply = dataAppliedPulse.process(args.sampleTime);
   if (MidiReceive::Remember == receive)
   {
      bankDisplay.setColor(SchweineSystem::Color{255, 255, 255});
      bankDisplay.setText("?");
   }
   else if (dataApply)
   {
      bankDisplay.setColor(SchweineSystem::Color{255, 255, 255});
      bankDisplay.setText("@");
   }
   else
   {
      bankDisplay.setColor(SchweineSystem::Color{255, 255, 255});
      bankDisplay.setText(std::to_string(bankIndex));
   }

   // outputs
   setOutputs(isReset, isClock);

   // maybe upload
   if (uploadTrigger.process(inputs[Panel::Upload].getVoltage() > 3.0) || uploadData)
   {
      uploadData = false;

      if (OperationMode::Input == operationMode)
         uploadToRemote();
   }
}

void TimeLord::updateDisplays()
{
   displayController.fill();

   if (OperationMode::Internal != operationMode)
      return;

   displayController.drawRect(0, 0, 80, 10, true);
   displayController.setColor(SchweineSystem::Color{0, 0, 0});

   if (DisplayMode::Division == displayMode)
      displayController.writeText(5, 1, "Division", SchweineSystem::DisplayOLED::Font::Normal);
   else if (DisplayMode::Length == displayMode)
      displayController.writeText(5, 1, "Length", SchweineSystem::DisplayOLED::Font::Normal);
   else if (DisplayMode::StageCount == displayMode)
      displayController.writeText(5, 1, "Count", SchweineSystem::DisplayOLED::Font::Normal);
   else
      displayController.writeText(5, 1, "Current", SchweineSystem::DisplayOLED::Font::Normal);

   displayController.setColor(SchweineSystem::Color{255, 255, 255});

   for (uint8_t rampIndex = 0; rampIndex < 8; rampIndex++)
   {
      PolyRamp* polyRamp = &ramps[rampIndex];

      const uint8_t x = 5;
      const uint8_t y = 16 + rampIndex * 13;

      std::string text = std::to_string(rampIndex + 1) + ": ";
      if (DisplayMode::Division == displayMode)
         text += Tempo::getName(polyRamp->getStepSize());
      else if (DisplayMode::Length == displayMode)
         text += std::to_string(polyRamp->getLength());
      else if (DisplayMode::StageCount == displayMode)
         text += std::to_string(polyRamp->getStageCount());
      else
         text += std::to_string(polyRamp->getCurrentStageIndex());

      displayController.writeText(x, y, text, SchweineSystem::DisplayOLED::Font::Normal);
   }
}

void TimeLord::setOutputs(bool isReset, bool isClock)
{
   for (uint8_t rampIndex = 0; rampIndex < 8; rampIndex++)
   {
      PolyRamp* polyRamp = &ramps[rampIndex];

      auto inputMode = [&]()
      {
         float voltage = inputList[rampIndex]->getVoltage();
         if (0 > voltage)
         {
            displayList[rampIndex]->setColor(SchweineSystem::Color{255, 0, 0});
            voltage = 0.0;
         }
         else
         {
            displayList[rampIndex]->setColor(SchweineSystem::Color{255, 255, 0});
         }

         const uint8_t value = voltageToValue(voltage);

         if (silenceOnStop && !tempo.isRunningOrFirstTick())
         {
            displayList[rampIndex]->setText("off");
            lightMeterList[rampIndex]->setValue(0);
            outputList[rampIndex]->setVoltage(0.0);
         }
         else
         {
            displayList[rampIndex]->setText(std::to_string(value));
            lightMeterList[rampIndex]->setValue(value);
            outputList[rampIndex]->setVoltage(voltage);
         }
      };

      auto remoteMode = [&]()
      {
         displayList[rampIndex]->setColor(SchweineSystem::Color{0, 0, 255});

         const uint8_t value = remoteValues[rampIndex];
         const float voltage = valueToVoltage(value);

         if (silenceOnStop && !tempo.isRunningOrFirstTick())
         {
            displayList[rampIndex]->setText("off");
            lightMeterList[rampIndex]->setValue(0);
            outputList[rampIndex]->setVoltage(0.0);
         }
         else
         {
            displayList[rampIndex]->setText(std::to_string(value));
            lightMeterList[rampIndex]->setValue(value);
            outputList[rampIndex]->setVoltage(voltage);
         }
      };

      auto internalMode = [&]()
      {
         displayList[rampIndex]->setColor(SchweineSystem::Color{0, 0, 0});
         displayList[rampIndex]->setText("");

         if (tempo.isRunningOrFirstTick())
         {
            const float perentageToNextTick = tempo.getPercentage(Tempo::Division::Sixteenth);
            const float value = polyRamp->getCurrentValue(perentageToNextTick);
            lightMeterList[rampIndex]->setValue(value);

            const float voltage = valueToVoltage(value);
            outputList[rampIndex]->setVoltage(voltage);
         }
         else
         {
            lightMeterList[rampIndex]->setValue(0);
            outputList[rampIndex]->setVoltage(0.0);
         }
      };

      if (isReset)
         polyRamp->clockReset();
      else if (isClock)
         polyRamp->clockTick();

      if (OperationMode::Input == operationMode)
         inputMode();
      else if (OperationMode::Remote == operationMode)
         remoteMode();
      else
         internalMode();
   }
}

void TimeLord::setOperationLEDs()
{
   modeInputLight.setActive(OperationMode::Input == operationMode);
   modeRemoteLight.setActive(OperationMode::Remote == operationMode);
   modeInternalLight.setActive(OperationMode::Internal == operationMode);
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

   auto extractJsonAndClearBuffer = [&]()
   {
      const Bytes data = SevenBit::decode(buffer);
      buffer.clear();

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
      return rootObject;
   };

   const Midi::ControllerMessage controllerMessage = static_cast<Midi::ControllerMessage>(message[1]);
   const uint8_t value = message[2];

   // ramps
   if (Midi::ControllerMessage::RememberInit == controllerMessage)
   {
      if (value != bankIndex)
         return;

      buffer.clear();
      receive = MidiReceive::Remember;
   }
   else if (Midi::ControllerMessage::RememberBlock == controllerMessage)
   {
      if (MidiReceive::Remember != receive)
         return;

      buffer << value;
   }
   else if (Midi::ControllerMessage::RememberApply == controllerMessage)
   {
      if (value != bankIndex || MidiReceive::Remember != receive)
         return;

      SchweineSystem::Json::Object rootObject = extractJsonAndClearBuffer();

      loadInternal(rootObject);
      receive = MidiReceive::None;
      dataAppliedPulse.trigger(2.0);
   }
   // values
   else if (Midi::ControllerMessage::DataInit == controllerMessage)
   {
      if (value != bankIndex)
         return;

      buffer.clear();
      receive = MidiReceive::Data;
   }
   else if (Midi::ControllerMessage::DataBlock == controllerMessage)
   {
      if (MidiReceive::Data != receive)
         return;

      buffer << value;
   }
   else if (Midi::ControllerMessage::DataApply == controllerMessage)
   {
      if (value != bankIndex || MidiReceive::Data != receive)
         return;

      SchweineSystem::Json::Object rootObject = extractJsonAndClearBuffer();

      loadRemote(rootObject);
      receive = MidiReceive::None;
   }
}

json_t* TimeLord::dataToJson()
{
   using namespace SchweineSystem::Json;

   Object rootObject;
   rootObject.set("bank", bankIndex);
   rootObject.set("display", static_cast<uint8_t>(displayMode));
   rootObject.set("operation", static_cast<uint8_t>(operationMode));
   rootObject.set("silence", silenceOnStop);

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

         const uint8_t endHeight = polyRamp->getStageEndHeight(stageIndex);
         stageObject.set("endHeight", Value(endHeight));

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
   displayMode = static_cast<DisplayMode>(rootObject.get("display").toInt());
   operationMode = static_cast<OperationMode>(rootObject.get("operation").toInt());
   silenceOnStop = rootObject.get("silence").toBool();

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

         const uint8_t endHeight = stageObject.get("endHeight").toInt();
         polyRamp->setStageEndHeight(stageIndex, endHeight);
      }
   }
}

void TimeLord::uploadToRemote()
{
   using namespace SchweineSystem::Json;

   Array valueArray;
   for (uint8_t rampIndex = 0; rampIndex < 8; rampIndex++)
   {
      float voltage = inputList[rampIndex]->getVoltage();
      if (0 > voltage)
         voltage = 0.0;

      const uint8_t value = voltageToValue(voltage);
      valueArray.append(value);
   }

   Object uploadObject;
   uploadObject.set("values", valueArray);
   uploadObject.set("bankIndex", bankIndex);

   Queue queue;

   const uint8_t firstByte = (Midi::Event::ControlChange | (Midi::Device::VCVRack - 1));
   auto sendMessage = [&](const Midi::ControllerMessage midiEvent, const uint8_t value)
   {
      Bytes message(3);
      message[0] = firstByte;
      message[1] = midiEvent;
      message[2] = value;
      queue.push_back(message);
   };

   sendMessage(Midi::ControllerMessage::DataInit, bankIndex);

   size_t size = json_dumpb(uploadObject.toJson(), NULL, 0, 0);
   if (size == 0)
      return;

   char* buffer = new char[size];
   size = json_dumpb(uploadObject.toJson(), buffer, size, 0);

   for (size_t index = 0; index < size; index++)
   {
      sendMessage(Midi::ControllerMessage::DataBlock, buffer[index]);
   }

   delete[] buffer;

   sendMessage(Midi::ControllerMessage::DataApply, bankIndex);

   Majordomo::send(queue);
}

void TimeLord::loadRemote(const SchweineSystem::Json::Object& rootObject)
{
   using namespace SchweineSystem::Json;

   Array valueArray = rootObject.get("values").toArray();
   const uint8_t valueCount = valueArray.size();
   if (8 != valueCount)
      return;

   for (uint8_t index = 0; index < valueCount; index++)
   {
      const uint8_t value = valueArray.get(index).toInt();
      remoteValues[index] = value;
   }
}

// widget

TimeLordWidget::TimeLordWidget(TimeLord* module)
   : SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelTimeLord = SchweineSystem::Master::the()->addModule<TimeLord, TimeLordWidget>("TimeLord");
