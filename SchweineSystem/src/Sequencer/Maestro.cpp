#include "Maestro.h"

#include <Tools/File.h>
#include <Tools/Text.h>
#include <Tools/Variable.h>

Maestro::Maestro()
   : Svin::Module()
   , Svin::MasterClock::Client()
   , fileName()
   , timeStamp(-1)
   , conductor()
   , localGrooves()
   , localStages()
   , voltages()
   , tickTriggers(0)
   , segmentGates(0)
   , unitGuard{}
   // control
   , display(this)
   , launchpad(this)
   // input
   , uploadInput(this, Panel::Upload)
   , contoutPassInput(this, Panel::ContourPass)
   , gatePassInput(this, Panel::GatePass)
   , noOffsetSwitch(this, Panel::NoOffset)
   // output
   , contourOutput(this, Panel::ContourOutput)
   , gateOutput(this, Panel::GateOutput)
   , valueToVoltage(0.0, 255.0, 0.0, 10.0)
   , triggerGenerator()
   , busMessage()
   // mode
   , loopButton(this, Panel::Loop, Panel::RGB_Loop)
   , operationMode(OperationMode::Passthrough)
   , modeButtonPass(this, Panel::ModePass, Panel::RGB_ModePass)
   , modeButtonRemote(this, Panel::ModeRemote, Panel::RGB_ModeRemote)
   , modeButtonReplay(this, Panel::ModeReplay, Panel::RGB_ModeReplay)
   , operationModeMap()

   // other

   , voltageToValue(0.0, 10.0, 0.0, 255.0)
{
   setup();
   registerHubClient("Maestro");
   registerAsBusModule<Svin::Midi::Bus>();

   localGrooves.update(16, 1);
   Grooves::Beat beat(16, BoolField8(0));
   localGrooves.setBeat(0, beat);
   localGrooves.setGates(0, BoolField8(0));
   localGrooves.setLooping(true);

   localStages.update(16, 1);
   Stages::Segment segment(16, Stages::Unit());
   localStages.setSegment(0, 0, segment);
   localStages.setLooping(true);

   voltages = std::vector<float>(16, 0.0);

   loopButton.setDefaultColor(Color::Predefined::Green);

   modeButtonPass.setDefaultColor(Color::Predefined::Yellow);
   operationModeMap[OperationMode::Passthrough] = &modeButtonPass;

   modeButtonRemote.setDefaultColor(Color::Predefined::Cyan);
   operationModeMap[OperationMode::Remote] = &modeButtonRemote;

   modeButtonReplay.setDefaultColor(Color::Predefined::Green);
   operationModeMap[OperationMode::Play] = &modeButtonReplay;
}

