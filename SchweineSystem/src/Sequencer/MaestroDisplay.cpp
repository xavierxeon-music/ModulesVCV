#include "Maestro.h"

#include <Tools/Text.h>
#include <Tools/Variable.h>

Maestro::Display::Display(Maestro* gm)
   : mode(Mode::Overview)
   , gm(gm)
   , controller(gm, Panel::Pixels_Display)
   , modeButtonOverivew(gm, Panel::DisplayOverview, Panel::RGB_DisplayOverview)
   , modeButtonGroove(gm, Panel::DisplayGroove, Panel::RGB_DisplayGroove)
   , modeButtonMelody(gm, Panel::DisplayMelody, Panel::RGB_DisplayMelody)
   , modeButtonContour(gm, Panel::DisplayContour, Panel::RGB_DisplayContour)
   , modeMap()
{
   controller.onPressedOpenFileFunction(gm, &Maestro::loadProject, "Projects:grm");

   modeButtonOverivew.setDefaultColor(Color::Predefined::White);
   modeMap[Mode::Overview] = &modeButtonOverivew;

   modeButtonGroove.setDefaultColor(Color::Predefined::White);
   modeMap[Mode::Groove] = &modeButtonGroove;

   modeButtonMelody.setDefaultColor(Color::Predefined::White);
   modeMap[Mode::Melody] = &modeButtonMelody;

   modeButtonContour.setDefaultColor(Color::Predefined::White);
   modeMap[Mode::Contour] = &modeButtonContour;
}

void Maestro::Display::process()
{
   if (modeButtonOverivew.isTriggered())
   {
      mode = Mode::Overview;
   }
   if (modeButtonGroove.isTriggered())
   {
      mode = Mode::Groove;
   }
   if (modeButtonMelody.isTriggered())
   {
      mode = Mode::Melody;
   }
   if (modeButtonContour.isTriggered())
   {
      mode = Mode::Contour;
   }
}

void Maestro::Display::update()
{
   for (ModeMap::const_iterator it = modeMap.cbegin(); it != modeMap.cend(); it++)
   {
      const bool on = (it->first == mode);
      it->second->setActive(on);
   }

   controller.fill();

   if (OperationMode::Passthrough == gm->operationMode)
      headerPassthrough();
   else if (OperationMode::Remote == gm->operationMode)
      headerRemote();
   else if (OperationMode::Play == gm->operationMode)
      headerPlay();

   // top row
   {
      const Grooves& grooves = (OperationMode::Play == gm->operationMode) ? gm->conductor : gm->localGrooves;

      const uint32_t segmentCount = gm->conductor.getSegmentCount();
      const uint16_t digitCount = Variable::compileDigitCount(segmentCount);
      const uint32_t segmentIndex = grooves.getCurrentSegmentIndex();

      controller.setColor(Color::Predefined::White);
      controller.writeText(5, 12, Text::pad(std::to_string(segmentIndex), digitCount), Svin::DisplayOLED::Font::Large);

      const std::string eventName = grooves.getSegmentName(segmentIndex);
      const std::string eventText = eventName.empty() ? "--" : eventName;
      controller.writeText(7 + 12 * digitCount, 17, eventText, Svin::DisplayOLED::Font::Normal);
   }

   if (Mode::Overview == mode)
      displayOverview();
   else if (Mode::Groove == mode)
      displayGroove();
   else if (Mode::Melody == mode)
      displayMelody();
   else if (Mode::Contour == mode)
      displayContours();

   gm->launchpad.read();
   gm->launchpad.updateGrid();
}

