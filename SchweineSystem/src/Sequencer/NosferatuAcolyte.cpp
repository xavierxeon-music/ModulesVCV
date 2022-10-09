#include "NosferatuAcolyte.h"

#include "NosferatuVampyre.h"

Nosferatu::Acolyte::Acolyte()
   : Svin::Module()
   // operation
   , banks{}
   , state{}
   , pushBank(false)
   , expanderActive(10)
   // display
   , display(this, Panel::Text_Number)
   // segments
   , currentLightList(this)
   , pitchSliderList(this)
   , tickSliderList(this)
   , lengthKnobList(this)
   , chanceKnobList(this)
   , activeButtonList(this)
{
   setup();
   registerAsBusModule<State>(); // from master
   registerAsBusModule<Bank>();  // to master

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
      currentLightList[index]->setDefaultColor(Color(255, 255, 0));
      currentLightList[index]->setOn();

      pitchSliderList[index]->setRange(0.0, 24.0);
      pitchSliderList[index]->enableSteps(true);
      pitchSliderList[index]->setOff();

      tickSliderList[index]->setRange(1.0, 16.0, 2.0);
      tickSliderList[index]->enableSteps(true);
      tickSliderList[index]->setDefaultColor(Color(0, 0, 255));
      tickSliderList[index]->setOn();

      lengthKnobList[index]->setRange(0.0, 1.0, 0.5);
      lengthKnobList[index]->enableSteps(true, 0.1);

      chanceKnobList[index]->setRange(0.0, 1.0, 1.0);
      chanceKnobList[index]->enableSteps(true, 0.05);

      activeButtonList[index]->setDefaultColor(Color(0, 255, 0));
      activeButtonList[index]->setOn();
   }

   display.setColor(Color(255, 255, 0));

   bankChange();
}

void Nosferatu::Acolyte::process(const ProcessArgs& args)
{
   const State newState = getBusData<State>(Side::Left);
   sendBusData<State>(Side::Right, newState);

   const bool update = (newState.bankIndex != state.bankIndex);
   state = newState;

   if (state.needsExpanderBanks)
      pushBank = true;

   if (update)
   {
      pushBank = true;
      bankChange();
   }

   for (uint8_t index = 0; index < 8; index++)
   {
      if (activeButtonList[index]->isTriggered())
      {
         expanderActive = index;
         pushBank = true;
      }
   }
}

void Nosferatu::Acolyte::updateDisplays()
{
   static const uint8_t noteBaseValue = Note::availableNotes.at(1).midiValue;

   Vampyre* mainModule = findFirstBusModule<State, Vampyre>(Side::Left);
   uint8_t counter = indexOfBusModule<State>(Side::Left, mainModule);
   display.setText(std::to_string(counter));

   // bank update and lights
   Bank& currentBank = banks[state.bankIndex];
   for (uint8_t index = 0; index < 8; index++)
   {
      const uint8_t pitch = pitchSliderList[index]->getValue();
      if (pitch != currentBank.segments[index].pitch)
      {
         currentBank.segments[index].pitch = pitch;
         pushBank = true;
      }

      const uint8_t ticks = tickSliderList[index]->getValue();
      if (ticks != currentBank.segments[index].ticks)
      {
         currentBank.segments[index].ticks = ticks;
         pushBank = true;
      }

      const float length = lengthKnobList[index]->getValue();
      if (length != currentBank.segments[index].length)
      {
         currentBank.segments[index].length = length;
         pushBank = true;
      }

      const float chance = chanceKnobList[index]->getValue();
      if (chance != currentBank.segments[index].chance)
      {
         currentBank.segments[index].chance = chance;
         pushBank = true;
      }

      const uint8_t totalIndex = (8 * counter) + index;
      if (0 == counter)
      {
         currentLightList[index]->setOff();
         pitchSliderList[index]->setOff();
         tickSliderList[index]->setOff();
         activeButtonList[index]->setOff();
      }
      else
      {
         const bool active = (totalIndex == state.currentSegmentIndex);
         if (active)
         {
            if (!state.playCurrentSegment)
               currentLightList[index]->setColor(Color(0, 0, 255));
            else
               currentLightList[index]->setOn(); // sets default color
         }
         else
            currentLightList[index]->setOff();

         const Note note = Note::fromMidi(noteBaseValue + state.pitchOffset + currentBank.segments[index].pitch);
         pitchSliderList[index]->setColor(Note::colorMap.at(note.value));

         const bool evenTick = (0 == (currentBank.segments[index].ticks % 2));
         tickSliderList[index]->setBrightness(evenTick ? 1.0 : 0.2);

         activeButtonList[index]->setActive(totalIndex < state.maxActive);
      }
   }

   if (mainModule && pushBank)
   {
      Svin::Json::Object object;
      object.set("index", counter);

      if (10 != expanderActive)
      {
         const uint8_t totalActive = (8 * counter) + expanderActive + 1;
         object.set("active", totalActive);
         expanderActive = 10;
      }

      broadcastMessage<Bank>(currentBank, object, mainModule);

      pushBank = false;
   }
}

void Nosferatu::Acolyte::bankChange()
{
   const Bank& currentBank = banks[state.bankIndex];

   for (uint8_t index = 0; index < 8; index++)
   {
      const Segment& segment = currentBank.segments[index];
      pitchSliderList[index]->setValue(segment.pitch);
      tickSliderList[index]->setValue(segment.ticks);
      lengthKnobList[index]->setValue(segment.length);
      chanceKnobList[index]->setValue(segment.chance);
   }

}

void Nosferatu::Acolyte::load(const Svin::Json::Object& rootObject)
{
   for (uint8_t index = 0; index < 16; index++)
   {
      Bank& currentBank = banks[index];

      const std::string bankKey = "b" + Text::pad(std::to_string(index), 2);
      const Svin::Json::Object bankObject = rootObject.get(bankKey).toObject();

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

   bankChange();
}

void Nosferatu::Acolyte::save(Svin::Json::Object& rootObject)
{
   for (uint8_t bankIndex = 0; bankIndex < 16; bankIndex++)
   {
      const Bank& currentBank = banks[bankIndex];

      Svin::Json::Object bankObject;

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

      const std::string bankKey = "b" + Text::pad(std::to_string(bankIndex), 2);
      rootObject.set(bankKey, bankObject);
   }
}

// widget

Nosferatu::AcolyteWidget::AcolyteWidget(Acolyte* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelNosferatuAcolyte = Svin::Origin::the()->addModule<Nosferatu::Acolyte, Nosferatu::AcolyteWidget>("NosferatuAcolyte");