void Maestro::process(const ProcessArgs& args)
{
   launchpad.client.sendClock();

   if (loopButton.isTriggered())
   {
      bool loop = conductor.isLooping();
      loop ^= true;
      conductor.setLooping(loop);
   }
   loopButton.setActive(conductor.isLooping());

   display.process();
   launchpad.process();

   // operation mode
   if (modeButtonPass.isTriggered())
   {
      operationMode = OperationMode::Passthrough;
      launchpad.updateHeader();
   }
   if (modeButtonRemote.isTriggered())
   {
      operationMode = OperationMode::Remote;
      launchpad.updateHeader();
   }
   if (modeButtonReplay.isTriggered())
   {
      operationMode = OperationMode::Play;
      launchpad.updateHeader();
   }

   contourOutput.setNumberOfChannels(16);
   gateOutput.setNumberOfChannels(16);

   // do stuff

   auto applyZero = [&]()
   {
      for (uint8_t index = 0; index < 16; index++)
      {
         contourOutput.setVoltage(0.0, index);
         gateOutput.setActive(false, index);
      }
   };

   if (hasReset())
   {
      conductor.clockReset();
      localGrooves.clockReset();
      localStages.clockReset();

      unitGuard.tick = 255;
      return applyZero();
   }

   if (conductor.isPastLoop())
      return applyZero();

   const Tempo tempo = getTempo();
   const bool on = tempo.isRunningOrFirstTick();

   if (!on)
      return applyZero();

   BoolField16 triggers(0);

   auto applyValues = [&]()
   {
      for (uint8_t index = 0; index < 16; index++)
      {
         contourOutput.setVoltage(voltages[index], index);
         gateOutput.setActive(triggers.get(index), index);
      }
   };

   auto fillTriggers = [&](Grooves& grooves)
   {
      const uint32_t segmentIndex = grooves.getCurrentSegmentIndex();
      bool isFirstTick = false;
      while (hasTick(&isFirstTick))
      {
         if (!isFirstTick)
            grooves.clockTick();

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
      voltages = std::vector<float>(16, 0.0);

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

      if (gatePassInput.isConnected()) // may override gates!
      {
         for (uint8_t index = 0; index < 8; index++)
         {
            const uint8_t inputIndex = noOffsetSwitch.isOn() ? index : index + 8;
            const float voltage = (inputIndex < gatePassInput.getNumberOfChannels()) ? gatePassInput.getVoltage(inputIndex) : 0.0;

            triggers.set(index + 8, (voltage > 3.0));
         }
      }

      if (uploadInput.isTriggered())
         uploadToHub();

      return applyValues();
   }
   else if (OperationMode::Remote == operationMode)
   {
      fillTriggers(localGrooves);
      return applyValues();
   }
   else if (OperationMode::Play == operationMode)
   {
      fillTriggers(conductor);

      const float tickPercentage = tempo.getPercentage();
      const uint32_t segmentIndex = conductor.getCurrentSegmentIndex();

      // stages
      const uint8_t tick = conductor.getCurrentSegmentTick();
      busMessage = Svin::Midi::Bus{}; // reset
      busMessage.noOfChannels = Stages::laneCount;

      for (uint8_t laneIndex = 0; laneIndex < Stages::laneCount; laneIndex++)
      {
         Svin::Midi::Bus::Channel& channelRef = busMessage.channels[laneIndex];

         auto addNoteOn = [&](const uint8_t midiNote, const uint8_t velocity)
         {
            Bytes message(3);
            message[0] = (Midi::Event::NoteOn | laneIndex);
            message[1] = midiNote;
            message[2] = velocity;

            channelRef.messageList.push_back(message);
            channelRef.hasEvents = true;
         };

         auto addNoteOff = [&](const uint8_t midiNote)
         {
            Bytes message(3);
            message[0] = (Midi::Event::NoteOff | laneIndex);
            message[1] = midiNote;
            message[2] = 0;

            channelRef.messageList.push_back(message);
            channelRef.hasEvents = true;
         };

         const Stages::Unit& unit = conductor.getUnit(laneIndex, segmentIndex, tick);

         UnitGuard::Lane& lane = unitGuard.lanes[laneIndex];
         const Stages::Unit& lastUnit = lane.unit;

         if (unitGuard.tick == tick)
         {
            if (lane.event == Midi::Event::NoteOff)
               continue;

            const float unitLength = (unit.length / 255.0);
            if (tickPercentage < unitLength)
               continue;

            const float overshoot = tickPercentage - unitLength;
            if (overshoot > 0.01) // sometimes tick Percentage is way to high, resulting in click sound
               continue;

            addNoteOff(unit.value1);
            lane.event = Midi::Event::NoteOff;
         }
         else
         {
            if (lane.event != Midi::Event::NoteOff)
            {
               addNoteOff(lastUnit.value1);
               lane.event = Midi::Event::NoteOff;
            }

            if (unit.length > 0.0)
            {
               if (true) // propablilty
                  addNoteOn(unit.value1, unit.value2);
               lane.event = Midi::Event::NoteOn;
            }

            lane.unit.store = unit.store;
         }
      }

      if (unitGuard.tick != tick)
         unitGuard.tick = tick;

      busMessage.runState = Tempo::Running;
      sendBusData<Svin::Midi::Bus>(Side::Right, busMessage);

      // contours
      const float segmentPercentage = conductor.getCurrentSegmentPrecentage(tickPercentage);
      for (uint8_t laneIndex = 0; laneIndex < Contours::laneCount; laneIndex++)
      {
         const uint8_t value = on ? conductor.getSegmentValue(laneIndex, segmentIndex, segmentPercentage) : 0.0;
         const float voltage = valueToVoltage(value);
         voltages[laneIndex] = voltage;
      }

      applyValues();
   }
}

void Maestro::loadProject(const std::string& newFileName)
{
   fileName = newFileName;
   timeStamp = File::getLasModifiedTimeStamp(fileName);

   const Bytes data = File::load(fileName);
   if (data.empty())
      return;

   const Svin::Json::Object rootObject(data);
   Svin::Json::Object projectObject = rootObject.get("project").toObject();

   const uint32_t segmentCount = projectObject.get("segments").toInt();
   const uint16_t digitCount = Variable::compileDigitCount(segmentCount);
   const uint8_t division = projectObject.get("division").toInt();

   auto compileSegmentKey = [&](const uint32_t segmentIndex) -> std::string
   {
      return Text::pad(std::to_string(segmentIndex), digitCount);
   };

   auto compileLaneKy = [](const uint8_t& laneIndex) -> std::string
   {
      return "lane" + Text::pad(std::to_string(laneIndex), 2);
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
      }
   }

   // gates
   {
      Svin::Json::Object gatesObject = rootObject.get("gates").toObject();
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
      Svin::Json::Object beatsObject = rootObject.get("beats").toObject();
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

   // stages
   {
      Svin::Json::Object staggesObject = rootObject.get("stages").toObject();
      for (uint8_t laneIndex = 0; laneIndex < Stages::laneCount; laneIndex++)
      {
         const std::string key = compileLaneKy(laneIndex);
         Svin::Json::Object laneObject = staggesObject.get(key).toObject();

         const std::string name = laneObject.get("name").toString();
         conductor.Stages::setName(laneIndex, name);

         for (uint32_t segmentIndex = 0; segmentIndex < conductor.getSegmentCount(); segmentIndex++)
         {
            const std::string segmentKey = compileSegmentKey(segmentIndex);
            if (!laneObject.hasKey(segmentKey))
               continue;

            Svin::Json::Array unitArray = laneObject.get(segmentKey).toArray();
            const uint8_t length = unitArray.size();
            if (length != conductor.getSegmentLength(segmentIndex))
               continue;

            Stages::Segment segment(length, Stages::Unit());
            for (uint8_t tick = 0; tick < length; tick++)
            {
               segment[tick].store = unitArray.at(tick).toInt();
            }

            conductor.Stages::setSegment(laneIndex, segmentIndex, segment);
         }
      }
   }

   // lanes
   {
      Svin::Json::Object contoursObject = rootObject.get("contours").toObject();
      for (uint8_t laneIndex = 0; laneIndex < Contours::laneCount; laneIndex++)
      {
         const std::string key = compileLaneKy(laneIndex);
         Svin::Json::Object laneObject = contoursObject.get(key).toObject();

         const std::string name = laneObject.get("name").toString();
         conductor.Contours::setName(laneIndex, name);

         for (uint32_t segmentIndex = 0; segmentIndex < conductor.getSegmentCount(); segmentIndex++)
         {
            const std::string segmentKey = compileSegmentKey(segmentIndex);
            if (!laneObject.hasKey(segmentKey))
               continue;

            Contours::Segment segment;
            segment.store = laneObject.get(segmentKey).toInt();
            conductor.Contours::setSegment(laneIndex, segmentIndex, segment);
         }
      }
   }
}

void Maestro::updateDisplays()
{
   for (OperationModeMap::const_iterator it = operationModeMap.cbegin(); it != operationModeMap.cend(); it++)
   {
      const bool on = (it->first == operationMode);
      it->second->setActive(on);
   }

   // relaod if file has changed
   if (-1 != timeStamp)
   {
      long currentTimeStamp = File::getLasModifiedTimeStamp(fileName);
      if (currentTimeStamp != timeStamp)
         return loadProject(fileName);
   }

   launchpad.updateButton();
   display.update();

   const uint32_t index = conductor.getCurrentSegmentIndex();

   Svin::Json::Object object;
   object.set("_Application", "Maestro");
   object.set("_Type", "Index");
   object.set("index", index);
   object.set("mode", static_cast<uint8_t>(operationMode));

   sendDocumentToHub(1, object);
}

void Maestro::uploadToHub()
{
   Svin::Json::Array stateArray;
   /*
   for (uint8_t laneIndex = 0; laneIndex < conductor.getContourCount(); laneIndex++)
   {
      const float voltage = contourOutput.getVoltage(laneIndex);
      const uint8_t value = voltageToValue(voltage);

      stateArray.append(value);
   }
   */

   const uint8_t gateValue = localGrooves.getGates(0);

   const Grooves::Beat beat = localGrooves.getBeat(0);
   const uint8_t length = localGrooves.getSegmentLength(0);

   Svin::Json::Array beatArray;
   for (uint8_t index = 0; index < length; index++)
   {
      const uint8_t triggers = beat.at(index);
      beatArray.append(triggers);
   }

   Svin::Json::Object object;
   object.set("_Application", "Maestro");
   object.set("_Type", "State");
   object.set("state", stateArray);
   object.set("gates", gateValue);
   object.set("length", length);
   object.set("beat", beatArray);

   sendDocumentToHub(1, object);
}

void Maestro::receivedDocumentFromHub(const ::Midi::Channel& channel, const Svin::Json::Object& object, const uint8_t docIndex)
{
   if (1 != channel || 0 != docIndex)
      return;

   const std::string type = object.get("_Type").toString();
   if ("Reload" == type)
   {
      const std::string fileName = object.get("fileName").toString();
      loadProject(fileName);
   }
   else if ("Remote" == type)
   {
      if (OperationMode::Play == operationMode)
      {
         const uint32_t segmentIndex = object.get("index").toInt();
         conductor.setCurrentSegmentIndex(segmentIndex);
      }
      else if (OperationMode::Remote == operationMode)
      {
         /*
         Svin::Json::Array stateArray = object.get("state").toArray();
         for (uint8_t laneIndex = 0; laneIndex < conductor.getContourCount(); laneIndex++)
         {
            const uint8_t value = stateArray.at(laneIndex).toInt();
            voltages[laneIndex] = valueToVoltage(value);
         }

         const BoolField8 gates = object.get("gates").toInt();
         localGrooves.setGates(0, gates);

         const uint8_t length = object.get("length").toInt();
         localGrooves.setSegmentLength(0, length);

         Grooves::Beat beat(length, BoolField8(0));
         Svin::Json::Array beatArray = object.get("beat").toArray();
         for (uint8_t tick = 0; tick < length; tick++)
         {
            const BoolField8 triggers = beatArray.at(tick).toInt();
            beat[tick] = triggers;
         }
         localGrooves.setBeat(0, beat);
         */
      }
   }
}

void Maestro::load(const Svin::Json::Object& rootObject)
{
   operationMode = static_cast<OperationMode>(rootObject.get("operation").toInt());
   display.mode = static_cast<Display::Mode>(rootObject.get("display").toInt());

   launchpad.wantConnection = static_cast<Launchpad::WantConnection>(rootObject.get("launchpad").toInt());
   if (Launchpad::WantConnection::Yes == launchpad.wantConnection)
      launchpad.connectionPrompt.arm();

   const bool loop = rootObject.get("loop").toBool();
   conductor.setLooping(loop);

   const bool no_offset = rootObject.get("no_offset").toBool();
   noOffsetSwitch.setState(no_offset);

   const std::string newFileName = rootObject.get("fileName").toString();
   loadProject(newFileName);

   Svin::Json::Array voltageArray = rootObject.get("voltages").toArray();
   if (voltages.size() < 16)
      voltages = std::vector<float>(16, 0.0);
   for (uint8_t index = 0; index < voltageArray.size(); index++)
      voltages[index] = voltageArray.at(index).toReal();

   const BoolField8 gates = rootObject.get("gates").toInt();
   localGrooves.setGates(0, gates);

   const uint8_t length = rootObject.get("length").toInt();
   localGrooves.setSegmentLength(0, length);

   Grooves::Beat beat(length, BoolField8(0));
   Svin::Json::Array beatArray = rootObject.get("beat").toArray();
   for (uint8_t tick = 0; tick < length; tick++)
      beat[tick] = beatArray.at(tick).toInt();
   localGrooves.setBeat(0, beat);

   // TODO localStages
}

void Maestro::save(Svin::Json::Object& rootObject)
{
   rootObject.set("operation", static_cast<uint8_t>(operationMode));
   rootObject.set("display", static_cast<uint8_t>(display.mode));
   rootObject.set("launchpad", static_cast<uint8_t>(launchpad.wantConnection));
   rootObject.set("loop", conductor.isLooping());
   rootObject.set("no_offset", noOffsetSwitch.isOn());

   rootObject.set("fileName", fileName);

   Svin::Json::Array voltageArray;
   for (uint8_t index = 0; index < voltages.size(); index++)
      voltageArray.append(voltages.at(index));
   rootObject.set("voltages", voltageArray);

   const uint8_t gates = localGrooves.getGates(0);
   rootObject.set("gates", gates);

   const uint8_t length = localGrooves.getSegmentLength(0);
   rootObject.set("length", length);

   Svin::Json::Array beatArray;
   for (uint8_t tick = 0; tick < length; tick++)
   {
      const uint8_t triggers = localGrooves.getTriggers(0, tick);
      beatArray.append(triggers);
   }

   rootObject.set("beat", beatArray);

   // TODO localStages
}

// widget

MaestroWidget::MaestroWidget(Maestro* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelMaestro = Svin::Origin::the()->addModule<Maestro, MaestroWidget>("Maestro");
