#include "GrooveMaestro.h"

#include <Tools/File.h>
#include <Tools/Text.h>
#include <Tools/Variable.h>

GrooveMaestro::GrooveMaestro()
   : Svin::Module()
   , Svin::MasterClock::Client()
   , fileName()
   , conductor()
   , localGrooves()
   , voltages()
   , tickTriggers(0)
   , segmentGates(0)
   // remote
   , deviceId(0)
   , deviceIdDisplay(this, Panel::Text_DeviceId)
   , launchpad()
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
   , launchpadOffset(0)
   // input
   , contoutPassInput(this, Panel::ContourPass)
   , gatePassInput(this, Panel::GatePass)
   , noOffsetSwitch(this, Panel::NoOffset)
   // output
   , contourOutput(this, Panel::ContourOutput)
   , gateOutput(this, Panel::GateOutput)
   , valueToVoltage(0.0, 255.0, 0.0, 10.0)
   , triggerGenerator()
   // mode
   , loopButton(this, Panel::Loop, Panel::RGB_Loop)
   , operationMode(OperationMode::Passthrough)
   , operationModeButton(this, Panel::Mode)
   // display
   , controller(this, Panel::Pixels_Display)
   , voltageToValue(0.0, 10.0, 0.0, 255.0)
{
   setup();
   registerHubClient("GrooveMaestro");

   localGrooves.update(20, 1);
   localGrooves.setLooping(true);

   deviceIdDisplay.setColor(Color::Predefined::Yellow);
   controller.onPressedOpenFileFunction(this, &GrooveMaestro::loadProject, "Projects:grm");

   loopButton.setDefaultColor(Color::Predefined::Green);

   connectionButton.setDefaultColor(Color::Predefined::Green);
   connectToLaunchpad();
}

