#include "GrooveMaestro.h"

#include <Tools/File.h>
#include <Tools/Text.h>
#include <Tools/Variable.h>

GrooveMaestro::GrooveMaestro()
   : Svin::Module()
   , Svin::MasterClock::Client()
   , fileName()
   , conductor()
   , tickTriggers(0)
   , segmentGates(0)
   // remote
   , deviceId(0)
   , deviceIdDisplay(this, Panel::Text_DeviceId)
   , deviceIdUpButton(this, Panel::DeviceIdUp)
   , deviceIdDownButton(this, Panel::DeviceIdDown)
   , launchpad()
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
   // input
   , gatePassInput(this, Panel::GatePass)
   , noOffsetSwitch(this, Panel::NoOffset)
   // output
   , gateOutput(this, Panel::GateOutput)
   , triggerGenerator()
   // mode
   , loopButton(this, Panel::Loop, Panel::RGB_Loop)
   , operationMode(OperationMode::Passthrough)
   , operationModeButton(this, Panel::Mode)
   // display
   , controller(this, Panel::Pixels_Display)
{
   setup();

   registerHubClient("GrooveMaestro");

   deviceIdDisplay.setColor(Color::Predefined::Yellow);
   controller.onClickedOpenFileFunction(this, &GrooveMaestro::loadProject, "Projects:grm");

   loopButton.setDefaultColor(Color::Predefined::Green);

   connectionButton.setDefaultColor(Color::Predefined::Green);
   connectToLaunchpad();
}

void GrooveMaestro::process(const ProcessArgs& args)
{
   if (loopButton.isTriggered())
   {
      bool loop = conductor.isLooping();
      loop ^= true;
      conductor.setLooping(loop);
   }
   loopButton.setActive(conductor.isLooping());

   Variable::Integer<uint8_t> varBank(deviceId, 0, 15, true);
   if (deviceIdUpButton.isTriggered())
      varBank.increment();
   else if (deviceIdDownButton.isTriggered())
      varBank.decrement();

   // operation mode
   if (operationModeButton.isTriggered())
   {
      static const std::vector<OperationMode> order = {OperationMode::Passthrough, OperationMode::Remote, OperationMode::Play};
      Variable::Enum<OperationMode> variable(operationMode, order, true);
      variable.increment();
   }

   gateOutput.setNumberOfChannels(16);

   // do stuff

   BoolField16 values(0);

   auto applyValues = [&]()
   {
      for (uint8_t index = 0; index < 16; index++)
         gateOutput.setActive(values.get(index), index);
   };

   const bool on = getTempo().isRunningOrFirstTick();
   if (!on)
      return applyValues();

   if (OperationMode::Passthrough == operationMode)
   {
      for (uint8_t index = 0; index < 8; index++)
      {
         if (!gatePassInput.isConnected() || !on)
            continue;

         const uint8_t inputIndex = noOffsetSwitch.isOn() ? index : index + 8;
         const float voltage = (inputIndex < gatePassInput.getNumberOfChannels()) ? gatePassInput.getVoltage(inputIndex) : 0.0;

         values.set(index + 8, (voltage > 3.0));
      }
      return applyValues();
   }

   if (hasReset())
   {
      conductor.clockReset();
      return applyValues();
   }

   while (hasTick())
   {
      conductor.clockTick();

      const uint32_t segmentIndex = conductor.getCurrentSegmentIndex();
      const uint32_t currentTick = conductor.getCurrentSegmentTick();
      tickTriggers = conductor.getTriggers(segmentIndex, currentTick);
      segmentGates = conductor.getGates(segmentIndex);

      triggerGenerator.trigger();
   }

   const bool pulse = triggerGenerator.process(args.sampleTime);

   for (uint8_t index = 0; index < 8; index++)
   {
      if (tickTriggers.get(index))
         values.set(index + 0, pulse);

      values.set(index + 8, segmentGates.get(index));
   }

   return applyValues();
}

