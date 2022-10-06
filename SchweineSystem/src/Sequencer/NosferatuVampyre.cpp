#include "NosferatuVampyre.h"

#include <Tools/Text.h>
#include <Tools/Variable.h>

#include "NosferatuAcolyte.h"

Nosferatu::Vampyre::Vampyre()
   : Svin::Module()
   , Svin::MasterClock::Client()
   // operation
   , banks{}
   , state{}
   , playBanks()
   , tickCounter(0)
   , noiseGenerator()
   // display
   , displayType(DisplayType::Bank)
   , displayValue(0)
   , displayOverride()
   // segments
   , currentLightList(this)
   , pitchSliderList(this)
   , tickSliderList(this)
   , lengthKnobList(this)
   , chanceKnobList(this)
   , activeButtonList(this)
   // bank
   , bankInput(this, Panel::BankSelect)
   , bankDownButton(this, Panel::Down)
   , bankUpButton(this, Panel::Up)
   // info
   , displayController(this, Panel::Text_Bank)
   , offsetKnob(this, Panel::Offset)
   // outputs
   , firstOutput(this, Panel::First)
   , pitchOutput(this, Panel::Pitch)
   , gateOutput(this, Panel::Gate)
{
   setup();
   registerAsBusModule<Bank>();  // from expander
   registerAsBusModule<State>(); // to expander

   currentLightList.append({Panel::RGB_Seg01_Current,
                            Panel::RGB_Seg02_Current,
                            Panel::RGB_Seg03_Current,
                            Panel::RGB_Seg04_Current,
                            Panel::RGB_Seg05_Current,
                            Panel::RGB_Seg06_Current,
                            Panel::RGB_Seg07_Current,
                            Panel::RGB_Seg08_Current});

   pitchSliderList.append({{Panel::Seg01_Pitch, Panel::RGB_Seg01_Pitch},
                           {Panel::Seg02_Pitch, Panel::RGB_Seg02_Pitch},
                           {Panel::Seg03_Pitch, Panel::RGB_Seg03_Pitch},
                           {Panel::Seg04_Pitch, Panel::RGB_Seg04_Pitch},
                           {Panel::Seg05_Pitch, Panel::RGB_Seg05_Pitch},
                           {Panel::Seg06_Pitch, Panel::RGB_Seg06_Pitch},
                           {Panel::Seg07_Pitch, Panel::RGB_Seg07_Pitch},
                           {Panel::Seg08_Pitch, Panel::RGB_Seg08_Pitch}});

   tickSliderList.append({{Panel::Seg01_Ticks, Panel::RGB_Seg01_Ticks},
                          {Panel::Seg02_Ticks, Panel::RGB_Seg02_Ticks},
                          {Panel::Seg03_Ticks, Panel::RGB_Seg03_Ticks},
                          {Panel::Seg04_Ticks, Panel::RGB_Seg04_Ticks},
                          {Panel::Seg05_Ticks, Panel::RGB_Seg05_Ticks},
                          {Panel::Seg06_Ticks, Panel::RGB_Seg06_Ticks},
                          {Panel::Seg07_Ticks, Panel::RGB_Seg07_Ticks},
                          {Panel::Seg08_Ticks, Panel::RGB_Seg08_Ticks}});

   lengthKnobList.append({Panel::Seg01_Length,
                          Panel::Seg02_Length,
                          Panel::Seg03_Length,
                          Panel::Seg04_Length,
                          Panel::Seg05_Length,
                          Panel::Seg06_Length,
                          Panel::Seg07_Length,
                          Panel::Seg08_Length});

   chanceKnobList.append({Panel::Seg01_Chance,
                          Panel::Seg02_Chance,
                          Panel::Seg03_Chance,
                          Panel::Seg04_Chance,
                          Panel::Seg05_Chance,
                          Panel::Seg06_Chance,
                          Panel::Seg07_Chance,
                          Panel::Seg08_Chance});

   activeButtonList.append({{Panel::Seg01_Active, Panel::RGB_Seg01_Active},
                            {Panel::Seg02_Active, Panel::RGB_Seg02_Active},
                            {Panel::Seg03_Active, Panel::RGB_Seg03_Active},
                            {Panel::Seg04_Active, Panel::RGB_Seg04_Active},
                            {Panel::Seg05_Active, Panel::RGB_Seg05_Active},
                            {Panel::Seg06_Active, Panel::RGB_Seg06_Active},
                            {Panel::Seg07_Active, Panel::RGB_Seg07_Active},
                            {Panel::Seg08_Active, Panel::RGB_Seg08_Active}});

   for (uint8_t index = 0; index < 8; index++)
   {
      currentLightList[index]->setDefaultColor(Color{255, 255, 0});
      currentLightList[index]->setOn();

      pitchSliderList[index]->setRange(0.0, 24.0);
      pitchSliderList[index]->enableSteps(true);
      pitchSliderList[index]->setOff();

      tickSliderList[index]->setRange(1.0, 16.0, 2.0);
      tickSliderList[index]->enableSteps(true);
      tickSliderList[index]->setDefaultColor(Color{0, 0, 255});
      tickSliderList[index]->setOn();

      lengthKnobList[index]->setRange(0.0, 1.0, 0.5);
      lengthKnobList[index]->enableSteps(true, 0.1);

      chanceKnobList[index]->setRange(0.0, 1.0, 1.0);
      chanceKnobList[index]->enableSteps(true, 0.05);

      activeButtonList[index]->setDefaultColor(Color{0, 255, 0});
      activeButtonList[index]->setOn();
   }

   displayController.setColor(Color{255, 255, 0});

   offsetKnob.setRange(0.0, 11.0);
   offsetKnob.enableSteps(true);

   bankChange();
}