void GrooveMaestro::process(const ProcessArgs& args)
{
   launchpad.update();

   if (loopButton.isTriggered())
   {
      bool loop = conductor.isLooping();
      loop ^= true;
      conductor.setLooping(loop);
   }
   loopButton.setActive(conductor.isLooping());

   if (connectionButton.isTriggered() && !launchpad.isConnected())
      connectToLaunchpad();

   // operation mode
   if (operationModeButton.isTriggered())
   {
      static const std::vector<OperationMode> order = {OperationMode::Passthrough, OperationMode::Remote, OperationMode::Play};
      Variable::Enum<OperationMode> variable(operationMode, order, true);
      variable.increment();
   }

   contourOutput.setNumberOfChannels(16);
   gateOutput.setNumberOfChannels(16);

   // do stuff
   voltages = std::vector<float>(16, 0.0);
   BoolField16 triggers(0);

   auto applyValues = [&]()
   {
      for (uint8_t index = 0; index < 16; index++)
      {
         contourOutput.setVoltage(voltages[index], index);
         gateOutput.setActive(triggers.get(index), index);
      }
   };

   if (hasReset())
   {
      conductor.clockReset();
      localGrooves.clockReset();
      return applyValues();
   }

   const Tempo tempo = getTempo();
   const bool on = tempo.isRunningOrFirstTick();
   if (!on)
      return applyValues();

   auto fillTriggers = [&](Grooves& grooves)
   {
      while (hasTick())
      {
         grooves.clockTick();

         const uint32_t segmentIndex = grooves.getCurrentSegmentIndex();
         const uint32_t currentTick = grooves.getCurrentSegmentTick();
         tickTriggers = on ? grooves.getTriggers(segmentIndex, currentTick) : BoolField8(0);
         segmentGates = on ? grooves.getGates(segmentIndex) : BoolField8(0);

         triggerGenerator.trigger();
      }

      const bool pulse = triggerGenerator.process(args.sampleTime);

      for (uint8_t index = 0; index < 8; index++)
      {
         if (tickTriggers.get(index))
            triggers.set(index + 0, pulse);

         triggers.set(index + 8, segmentGates.get(index));
      }
   };

   if (OperationMode::Passthrough == operationMode)
   {
      if (contoutPassInput.isConnected())
      {
         for (uint8_t index = 0; index < 16; index++)
         {
            voltages[index] = (index < contoutPassInput.getNumberOfChannels()) ? contoutPassInput.getVoltage(index) : 0.0;
            if (voltages[index] < 0.0)
               voltages[index] = 0.0;
         }
      }

      fillTriggers(localGrooves);

      if (gatePassInput.isConnected())
      {
         for (uint8_t index = 0; index < 8; index++)
         {
            const uint8_t inputIndex = noOffsetSwitch.isOn() ? index : index + 8;
            const float voltage = (inputIndex < gatePassInput.getNumberOfChannels()) ? gatePassInput.getVoltage(inputIndex) : 0.0;

            triggers.set(index + 8, (voltage > 3.0));
         }
      }

      return applyValues();
   }
   else if (OperationMode::Remote == operationMode)
   {
      return applyValues();
   }
   else if (OperationMode::Play == operationMode)
   {
      fillTriggers(conductor);

      const float tickPercentage = tempo.getPercentage();
      const uint32_t segmentIndex = conductor.getCurrentSegmentIndex();
      const float segmentPercentage = conductor.getCurrentSegmentPrecentage(tickPercentage);
      for (uint8_t laneIndex = 0; laneIndex < conductor.getContourCount(); laneIndex++)
      {
         const Contour& contour = conductor.getContour(laneIndex);

         const uint8_t value = on ? contour.getSegmentValue(segmentIndex, segmentPercentage) : 0.0;
         const float voltage = valueToVoltage(value);
         voltages[laneIndex] = voltage;
      }

      return applyValues();
   }
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

   // lanes
   {
      Svin::Json::Array contourArray = projectObject.get("contours").toArray();
      if (conductor.getContourCount() != contourArray.size())
      {
         std::cout << newFileName << " " << (uint16_t)conductor.getContourCount() << " " << contourArray.size() << std::endl;
         return;
      }

      for (uint8_t contourIndex = 0; contourIndex < conductor.getContourCount(); contourIndex++)
      {
         Contour& contour = conductor.getContour(contourIndex);
         Svin::Json::Object contourObject = contourArray.at(contourIndex).toObject();
         contour.setName(contourObject.get("name").toString());

         for (uint32_t segmentIndex = 0; segmentIndex < segmentCount; segmentIndex++)
         {
            const std::string segmentKey = compileSegmentKey(segmentIndex);
            if (!contourObject.hasKey(segmentKey))
               continue;

            Svin::Json::Object segmentObject = contourObject.get(segmentKey).toObject();
            contour.setSegmentSteady(segmentIndex, segmentObject.get("steady").toBool());

            if (segmentObject.hasKey("start"))
               contour.setSegmentStartValue(segmentIndex, segmentObject.get("start").toInt());
            if (segmentObject.hasKey("end"))
               contour.setSegmentEndValue(segmentIndex, segmentObject.get("end").toInt());
         }
      }
   }

   deviceId = rootObject.get("deviceId").toInt();
   connectToLaunchpad();
}

void GrooveMaestro::updateDisplays()
{
   controller.fill();

   connectionButton.setActive(launchpad.isConnected());
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

   if (false)
   {
      static Counter counter(60);
      static bool firstPage = true;

      if (counter.nextAndIsMaxValue())
         firstPage ^= true;

      launchpad.showColorTest(firstPage);
   }
}

