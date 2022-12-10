#include "GrooveMaestro.h"

#include <Tools/Text.h>
#include <Tools/Variable.h>

void GrooveMaestro::updateDisplayPassthrough()
{
   controller.setColor(Color::Predefined::Yellow);
   controller.drawRect(0, 0, 130, 10, true);

   controller.setColor(Color::Predefined::Black);
   controller.writeText(65, 0, "Passthrough", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   if (!displayGroove())
      return;

   displayContours();
   readLaunchpad();
   updateLaunchpadGrid();
}

void GrooveMaestro::updateDisplayRemote()
{
   controller.setColor(Color::Predefined::Cyan);
   controller.drawRect(0, 0, 130, 10, true);

   controller.setColor(Color::Predefined::Black);
   controller.writeText(65, 0, "Remote", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   if (!displayGroove())
      return;

   displayContours();
   readLaunchpad();
   updateLaunchpadGrid();
}

void GrooveMaestro::updateDisplayPlay()
{
   controller.setColor(Color::Predefined::Green);
   controller.drawRect(0, 0, 130, 10, true);

   controller.setColor(Color::Predefined::Black);
   controller.writeText(65, 0, "Play", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   if (!displayGroove())
      return;

   displayContours();
   readLaunchpad();
   updateLaunchpadGrid();
}

void GrooveMaestro::displayStoped()
{
   const uint32_t segmentCount = conductor.getSegmentCount();
   const uint16_t digitCount = Variable::compileDigitCount(segmentCount);

   controller.setColor(Color::Predefined::White);
   controller.writeText(5, 12, Text::pad(std::to_string(segmentCount), digitCount), Svin::DisplayOLED::Font::Large);
   controller.writeText(7 + 12 * digitCount, 17, "segmemnts", Svin::DisplayOLED::Font::Normal);

   const uint32_t segmentIndex = conductor.getCurrentSegmentIndex();
   controller.writeText(5, 32, Text::pad(std::to_string(segmentIndex), digitCount), Svin::DisplayOLED::Font::Large);
   controller.writeText(7 + 12 * digitCount, 37, "current", Svin::DisplayOLED::Font::Normal);

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

bool GrooveMaestro::displayGroove()
{
   const Grooves& grooves = (OperationMode::Play == operationMode) ? conductor : localGrooves;

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
      if (name.length() > 6)
         name = name.substr(0, 6);
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
