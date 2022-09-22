#include "NosferatuVampyre.h"

#include <Tools/Text.h>
#include <Tools/Variable.h>

Nosferatu::Vampyre::Vampyre()
   : Svin::Module()
   , Svin::MasterClock::Client()
   , Svin::Message<Bank>::Subscriber(this)
   // operation
   , banks{}
   , bankIndex(0)
   , currentSegmentIndex(0)
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
   registerAsBusModule<Nosferatu::Bus>();

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
      currentLightList[index]->setDefaultColor(Svin::Color{255, 255, 0});
      currentLightList[index]->setOn();

      pitchSliderList[index]->setRange(0.0, 24.0);
      pitchSliderList[index]->enableSteps(true);
      pitchSliderList[index]->setOff();

      tickSliderList[index]->setRange(1.0, 16.0, 2.0);
      tickSliderList[index]->enableSteps(true);
      tickSliderList[index]->setDefaultColor(Svin::Color{0, 0, 255});
      tickSliderList[index]->setOn();

      lengthKnobList[index]->setRange(0.0, 1.0, 0.5);
      lengthKnobList[index]->enableSteps(true, 0.1);

      chanceKnobList[index]->setRange(0.0, 1.0, 1.0);
      chanceKnobList[index]->enableSteps(true, 0.05);

      activeButtonList[index]->setDefaultColor(Svin::Color{0, 255, 0});
      activeButtonList[index]->setOn();
   }

   displayController.setColor(Svin::Color{255, 255, 0});

   offsetKnob.setRange(0.0, 11.0);
   offsetKnob.enableSteps(true);
}

void Nosferatu::Vampyre::process(const ProcessArgs& args)
{
   // user interaction
   if (bankInput.isConnected())
   {
   }
   else
   {
      Variable::Integer<uint8_t> var(bankIndex, 0, 15, true);
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

   const Bank& currentBank = updateBank();
   if (!displayOverride.process(args.sampleTime))
      displayType = DisplayType::Bank;

   // sequence
   if (hasReset())
   {
      currentSegmentIndex = 0;
      tickCounter = 0;
      updateSegment();
      return;
   }

   firstOutput.setActive(0 == currentSegmentIndex);

   const Segment& currentSegment = currentBank.segments[currentSegmentIndex];

   static const uint8_t noteBaseValue = Note::availableNotes.at(1).midiValue;
   const uint8_t midiValue = noteBaseValue + currentBank.offset + currentSegment.pitch;
   const Note note = Note::fromMidi(midiValue);
   pitchOutput.setVoltage(note.voltage);

   const Tempo tempo = getTempo();
   const float tickPercentage = tempo.getPercentage();

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
      if (tickCounter >= currentBank.segments[currentSegmentIndex].ticks)
      {
         tickCounter = 0;
         currentSegmentIndex++;

         if (currentSegmentIndex >= currentBank.maxActive)
            currentSegmentIndex = 0;

         updateSegment();
      }
   }
}