void Nosferatu::Vampyre::process(const ProcessArgs& args)
{
   // user interaction
   if (bankInput.isConnected())
   {
   }
   else
   {
      Variable::Integer<uint8_t> var(state.bankIndex, 0, 15, true);
      if (bankDownButton.isTriggered())
      {
         var.decrement();
         bankChange();
      }
      else if (bankUpButton.isTriggered())
      {
         var.increment();
         bankChange();
      }
   }

   if (!displayOverride.process(args.sampleTime))
      displayType = DisplayType::Bank;

   if (hasReset())
   {
      state.currentSegmentIndex = 0;
      tickCounter = 0;
      updateSegmentPlayChances();
      return;
   }

   // sequence length
   {
      Acolyte* lastAcolyte = findLastBusModule<State, Acolyte>(Side::Right, true);
      const uint8_t bankCount = 1 + indexOfBusModule<State>(Side::Right, lastAcolyte);

      while (playBanks.size() < bankCount)
         playBanks.push_back(Bank{});
      while (playBanks.size() > bankCount)
         playBanks.pop_back();

      const uint8_t maxSteps = 8 * bankCount;

      if (maxSteps < state.maxActive)
      {
         std::cout << (uint16_t)state.maxActive << " " << (uint16_t)maxSteps << " " << (uint16_t)bankCount << std::endl;
         state.maxActive = maxSteps;
      }

      if (maxSteps <= state.currentSegmentIndex)
         state.currentSegmentIndex = maxSteps;
      playBanks[0] = updateCurrentBank();

      state.pitchOffset = playBanks[0].pitchOffset;
   }

   while (hasMessage<Bank>())
   {
      const Message<Bank> message = popMessage<Bank>();

      uint8_t expanderIndex = message.document.get("index").toInt();
      playBanks[expanderIndex] = message.data;

      if (message.document.hasKey("active"))
      {
         const uint8_t expanderActive = message.document.get("active").toInt();
         state.maxActive = expanderActive;

         std::cout << __FUNCTION__ << " " << (uint16_t)expanderActive << std::endl;
      }
   }

   firstOutput.setActive(0 == state.currentSegmentIndex);

   const Tempo tempo = getTempo();
   const float tickPercentage = tempo.getPercentage();

   const uint8_t segmentIndex = state.currentSegmentIndex % 8;
   const uint8_t expanderIndex = (state.currentSegmentIndex - segmentIndex) / 8;
   const Bank& currentBank = playBanks[expanderIndex];

   // pitch and gate
   const Segment& currentSegment = currentBank.segments[segmentIndex];

   static const uint8_t noteBaseValue = Note::availableNotes.at(1).midiValue;
   const uint8_t midiValue = noteBaseValue + currentBank.pitchOffset + currentSegment.pitch;
   const Note note = Note::fromMidi(midiValue);
   pitchOutput.setVoltage(note.voltage);

   float currentTick = tickCounter;
   const float maxTick = currentSegment.ticks;
   if (currentTick != maxTick && 0.0 < tickPercentage && 1.0 > tickPercentage)
      currentTick += tickPercentage;

   const float segmentPercentage = currentTick / maxTick;
   const float segmentLength = currentSegment.length;
   const bool on = (segmentPercentage <= segmentLength) && currentSegment.play;
   if (tempo.isRunningOrFirstTick())
      gateOutput.setActive(on);
   else
      gateOutput.setOff();

   // advance
   while (hasTick())
   {
      if (tempo.getRunState() == Tempo::FirstTick)
         continue;

      tickCounter++;
      if (tickCounter >= currentBank.segments[segmentIndex].ticks)
      {
         tickCounter = 0;
         state.currentSegmentIndex++;

         if (state.currentSegmentIndex >= state.maxActive)
            state.currentSegmentIndex = 0;

         updateSegmentPlayChances();
      }
   }

   sendBusData<State>(Side::Right, state);
}