void Maestro::Display::headerPassthrough()
{
   controller.setColor(Color::Predefined::Yellow);
   controller.drawRect(0, 0, 130, 10, true);

   controller.setColor(Color::Predefined::Black);
   controller.writeText(65, 0, "Passthrough", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

}

void Maestro::Display::headerRemote()
{
   controller.setColor(Color::Predefined::Cyan);
   controller.drawRect(0, 0, 130, 10, true);

   controller.setColor(Color::Predefined::Black);
   controller.writeText(65, 0, "Remote", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

}

void Maestro::Display::headerPlay()
{
   controller.setColor(Color::Predefined::Green);
   controller.drawRect(0, 0, 130, 10, true);

   controller.setColor(Color::Predefined::Black);
   controller.writeText(65, 0, "Play", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);
}

void Maestro::Display::displayOverview()
{
   const uint32_t segmentCount = gm->conductor.getSegmentCount();
   const uint16_t digitCount = Variable::compileDigitCount(segmentCount);

   const uint8_t noOfLines = 10;
   const uint8_t noOfLetters = 15;

   const uint8_t x = 20;
   for (uint8_t counter = 0; counter < noOfLines; counter++)
   {
      const uint8_t row = noOfLines - (counter + 1);
      const uint8_t y = 10 * row;
      const int8_t index = gm->fileName.length() - ((noOfLines - row) * noOfLetters);
      if (index >= 0)
      {
         const std::string text = gm->fileName.substr(index, noOfLetters);
         controller.writeText(x, y, text, 10);
      }
      else
      {
         const std::string text = gm->fileName.substr(0, noOfLetters + index);
         controller.writeText(x, y, Text::pad(text, noOfLetters, " "), 10);
         break;
      }
   }

   controller.setColor(Color::Predefined::White);
   controller.writeText(5, 132, Text::pad(std::to_string(segmentCount), digitCount), Svin::DisplayOLED::Font::Large);
   controller.writeText(15 + 18 * digitCount, 137, "segmemnts", Svin::DisplayOLED::Font::Normal);
}

void Maestro::Display::displayGroove()
{
   const Grooves& grooves = (OperationMode::Play == gm->operationMode) ? gm->conductor : gm->localGrooves;

   const uint32_t segmentCount = grooves.getSegmentCount();

   if (0 == segmentCount)
      return;

   // the grid
   const uint32_t segmentIndex = gm->conductor.getCurrentSegmentIndex();

   const Grooves::Gates& gates = grooves.getGates(segmentIndex);
   const bool hasGates = grooves.hasGates(segmentIndex);

   const Grooves::Beat& beat = grooves.getBeat(segmentIndex);
   const bool hasBeat = grooves.hasBeat(segmentIndex);
   const uint8_t currentTick = grooves.getCurrentSegmentTick();
   const uint8_t length = grooves.getSegmentLength(segmentIndex);

   const uint8_t offset = (currentTick - (currentTick % 8));

   const uint8_t yMarkerA = 35;
   const uint8_t yMarkerB = 137;
   for (uint8_t row = 0; row < 8; row++)
   {
      const uint8_t y = 42 + row * 12;

      if (hasGates)
         controller.setColor(Color::Predefined::White);
      else
         controller.setColor(Color(155, 155, 200));

      if (gates.get(row))
         controller.drawRect(115, y, 125, y + 8, true);
      else
         controller.drawRect(115, y, 125, y + 8, false);

      for (uint8_t col = 0; col < 8; col++)
      {
         const uint tick = offset + col;
         const uint8_t x = 5 + col * 12;

         if (tick >= length)
            break;

         if (tick == currentTick)
         {
            controller.setColor(Color::Predefined::Green);
            controller.drawRect(x, yMarkerA, x + 8, yMarkerA + 4, true);
            controller.drawRect(x, yMarkerB, x + 8, yMarkerB + 4, true);
         }

         if (hasBeat)
            controller.setColor(Color::Predefined::White);
         else
            controller.setColor(Color(155, 155, 200));

         if (beat[tick].get(row))
            controller.drawRect(x, y, x + 8, y + 8, true);
      }
   }
}

void Maestro::Display::displayMelody()
{
   const Stages& stage = (OperationMode::Play == gm->operationMode) ? gm->conductor : gm->localStages;

   const uint8_t currentTick = stage.getCurrentSegmentTick();
   const uint8_t offset = (currentTick - (currentTick % 16));

   const uint32_t segmentIndex = gm->conductor.getCurrentSegmentIndex();
   const uint8_t length = stage.getSegmentLength(segmentIndex);

   const uint8_t yMarkerA = 35;
   const uint8_t yMarkerB = 144;
   for (uint8_t laneIndex = 0; laneIndex < Stages::laneCount; laneIndex++)
   {
      const Stages::Segment& segment = stage.getSegment(laneIndex, segmentIndex);
      const bool hasSegment = stage.hasSegment(laneIndex, segmentIndex);

      const uint8_t y = 40 + laneIndex * 13;

      controller.setColor(Color(155, 155, 155));
      std::string name = gm->conductor.Stages::getName(laneIndex);
      if (name.length() > 5)
         name = name.substr(0, 5);
      controller.writeText(2, y + 3, name, Svin::DisplayOLED::Font::Small, Svin::DisplayOLED::Alignment::Left);

      for (uint8_t col = 0; col < 16; col++)
      {
         const uint8_t x = 30 + col * 6;

         const uint tick = offset + col;
         if (tick >= length)
            break;

         if (tick == currentTick)
         {
            controller.setColor(Color::Predefined::Green);
            controller.drawRect(x, yMarkerA, x + 4, yMarkerA + 2, true);
            controller.drawRect(x, yMarkerB, x + 4, yMarkerB + 2, true);
         }

         if (hasSegment)
            controller.setColor(Color::Predefined::White);
         else
            controller.setColor(Color(155, 155, 200));

         const Stages::Unit& unit = segment.at(tick);
         uint8_t height = static_cast<uint8_t>(10.0 * unit.value1 / 255.0);
         if (0 == height)
            height = 1;

         const uint8_t width = static_cast<uint8_t>(4.0 * unit.length / 255.0);

         if (0 != width)
            controller.drawRect(x, y + (10 - height), x + width, y + 10, true);
      }
   }
}

void Maestro::Display::displayContours()
{
   for (uint8_t laneIndex = 0; laneIndex < Contours::laneCount; laneIndex++)
   {
      controller.setColor(Color(155, 155, 155));

      const uint8_t column = (laneIndex < 8) ? 0 : 1;
      const uint8_t row = (laneIndex < 8) ? laneIndex : laneIndex - 8;

      const uint8_t y = 30 + 14 * row;

      std::string name = gm->conductor.Contours::getName(laneIndex);
      if (name.length() > 5)
         name = name.substr(0, 5);
      const uint8_t xName = 5 + (column * 64);
      controller.writeText(xName, y + 5, name, Svin::DisplayOLED::Font::Small, Svin::DisplayOLED::Alignment::Left);

      controller.setColor(Color::Predefined::White);

      const float voltage = gm->contourOutput.getVoltage(laneIndex);
      const uint8_t value = gm->voltageToValue(voltage);
      const std::string valueText = Text::convert(value);
      const uint8_t xVoltage = 55 + (column * 64);

      controller.writeText(xVoltage, y, valueText, 14, Svin::DisplayOLED::Alignment::Right);
   }
}