const Nosferatu::Bank& Nosferatu::Vampyre::updateBank()
{
   Bank& currentBank = banks[bankIndex];

   for (uint8_t index = 0; index < 8; index++)
   {
      if (activeButtonList[index]->isTriggered())
         currentBank.maxActive = index + 1;

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

   const uint8_t offset = offsetKnob.getValue();
   if (offset != currentBank.offset)
   {
      currentBank.offset = offset;
      setDisplay(DisplayType::Offset, offset);
   }

   return currentBank;
}

void Nosferatu::Vampyre::updateDisplays()
{
   static const uint8_t noteBaseValue = Note::availableNotes.at(1).midiValue;

   // lights
   const Bank& currentBank = banks[bankIndex];
   for (uint8_t index = 0; index < 8; index++)
   {
      currentLightList[index]->setActive(index == currentSegmentIndex);

      const Note note = Note::fromMidi(noteBaseValue + currentBank.offset + currentBank.segments[index].pitch);
      pitchSliderList[index]->setColor(Svin::Color::noteMap.at(note.value));

      const bool evenTick = (0 == (currentBank.segments[index].ticks % 2));
      tickSliderList[index]->setBrightness(evenTick ? 1.0 : 0.2);

      activeButtonList[index]->setActive(index < currentBank.maxActive);
   }

   if (DisplayType::Bank == displayType)
   {
      displayController.setColor(Svin::Color{255, 255, 0});
      const std::string displayText = "b" + Text::pad(std::to_string(bankIndex + 1), 2);
      displayController.setText(displayText);
   }
   else if (DisplayType::Pitch == displayType)
   {
      displayController.setColor(Svin::Color{255, 255, 255});
      const Note note = Note::fromMidi(noteBaseValue + currentBank.offset + displayValue);
      displayController.setText(note.name);
   }
   else if (DisplayType::Ticks == displayType)
   {
      displayController.setColor(Svin::Color{0, 0, 255});
      const std::string displayText = "t" + Text::pad(std::to_string(displayValue), 2);
      displayController.setText(displayText);
   }
   else if (DisplayType::Offset == displayType)
   {
      displayController.setColor(Svin::Color{255, 0, 255});
      const Note note = Note::fromMidi(noteBaseValue + displayValue);
      displayController.setText(note.name);
   }
}

void Nosferatu::Vampyre::bankChange()
{
   const Bank& currentBank = banks[bankIndex];
   if (currentSegmentIndex >= currentBank.maxActive)
   {
      currentSegmentIndex = 0;
      updateSegment();
      if (tickCounter >= currentBank.segments[currentSegmentIndex].ticks)
         tickCounter = 0;
   }

   for (uint8_t index = 0; index < 8; index++)
   {
      const Segment& segment = currentBank.segments[index];
      pitchSliderList[index]->setValue(segment.pitch);
      tickSliderList[index]->setValue(segment.ticks);
      lengthKnobList[index]->setValue(segment.length);
      chanceKnobList[index]->setValue(segment.chance);
   }

   offsetKnob.setValue(currentBank.offset);

   displayType = DisplayType::Bank;
   displayOverride.reset();

   Nosferatu::Bus message;
   message.bankIndex = bankIndex;
   sendBusMessage(Side::Right, message);
}

void Nosferatu::Vampyre::setDisplay(const DisplayType newType, const uint8_t value)
{
   displayType = newType;
   displayValue = value;
   displayOverride.trigger(3.0);
}

void Nosferatu::Vampyre::updateSegment()
{
   Bank& currentBank = banks[bankIndex];

   for (uint8_t index = 0; index < 16; index++)
   {
      Segment& currentSegment = currentBank.segments[currentSegmentIndex];
      const float random = 2.0 * noiseGenerator.value() - 1.0;
      currentSegment.play = (random <= currentSegment.chance);
   }
}

void Nosferatu::Vampyre::load(const Svin::Json::Object& rootObject)
{
   bankIndex = rootObject.get("currentBank").toInt();

   for (uint8_t bankIndex = 0; bankIndex < 16; bankIndex++)
   {
      Bank& currentBank = banks[bankIndex];

      const std::string bankKey = "b" + Text::pad(std::to_string(bankIndex), 2);
      const Svin::Json::Object bankObject = rootObject.get(bankKey).toObject();

      currentBank.maxActive = bankObject.get("max").toInt();
      currentBank.offset = bankObject.get("offset").toInt();

      for (uint8_t index = 0; index < 8; index++)
      {
         const std::string segmentKey = "s" + Text::pad(std::to_string(index), 2);
         Svin::Json::Object segmentObject = bankObject.get(segmentKey).toObject();

         currentBank.segments[index].pitch = segmentObject.get("pitch").toInt();
         currentBank.segments[index].ticks = segmentObject.get("ticks").toInt();
         currentBank.segments[index].length = segmentObject.get("length").toReal();
         currentBank.segments[index].chance = segmentObject.get("chance").toReal();
      }
   }

   displayType = DisplayType::Bank;
   displayOverride.reset();

   currentSegmentIndex = 0;
   tickCounter = 0;
   bankChange();
}

void Nosferatu::Vampyre::save(Svin::Json::Object& rootObject)
{
   rootObject.set("currentBank", bankIndex);

   for (uint8_t bankIndex = 0; bankIndex < 8; bankIndex++)
   {
      const Bank& currentBank = banks[bankIndex];

      Svin::Json::Object bankObject;
      bankObject.set("max", currentBank.maxActive);
      bankObject.set("offset", currentBank.offset);

      for (uint8_t index = 0; index < 16; index++)
      {
         Svin::Json::Object segmentObject;
         segmentObject.set("pitch", currentBank.segments[index].pitch);
         segmentObject.set("ticks", currentBank.segments[index].ticks);
         segmentObject.set("length", currentBank.segments[index].length);
         segmentObject.set("chance", currentBank.segments[index].chance);

         const std::string segmentKey = "s" + Text::pad(std::to_string(index), 2);
         bankObject.set(segmentKey, segmentObject);
      }

      const std::string bankKey = "b" + Text::pad(std::to_string(bankIndex), 2);
      rootObject.set(bankKey, bankObject);
   }
}

void Nosferatu::Vampyre::receive(const Bank& bank, Module* sender)
{
}

// widget

Nosferatu::VampyreWidget::VampyreWidget(Vampyre* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelNosferatuVampyre = Svin::Origin::the()->addModule<Nosferatu::Vampyre, Nosferatu::VampyreWidget>("NosferatuVampyre");
