#include "TimeLord.h"
#include "TimeLordPanel.h"

#include <osdialog.h>

#include <Midi/MidiCommon.h>
#include <Tools/File.h>
#include <Tools/SevenBit.h>
#include <Tools/Variable.h>

#include <SyJson.h>
#include <SyMaster.h>

const std::string TimeLord::keys = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

TimeLord::TimeLord()
   : Sy::Module()
   , Sy::Exapnder<BusTimeLord>(this)
   , fileName()
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
   , displayController(this, Panel::Pixels_Display)
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
{
   Majordomo::hello(this);

   setup();
   allowExpanderOnLeft();

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
      displayList[rampIndex]->setColor(Sy::Color{255, 255, 0});
      displayList[rampIndex]->setText("ABC");
   }

   modeInputLight.setDefaultColor(Sy::Color{255, 255, 0});
   modeRemoteLight.setDefaultColor(Sy::Color{0, 0, 255});
   modeInternalLight.setDefaultColor(Sy::Color{0, 255, 0});
   setOperationLEDs();
}

TimeLord::~TimeLord()
{
   Majordomo::bye(this);
}

void TimeLord::process(const ProcessArgs& args)
{
   Majordomo::process();

   BusTimeLord busMessage = receiveFromLeft();

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
      bankDisplay.setColor(Sy::Color{255, 255, 255});
      bankDisplay.setText("?");
   }
   else if (dataApply)
   {
      bankDisplay.setColor(Sy::Color{255, 255, 255});
      bankDisplay.setText("@");
   }
   else
   {
      bankDisplay.setColor(Sy::Color{255, 255, 255});
      bankDisplay.setText(std::to_string(bankIndex));
   }

   // outputs
   setOutputs(isReset, isClock, busMessage);

   // maybe upload
   if (uploadTrigger.process(inputs[Panel::Upload].getVoltage() > 3.0) || uploadData)
   {
      uploadData = false;

      if (OperationMode::Input == operationMode)
         uploadToRemote(busMessage);
   }
}

void TimeLord::updateDisplays()
{
   displayController.fill();

   if (OperationMode::Internal != operationMode)
      return;

   displayController.setColor(Sy::Color{255, 255, 255});
   displayController.drawRect(0, 0, 60, 10, true);

   displayController.setColor(Sy::Color{0, 0, 0});

   if (DisplayMode::Division == displayMode)
      displayController.writeText(5, 1, "Step", Sy::DisplayOLED::Font::Normal);
   else if (DisplayMode::Length == displayMode)
      displayController.writeText(5, 1, "Length", Sy::DisplayOLED::Font::Normal);
   else if (DisplayMode::StageCount == displayMode)
      displayController.writeText(5, 1, "Count", Sy::DisplayOLED::Font::Normal);
   else
      displayController.writeText(5, 1, "Current", Sy::DisplayOLED::Font::Normal);

   displayController.setColor(Sy::Color{255, 255, 255});

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

      displayController.writeText(x, y, text, Sy::DisplayOLED::Font::Normal);
   }
}