const Nosferatu::Bank& Nosferatu::Vampyre::updateCurrentBank()
{
   Bank& currentBank = banks[state.bankIndex];

   for (uint8_t index = 0; index < 8; index++)
   {
      if (activeButtonList[index]->isTriggered())
         state.maxActive = index + 1;

      const uint8_t pitch = pitchSliderList[index]->getValue();
      if (pitch != currentBank.segments[index].pitch)
      {
         currentBank.segments[index].pitch = pitch;
         setDisplay(DisplayType::Pitch, pitch);
      }

      const uint8_t ticks = tickSliderList[index]->getValue();
      if (ticks != currentBank.segments[index].ticks)
      {
         currentBank.segments[index].ticks = ticks;
         setDisplay(DisplayType::Ticks, ticks);
      }
      currentBank.segments[index].length = lengthKnobList[index]->getValue();
      currentBank.segments[index].chance = chanceKnobList[index]->getValue();
   }

   const uint8_t pitchOffset = offsetKnob.getValue();
   if (pitchOffset != currentBank.pitchOffset)
   {
      currentBank.pitchOffset = pitchOffset;
      setDisplay(DisplayType::Offset, pitchOffset);
   }

   return currentBank;
}

void Nosferatu::Vampyre::updateDisplays()
{
   static const uint8_t noteBaseValue = Note::availableNotes.at(1).midiValue;

   // lights
   const Bank& currentBank = playBanks[0];
   for (uint8_t index = 0; index < 8; index++)
   {
      currentLightList[index]->setActive(index == state.currentSegmentIndex);

      const Note note = Note::fromMidi(noteBaseValue + currentBank.pitchOffset + currentBank.segments[index].pitch);
      pitchSliderList[index]->setColor(Note::colorMap.at(note.value));

      const bool evenTick = (0 == (currentBank.segments[index].ticks % 2));
      tickSliderList[index]->setBrightness(evenTick ? 1.0 : 0.2);

      activeButtonList[index]->setActive(index < state.maxActive);
   }

   if (DisplayType::Bank == displayType)
   {
      displayController.setColor(Color{255, 255, 0});
      const std::string displayText = "b" + Text::pad(std::to_string(state.bankIndex + 1), 2);
      displayController.setText(displayText);
   }
   else if (DisplayType::Pitch == displayType)
   {
      displayController.setColor(Color{255, 255, 255});
      const Note note = Note::fromMidi(noteBaseValue + currentBank.pitchOffset + displayValue);
      displayController.setText(note.name);
   }
   else if (DisplayType::Ticks == displayType)
   {
      displayController.setColor(Color{0, 0, 255});
      const std::string displayText = "t" + Text::pad(std::to_string(displayValue), 2);
      displayController.setText(displayText);
   }
   else if (DisplayType::Offset == displayType)
   {
      displayController.setColor(Color{255, 0, 255});
      const Note note = Note::fromMidi(noteBaseValue + displayValue);
      displayController.setText(note.name);
   }
}

