#include "NosferatuAcolyte.h"

#include "NosferatuVampyre.h"

Nosferatu::Acolyte::Acolyte()
   : Svin::Module()
   // operation
   , banks{}
   , bankIndex(0)
   , currentSegmentIndex(-1)
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

   display.setColor(Svin::Color{255, 255, 0});

   bankChange();
}

void Nosferatu::Acolyte::process(const ProcessArgs& args)
{
   const Nosferatu::Bus message = getBusData<Nosferatu::Bus>(Side::Left);
   if (message.bankIndex != bankIndex)
   {
      bankIndex = message.bankIndex;
      bankChange();
   }
   sendBusData<Nosferatu::Bus>(Side::Right, message);

   Vampyre* mainModule = findFirstBusModule<Nosferatu::Bus, Vampyre>(Side::Left);
   uint8_t counter = indexOfBusModule<Nosferatu::Bus>(Side::Left, mainModule);
   display.setText(std::to_string(counter));

   Bank& currentBank = banks[bankIndex];
   for (uint8_t index = 0; index < 8; index++)
   {
      if (activeButtonList[index]->isTriggered())
      {
         currentBank.maxActive = index + 1;
         //publishMessage(currentBank);
      }
   }
}

void Nosferatu::Acolyte::updateDisplays()
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
}

void Nosferatu::Acolyte::bankChange()
{
   const Bank& currentBank = banks[bankIndex];

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
   bankIndex = rootObject.get("currentBank").toInt();

   for (uint8_t bankIndex = 0; bankIndex < 16; bankIndex++)
   {
      Bank& currentBank = banks[bankIndex];

      const std::string bankKey = "b" + Text::pad(std::to_string(bankIndex), 2);
      const Svin::Json::Object bankObject = rootObject.get(bankKey).toObject();

      currentBank.maxActive = bankObject.get("max").toInt();

      for (uint8_t index = 0; index < 8; index++)
      {
         const std::string segmentKey = "s" + Text::pad(std::to_string(index), 2);
         Svin::Json::Array segmentArray = bankObject.get(segmentKey).toArray();

         currentBank.segments[index].pitch = segmentArray.at(0).toInt();
         currentBank.segments[index].ticks = segmentArray.at(1).toInt();
         currentBank.segments[index].length = segmentArray.at(2).toReal();
         currentBank.segments[index].chance = segmentArray.at(3).toReal();
      }
   }

   currentSegmentIndex = -1;
   bankChange();
}

void Nosferatu::Acolyte::save(Svin::Json::Object& rootObject)
{
   rootObject.set("currentBank", bankIndex);

   for (uint8_t bankIndex = 0; bankIndex < 8; bankIndex++)
   {
      const Bank& currentBank = banks[bankIndex];

      Svin::Json::Object bankObject;
      bankObject.set("max", currentBank.maxActive);

      for (uint8_t index = 0; index < 16; index++)
      {
         Svin::Json::Array segmentArray;
         segmentArray.append(currentBank.segments[index].pitch);
         segmentArray.append(currentBank.segments[index].ticks);
         segmentArray.append(currentBank.segments[index].length);
         segmentArray.append(currentBank.segments[index].chance);

         const std::string segmentKey = "s" + Text::pad(std::to_string(index), 2);
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

// creete module
Model* modelNosferatuAcolyte = Svin::Origin::the()->addModule<Nosferatu::Acolyte, Nosferatu::AcolyteWidget>("NosferatuAcolyte");