void GrooveMaestro::updateDisplayPassthrough()
{
   controller.setColor(Color::Predefined::Yellow);
   controller.drawRect(0, 0, 130, 10, true);

   controller.setColor(Color::Predefined::Black);
   controller.writeText(65, 0, "Passthrough", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   for (const Svin::LaunchpadClient::Pad& pad : launchpad.triggeredPads())
   {
      const bool pressed = (Svin::LaunchpadClient::Button::Off != pad.button);
      if (!pressed)
         continue;

      if (8 == pad.column)
      {
         Grooves::Gates gates = localGrooves.getGates(0);
         const uint8_t index = 7 - pad.row;

         gates.flip(index);

         localGrooves.setGates(0, gates);
      }
      else if (8 == pad.row)
      {
         if (1 == pad.column)
         {
            launchpadOffset += 1;
            clearLaunchpad();
         }
         else if (0 == pad.column)
         {
            if (0 != launchpadOffset)
            {
               launchpadOffset -= 1;
               clearLaunchpad();
            }
         }
         else if (2 == pad.column)
         {
            uint8_t length = localGrooves.getSegmentLength(0);
            if (1 < length)
            {
               length--;
               localGrooves.setSegmentLength(0, length);
               clearLaunchpad();
            }
         }
         else if (3 == pad.column)
         {
            uint8_t length = localGrooves.getSegmentLength(0);
            length++;
            localGrooves.setSegmentLength(0, length);
            clearLaunchpad();
         }
      }
      else
      {
         const uint8_t index = launchpadOffset + (7 - pad.row);

         const uint8_t currentTick = localGrooves.getCurrentSegmentTick();
         const uint8_t length = localGrooves.getSegmentLength(0);

         Grooves::Beat beat = localGrooves.getBeat(0);

         const uint8_t lastFullRow = length - (length % 8);
         const uint8_t fullRows = lastFullRow / 8;
         const uint8_t numberOfRows = (length == lastFullRow) ? fullRows : 1 + fullRows;

         const uint8_t laneOffset = index % numberOfRows;
         const uint8_t laneIndex = (index - laneOffset) / numberOfRows;

         const uint8_t tick = pad.column + (laneOffset * 8);
         if (tick >= length)
            continue;

         beat.at(tick).flip(laneIndex);
         localGrooves.setBeat(0, beat);
      }
   }

   if (!displayGroove(localGrooves))
      return;

   displayContours();
   updateLaunchpad(localGrooves);
}

void GrooveMaestro::updateDisplayRemote()
{
   controller.setColor(Color::Predefined::Cyan);
   controller.drawRect(0, 0, 130, 10, true);

   controller.setColor(Color::Predefined::Black);
   controller.writeText(65, 0, "Remote", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   if (!displayGroove(localGrooves))
      return;

   displayContours();

   launchpad.triggeredPads(); // clear buffer
   updateLaunchpad(localGrooves);
}

void GrooveMaestro::updateDisplayPlay()
{
   controller.setColor(Color::Predefined::Green);
   controller.drawRect(0, 0, 130, 10, true);

   controller.setColor(Color::Predefined::Black);
   controller.writeText(65, 0, "Play", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   if (!displayGroove(conductor))
      return;

   displayContours();
   launchpad.triggeredPads(); // clear buffer
   updateLaunchpad(conductor);
}

void GrooveMaestro::displayStoped()
{
   const uint32_t segmentCount = conductor.getSegmentCount();
   const uint16_t digitCount = Variable::compileDigitCount(segmentCount);

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
}

bool GrooveMaestro::displayGroove(const Grooves& grooves)
{
   const Tempo tempo = getTempo();
   const bool on = tempo.isRunningOrFirstTick();
   const uint32_t segmentCount = grooves.getSegmentCount();

   if (0 == segmentCount || !on)
   {
      displayStoped();
      return false;
   }

   // top row
   const uint16_t digitCount = Variable::compileDigitCount(segmentCount);
   const uint32_t segmentIndex = grooves.getCurrentSegmentIndex();

   controller.setColor(Color::Predefined::White);
   controller.writeText(5, 12, Text::pad(std::to_string(segmentIndex), digitCount), Svin::DisplayOLED::Font::Large);

   const std::string eventName = grooves.getSegmentName(segmentIndex);
   const std::string eventText = eventName.empty() ? "--" : eventName;
   controller.writeText(7 + 12 * digitCount, 17, eventText, Svin::DisplayOLED::Font::Normal);

   // the grid
   const Grooves::Gates& gates = grooves.getGates(segmentIndex);
   const bool hasGates = grooves.hasGates(segmentIndex);

   const Grooves::Beat& beat = grooves.getBeat(segmentIndex);
   const bool hasBeat = grooves.hasBeat(segmentIndex);
   const uint8_t currentTick = grooves.getCurrentSegmentTick();
   const uint8_t length = grooves.getSegmentLength(segmentIndex);

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

   return true;
}

void GrooveMaestro::displayContours()
{
   for (uint8_t laneIndex = 0; laneIndex < conductor.getContourCount(); laneIndex++)
   {
      const Contour& contour = conductor.getContour(laneIndex);
      controller.setColor(Color(155, 155, 155));

      const uint8_t column = (laneIndex < 8) ? 0 : 1;
      const uint8_t row = (laneIndex < 8) ? laneIndex : laneIndex - 8;

      const uint8_t y = 133 + 14 * row;

      std::string name = contour.getName();
      if (name.length() > 4)
         name = name.substr(0, 4);
      const uint8_t xName = 5 + (column * 64);
      controller.writeText(xName, y + 3, name, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Left);

      controller.setColor(Color::Predefined::White);

      const float voltage = contourOutput.getVoltage(laneIndex);
      const uint8_t value = voltageToValue(voltage);
      const std::string valueText = Text::convert(value);
      const uint8_t xVoltage = 55 + (column * 64);

      controller.writeText(xVoltage, y, valueText, 14, Svin::DisplayOLED::Alignment::Right);
   }
}

void GrooveMaestro::connectToLaunchpad()
{
   launchpad.connect(deviceId);
   if (!launchpad.isConnected())
      return;

   for (uint8_t col = 0; col < 8; col++)
      launchpad.setPad(8, col, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::White);

   clearLaunchpad();
}

void GrooveMaestro::updateLaunchpad(const Grooves& grooves)
{
   const uint32_t segmentIndex = grooves.getCurrentSegmentIndex();
   const uint8_t currentTick = grooves.getCurrentSegmentTick();
   const uint8_t length = grooves.getSegmentLength(segmentIndex);

   const Grooves::Gates& gates = grooves.getGates(segmentIndex);
   for (uint8_t row = 0; row < 8; row++)
   {
      const uint8_t index = 7 - row;
      const Color color = gates.get(index) ? Color::Predefined::Yellow : Color::Predefined::Blue;
      launchpad.setPad(row, 8, Svin::LaunchpadClient::Mode::Steady, color);
   }

   const Grooves::Beat& beat = grooves.getBeat(segmentIndex);

   const uint8_t lastFullRow = length - (length % 8);
   const uint8_t fullRows = lastFullRow / 8;
   const uint8_t numberOfRows = (length == lastFullRow) ? fullRows : 1 + fullRows;

   const uint8_t maxOffset = 8 * (numberOfRows - 1);
   if (maxOffset < launchpadOffset)
      launchpadOffset = maxOffset;

   for (uint8_t laneIndex = 0; laneIndex < 8; laneIndex++)
   {
      const uint8_t rowOffset = laneIndex * numberOfRows;
      const uint8_t laneColorIndex = (10 * laneIndex) + 5;

      for (uint8_t index = 0; index < length; index++)
      {
         const uint8_t col = (index % 8);
         const uint8_t row = rowOffset + ((index - col) / 8);
         if (row < launchpadOffset)
            continue;
         if (row >= launchpadOffset + 8)
            break;

         if (index == currentTick)
            launchpad.setPad(launchpadOffset + 7 - row, col, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::White);
         else if (beat.at(index).get(laneIndex))
            launchpad.setPad(launchpadOffset + 7 - row, col, Svin::LaunchpadClient::Mode::Steady, laneColorIndex);
         else
            launchpad.setPad(launchpadOffset + 7 - row, col, Svin::LaunchpadClient::Mode::Steady, laneColorIndex + 2);
      }
   }
}

void GrooveMaestro::clearLaunchpad()
{
   for (uint8_t row = 0; row < 8; row++)
   {
      for (uint8_t col = 0; col < 8; col++)
      {
         launchpad.setPad(row, col, Svin::LaunchpadClient::Mode::Off, 0);
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