void Nosferatu::Vampyre::bankChange()
{
   const Bank& currentBank = banks[state.bankIndex];

   state.currentSegmentIndex = 0;
   tickCounter = 0;
   updateSegmentPlayChances();

   for (uint8_t index = 0; index < 8; index++)
   {
      const Segment& segment = currentBank.segments[index];
      pitchSliderList[index]->setValue(segment.pitch);
      tickSliderList[index]->setValue(segment.ticks);
      lengthKnobList[index]->setValue(segment.length);
      chanceKnobList[index]->setValue(segment.chance);
   }

   offsetKnob.setValue(currentBank.pitchOffset);

   displayType = DisplayType::Bank;
   displayOverride.reset();
}

void Nosferatu::Vampyre::setDisplay(const DisplayType newType, const uint8_t value)
{
   displayType = newType;
   displayValue = value;
   displayOverride.trigger(3.0);
}

void Nosferatu::Vampyre::updateSegmentPlayChances()
{
   return;
   Bank& currentBank = banks[0];

   for (uint8_t index = 0; index < 8; index++)
   {
      Segment& currentSegment = currentBank.segments[state.currentSegmentIndex];
      const float random = 2.0 * noiseGenerator.value() - 1.0;
      currentSegment.play = (random <= currentSegment.chance);
   }
}

void Nosferatu::Vampyre::load(const Svin::Json::Object& rootObject)
{
   state.bankIndex = rootObject.get("currentBank").toInt();
   state.maxActive = rootObject.get("maxActive").toInt();

   for (uint8_t index = 0; index < 16; index++)
   {
      Bank& currentBank = banks[index];

      const std::string bankKey = "b" + Text::pad(std::to_string(index), 2);
      const Svin::Json::Object bankObject = rootObject.get(bankKey).toObject();

      currentBank.pitchOffset = bankObject.get("pitchOffset").toInt();

      for (uint8_t segmentIndex = 0; segmentIndex < 8; segmentIndex++)
      {
         const std::string segmentKey = "s" + Text::pad(std::to_string(segmentIndex), 2);
         Svin::Json::Array segmentArray = bankObject.get(segmentKey).toArray();

         currentBank.segments[segmentIndex].pitch = segmentArray.at(0).toInt();
         currentBank.segments[segmentIndex].ticks = segmentArray.at(1).toInt();
         currentBank.segments[segmentIndex].length = segmentArray.at(2).toReal();
         currentBank.segments[segmentIndex].chance = segmentArray.at(3).toReal();
      }
   }

   displayType = DisplayType::Bank;
   displayOverride.reset();

   state.currentSegmentIndex = 0;
   tickCounter = 0;
   bankChange();
}

void Nosferatu::Vampyre::save(Svin::Json::Object& rootObject)
{
   rootObject.set("currentBank", state.bankIndex);
   rootObject.set("maxActive", state.maxActive);

   for (uint8_t index = 0; index < 16; index++)
   {
      const Bank& currentBank = banks[index];

      Svin::Json::Object bankObject;
      bankObject.set("pitchOffset", currentBank.pitchOffset);

      for (uint8_t segmentIndex = 0; segmentIndex < 8; segmentIndex++)
      {
         Svin::Json::Array segmentArray;
         segmentArray.append(currentBank.segments[segmentIndex].pitch);
         segmentArray.append(currentBank.segments[segmentIndex].ticks);
         segmentArray.append(currentBank.segments[segmentIndex].length);
         segmentArray.append(currentBank.segments[segmentIndex].chance);

         const std::string segmentKey = "s" + Text::pad(std::to_string(segmentIndex), 2);
         bankObject.set(segmentKey, segmentArray);
      }

      const std::string bankKey = "b" + Text::pad(std::to_string(index), 2);
      rootObject.set(bankKey, bankObject);
   }
}

// widget

Nosferatu::VampyreWidget::VampyreWidget(Vampyre* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelNosferatuVampyre = Svin::Origin::the()->addModule<Nosferatu::Vampyre, Nosferatu::VampyreWidget>("NosferatuVampyre");