void TimeLord::loadRamps(const std::string& newFileName)
{
   fileName = newFileName;

   const Bytes data = File::load(fileName);
   if (data.empty())
      return;

   using namespace Sy::Json;

   auto loadContent = [&](const Object& contentObject)
   {
      for (uint8_t rampIndex = 0; rampIndex < 8; rampIndex++)
      {
         PolyRamp* polyRamp = &ramps[rampIndex];
         polyRamp->clear();

         Object rampObject = contentObject.get(keys.substr(rampIndex, 1)).toObject();

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
   };

   const Object rootObject(data);

   const Array banksArray = rootObject.get("banks").toArray();
   for (uint8_t bankCounter = 0; bankCounter < banksArray.size(); bankCounter++)
   {
      const Object bankObject = banksArray.get(bankCounter).toObject();

      const uint8_t index = bankObject.get("index").toInt();
      if (index != bankIndex)
         continue;

      Object contentObject = bankObject.get("content").toObject();
      loadContent(contentObject);
      break;
   }
}

void TimeLord::setOutputs(bool isReset, bool isClock, const BusTimeLord& busMessage)
{
   for (uint8_t rampIndex = 0; rampIndex < 8; rampIndex++)
   {
      PolyRamp* polyRamp = &ramps[rampIndex];

      auto inputMode = [&]()
      {
         float voltage = inputList[rampIndex]->getVoltage();
         if (0 > voltage)
         {
            displayList[rampIndex]->setColor(Sy::Color{255, 0, 0});
            voltage = 0.0;
         }
         else
         {
            displayList[rampIndex]->setColor(Sy::Color{255, 255, 0});
         }

         const uint8_t value = voltageToValue(voltage);

         if (busMessage.silence[rampIndex] && !tempo.isRunningOrFirstTick())
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
         displayList[rampIndex]->setColor(Sy::Color{0, 0, 255});

         const uint8_t value = remoteValues[rampIndex];
         const float voltage = valueToVoltage(value);

         if (busMessage.silence[rampIndex] && !tempo.isRunningOrFirstTick())
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
         displayList[rampIndex]->setColor(Sy::Color{0, 0, 0});
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

      auto printIncomingData = [&]()
      {
         for (uint8_t byte : data)
            std::cout << byte;
         std::cout << std::endl;
      };
      printIncomingData();

      Sy::Json::Object rootObject(data);
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

      buffer += value;
   }
   else if (Midi::ControllerMessage::RememberApply == controllerMessage)
   {
      if (value != bankIndex || MidiReceive::Remember != receive)
         return;

      Sy::Json::Object rootObject = extractJsonAndClearBuffer();

      const std::string newFileName = rootObject.get("fileName").toString();
      loadRamps(newFileName);

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

      buffer += value;
   }
   else if (Midi::ControllerMessage::DataApply == controllerMessage)
   {
      if (value != bankIndex || MidiReceive::Data != receive)
         return;

      Sy::Json::Object rootObject = extractJsonAndClearBuffer();

      setFromRemote(rootObject);
      receive = MidiReceive::None;
   }
}

void TimeLord::load(const Sy::Json::Object& rootObject)
{
   bankIndex = rootObject.get("bank").toInt();
   displayMode = static_cast<DisplayMode>(rootObject.get("display").toInt());
   operationMode = static_cast<OperationMode>(rootObject.get("operation").toInt());

   const std::string newFileName = rootObject.get("fileName").toString();
   loadRamps(newFileName);
}

void TimeLord::save(Sy::Json::Object& rootObject)
{
   rootObject.set("bank", bankIndex);
   rootObject.set("display", static_cast<uint8_t>(displayMode));
   rootObject.set("operation", static_cast<uint8_t>(operationMode));

   rootObject.set("fileName", fileName);
}

void TimeLord::uploadToRemote(const BusTimeLord& busMessage)
{
   using namespace Sy::Json;

   Array stageArray;
   for (uint8_t rampIndex = 0; rampIndex < 8; rampIndex++)
   {
      float voltage = inputList[rampIndex]->getVoltage();
      if (0 > voltage)
         voltage = 0.0;

      Object stageObject;
      stageObject.set("value", voltageToValue(voltage));
      stageObject.set("steady", busMessage.steady[rampIndex]);

      stageArray.append(stageObject);
   }

   Object uploadObject;
   uploadObject.set("stages", stageArray);
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

   const Bytes buffer = uploadObject.toBytes();
   const std::string data = SevenBit::encode(buffer);
   for (const char& byte : data)
      sendMessage(Midi::ControllerMessage::DataBlock, byte);

   sendMessage(Midi::ControllerMessage::DataApply, bankIndex);

   Majordomo::send(queue);
}

void TimeLord::setFromRemote(const Sy::Json::Object& rootObject)
{
   using namespace Sy::Json;

   Array stageArray = rootObject.get("stages").toArray();
   const uint8_t valueCount = stageArray.size();
   if (8 != valueCount)
      return;

   for (uint8_t index = 0; index < valueCount; index++)
   {
      const Object stageObject = stageArray.get(index).toObject();

      remoteValues[index] = stageObject.get("value").toInt();
   }
}

// widget

TimeLordWidget::TimeLordWidget(TimeLord* module)
   : Sy::ModuleWidget(module)
{
   setup();

   using OLEDWidget = Sy::DisplayOLED::Widget;

   OLEDWidget* oled = OLEDWidget::find(module, TimeLord::Panel::Pixels_Display);
   if (oled)
      oled->onClicked(this, &TimeLordWidget::displayClicked);

   std::string logoPath = asset::plugin(Sy::Master::the()->instance(), "res/Utilities/TimeLordLogo.svg");

   Sy::SvgImage* logoWidget = new Sy::SvgImage(rack::math::Vec(0, 342.5), module, logoPath, 0.4);
   const int8_t xShift = 0.5 * logoWidget->box.size.x;
   logoWidget->shift(math::Vec(-xShift, 0.0));
   addChild(logoWidget);
}

void TimeLordWidget::displayClicked(const float& x, const float& y)
{
   (void)x;
   (void)y;

   TimeLord* myModule = dynamic_cast<TimeLord*>(getSchweineModule());
   if (!myModule)
      return;

   const char* path = osdialog_file(OSDIALOG_OPEN, nullptr, NULL, osdialog_filters_parse("Ramps:json"));
   if (path)
      myModule->loadRamps(std::string(path));
}

Model* modelTimeLord = Sy::Master::the()->addModule<TimeLord, TimeLordWidget>("TimeLord");