void GrooveMaestro::loadProject(const std::string& newFileName)
{
   fileName = newFileName;

   const Bytes data = File::load(fileName);
   if (data.empty())
      return;

   const Svin::Json::Object rootObject(data);
   Svin::Json::Object projectObject = rootObject.get("project").toObject();

   const uint32_t segmentCount = projectObject.get("segments").toInt();
   const uint16_t digitCount = Variable::compileDigitCount(segmentCount);
   const uint8_t division = projectObject.get("division").toInt();

   auto compileSegmentKey = [&](const uint32_t segmentIndex)
   {
      return Text::pad(std::to_string(segmentIndex), digitCount);
   };

   auto compileColor = [](const Svin::Json::Array& array)
   {
      uint8_t red = array.at(0).toInt();
      uint8_t green = array.at(1).toInt();
      uint8_t blue = array.at(2).toInt();

      return Color(red, green, blue);
   };

   conductor.clear();
   conductor.update(division, segmentCount);

   // header
   {
      Svin::Json::Object headerObject = projectObject.get("header").toObject();
      for (uint32_t segmentIndex = 0; segmentIndex < segmentCount; segmentIndex++)
      {
         const std::string segmentKey = compileSegmentKey(segmentIndex);
         if (!headerObject.hasKey(segmentKey))
            continue;

         Svin::Json::Object segmentObject = headerObject.get(segmentKey).toObject();
         conductor.setSegmentName(segmentIndex, segmentObject.get("name").toString());

         if (segmentObject.hasKey("length"))
         {
            conductor.setSegmentLength(segmentIndex, segmentObject.get("length").toInt());
         }
         if (segmentObject.hasKey("fgColor"))
         {
            const Svin::Json::Array colorArray = segmentObject.get("fgColor").toArray();
            conductor.setSegmentForegroundColor(segmentIndex, compileColor(colorArray));
         }

         if (segmentObject.hasKey("bgColor"))
         {
            const Svin::Json::Array colorArray = segmentObject.get("bgColor").toArray();
            conductor.setSegmentBackgroundColor(segmentIndex, compileColor(colorArray));
         }
      }
   }

   // gates
   {
      Svin::Json::Object gatesObject = projectObject.get("gates").toObject();
      for (uint32_t segmentIndex = 0; segmentIndex < segmentCount; segmentIndex++)
      {
         const std::string segmentKey = compileSegmentKey(segmentIndex);
         if (!gatesObject.hasKey(segmentKey))
            continue;

         const BoolField8 gates = gatesObject.get(segmentKey).toInt();
         conductor.setGates(segmentIndex, gates);
      }
   }

   // beats
   {
      Svin::Json::Object beatsObject = projectObject.get("beats").toObject();
      for (uint32_t segmentIndex = 0; segmentIndex < segmentCount; segmentIndex++)
      {
         const std::string segmentKey = compileSegmentKey(segmentIndex);
         if (!beatsObject.hasKey(segmentKey))
            continue;

         Svin::Json::Array beatArray = beatsObject.get(segmentKey).toArray();

         const uint8_t beatLength = beatArray.size();
         if (beatLength != conductor.getSegmentLength(segmentIndex))
            continue;

         Grooves::Beat beat(beatLength, BoolField8(0));
         for (uint8_t tick = 0; tick < beatLength; tick++)
         {
            const BoolField8 triggers = beatArray.at(tick).toInt();
            beat[tick] = triggers;
         }
         conductor.setBeat(segmentIndex, beat);
      }
   }

   deviceId = rootObject.get("deviceId").toInt();
}

void GrooveMaestro::connectToLaunchpad()
{
}

void GrooveMaestro::updateDisplays()
{
   controller.fill();

   deviceIdDisplay.setText(Text::pad(std::to_string(deviceId + 1), 2));

   if (OperationMode::Passthrough == operationMode)
      updateDisplayPassthrough();
   else if (OperationMode::Remote == operationMode)
      updateDisplayRemote();
   else if (OperationMode::Play == operationMode)
      updateDisplayPlay();

   const uint32_t index = conductor.getCurrentSegmentIndex();

   Svin::Json::Object object;
   object.set("_Application", "GateKeeper");
   object.set("_Type", "Index");
   object.set("index", index);
   object.set("deviceId", deviceId);
   object.set("mode", static_cast<uint8_t>(operationMode));

   sendDocumentToHub(1, object);
}

void GrooveMaestro::updateDisplayPassthrough()
{
   controller.setColor(Color::Predefined::Yellow);
   controller.drawRect(0, 0, 130, 10, true);

   controller.setColor(Color::Predefined::Black);
   controller.writeText(65, 0, "Passthrough", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   const Tempo tempo = getTempo();
   const bool on = tempo.isRunningOrFirstTick();

   for (uint8_t index = 0; index < 8; index++)
   {
      const uint8_t column = (index < 4) ? 0 : 1;
      const uint8_t row = (index < 4) ? index : index - 4;

      const uint8_t x = 50 + column * 50;
      const uint8_t y = 25 + row * 20;

      controller.setColor(Color(155, 155, 155));
      controller.writeText(x, y, std::to_string(index + 1), Svin::DisplayOLED::Font::Large, Svin::DisplayOLED::Alignment::Right);

      controller.setColor(Color::Predefined::White);
      if (!on)
         controller.writeText(x + 10, y, ".", Svin::DisplayOLED::Font::Large);
      else if (gateOutput.getVoltage(index + 8) > 3.0)
         controller.writeText(x + 10, y, "H", Svin::DisplayOLED::Font::Large);
      else
         controller.writeText(x + 10, y, "_", Svin::DisplayOLED::Font::Large);
   }
}

void GrooveMaestro::updateDisplayRemote()
{
}

void GrooveMaestro::updateDisplayPlay()
{
   controller.setColor(Color::Predefined::Green);
   controller.drawRect(0, 0, 130, 10, true);

   controller.setColor(Color::Predefined::Black);
   controller.writeText(65, 0, "Current", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   const Tempo tempo = getTempo();
   const bool on = tempo.isRunningOrFirstTick();
   const uint32_t segmentCount = conductor.getSegmentCount();
   const uint16_t digitCount = Variable::compileDigitCount(segmentCount);

   if (0 == segmentCount || !on)
   {
      controller.setColor(Color::Predefined::White);
      controller.writeText(5, 12, Text::pad(std::to_string(segmentCount), digitCount), Svin::DisplayOLED::Font::Large);
      controller.writeText(7 + 12 * digitCount, 17, "segmemnts", Svin::DisplayOLED::Font::Normal);

      const uint8_t noOfLines = 10;
      const uint8_t noOfLetters = 15;

      const uint8_t x = 20;
      for (uint8_t counter = 0; counter < noOfLines; counter++)
      {
         const uint8_t row = noOfLines - (counter + 1);
         const uint8_t y = 30 + 10 * row;
         const int8_t index = fileName.length() - ((noOfLines - row) * noOfLetters);
         if (index >= 0)
         {
            const std::string text = fileName.substr(index, noOfLetters);
            controller.writeText(x, y, text, 10);
         }
         else
         {
            const std::string text = fileName.substr(0, noOfLetters + index);
            controller.writeText(x, y, Text::pad(text, noOfLetters, " "), 10);
            break;
         }
      }

      return;
   }

   // top row
   const uint32_t segmentIndex = conductor.getCurrentSegmentIndex();

   controller.setColor(Color::Predefined::White);
   controller.writeText(5, 12, Text::pad(std::to_string(segmentIndex), digitCount), Svin::DisplayOLED::Font::Large);

   const std::string eventName = conductor.getSegmentName(segmentIndex);
   const std::string eventText = eventName.empty() ? "--" : eventName;
   controller.writeText(7 + 12 * digitCount, 17, eventText, Svin::DisplayOLED::Font::Normal);

   // the grid
   const Grooves::Gates& gates = conductor.getGates(segmentIndex);
   const bool hasGates = conductor.hasGates(segmentIndex);

   const Grooves::Beat& beat = conductor.getBeat(segmentIndex);
   const bool hasBeat = conductor.hasBeat(segmentIndex);
   const uint8_t currentTick = conductor.getCurrentSegmentTick();
   const uint8_t length = conductor.getSegmentLength(segmentIndex);

   const uint8_t offset = (currentTick - (currentTick % 8));

   for (uint8_t col = 0; col < 8; col++)
   {
      const uint tick = offset + col;

      if (tick != currentTick)
         continue;

      controller.setColor(Color::Predefined::Green);

      const uint8_t x = 5 + col * 12;
      const uint8_t y = 30;
      controller.drawRect(x, y, x + 8, y + 4, true);

      break;
   }

   for (uint8_t row = 0; row < 8; row++)
   {
      const uint8_t y = 37 + row * 12;

      if (hasGates)
         controller.setColor(Color::Predefined::White);
      else
         controller.setColor(Color(155, 155, 200));

      if (gates.get(row))
         controller.drawRect(115, y, 125, y + 8, true);
      else
         controller.drawRect(115, y, 125, y + 8, false);

      if (hasBeat)
         controller.setColor(Color::Predefined::White);
      else
         controller.setColor(Color(155, 155, 200));

      for (uint8_t col = 0; col < 8; col++)
      {
         const uint tick = offset + col;
         const uint8_t x = 5 + col * 12;

         if (tick >= length)
            break;

         if (beat[tick].get(row))
            controller.drawRect(x, y, x + 8, y + 8, true);
      }
   }
}

void GrooveMaestro::receivedDocumentFromHub(const ::Midi::Channel& channel, const Svin::Json::Object& object, const uint8_t docIndex)
{
   if (1 != channel || 0 != docIndex)
      return;

   if ("Reload" == object.get("_Type").toString())
   {
      const uint8_t objectDeviceId = object.get("deviceId").toInt();
      if (objectDeviceId != deviceId)
         return;

      const std::string fileName = object.get("fileName").toString();
      loadProject(fileName);
   }
}

void GrooveMaestro::load(const Svin::Json::Object& rootObject)
{
   deviceId = rootObject.get("deviceId").toInt();
   operationMode = static_cast<OperationMode>(rootObject.get("operation").toInt());

   const bool loop = rootObject.get("loop").toBool();
   conductor.setLooping(loop);

   const bool no_offset = rootObject.get("no_offset").toBool();
   noOffsetSwitch.setState(no_offset);

   const std::string newFileName = rootObject.get("fileName").toString();
   loadProject(newFileName);
}

void GrooveMaestro::save(Svin::Json::Object& rootObject)
{
   rootObject.set("deviceId", deviceId);
   rootObject.set("operation", static_cast<uint8_t>(operationMode));
   rootObject.set("loop", conductor.isLooping());
   rootObject.set("no_offset", noOffsetSwitch.isOn());

   rootObject.set("fileName", fileName);
}

// widget

GrooveMaestroWidget::GrooveMaestroWidget(GrooveMaestro* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelGrooveMaestro = Svin::Origin::the()->addModule<GrooveMaestro, GrooveMaestroWidget>("GrooveMaestro");
