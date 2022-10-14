#include "GrooveMaestro.h"

void GrooveMaestro::connectToLaunchpad()
{
   launchpad.connect(deviceId);
   if (!launchpad.isConnected())
      return;

   launchpad.setAll(0, false);

   updateLaunchpadHeader();
}

void GrooveMaestro::readLaunchpad()
{
   for (const Svin::LaunchpadClient::Pad& pad : launchpad.triggeredPads())
   {
      const bool pressed = (Svin::LaunchpadClient::Button::Off != pad.button);
      if (!pressed)
         continue;

      if (8 == pad.column && OperationMode::Passthrough == operationMode)
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
            launchpadOffset += 4;
            launchpad.setAll(0);
         }
         else if (0 == pad.column)
         {
            if (4 < launchpadOffset)
               launchpadOffset -= 4;
            else
               launchpadOffset = 0;
            launchpad.setAll(0);
         }
         else if (2 == pad.column && OperationMode::Passthrough == operationMode)
         {
            uint8_t length = localGrooves.getSegmentLength(0);
            const uint8_t tick = localGrooves.getCurrentSegmentTick();
            if (1 < length && tick + 1 < length)
            {
               length--;
               localGrooves.setSegmentLength(0, length);
               launchpad.setAll(0);
            }
         }
         else if (3 == pad.column && OperationMode::Passthrough == operationMode)
         {
            uint8_t length = localGrooves.getSegmentLength(0);
            length++;
            localGrooves.setSegmentLength(0, length);
            launchpad.setAll(0);
         }
         else if (4 == pad.column && OperationMode::Passthrough == operationMode)
         {
            uploadToHub();
         }
         else if (5 == pad.column)
         {
            operationMode = OperationMode::Passthrough;
            updateLaunchpadHeader();
         }
         else if (6 == pad.column)
         {
            operationMode = OperationMode::Remote;
            updateLaunchpadHeader();
         }
         else if (7 == pad.column)
         {
            operationMode = OperationMode::Play;
            updateLaunchpadHeader();
         }
      }
      else if (OperationMode::Passthrough == operationMode)
      {
         const uint8_t length = localGrooves.getSegmentLength(0);

         const uint8_t lastFullRow = length - (length % 8);
         const uint8_t fullRows = lastFullRow / 8;
         const uint8_t numberOfRows = (length == lastFullRow) ? fullRows : 1 + fullRows;

         const uint8_t index = launchpadOffset + (7 - pad.row);
         const uint8_t trackOffset = index % numberOfRows;
         const uint8_t trackIndex = (index - trackOffset) / numberOfRows;

         const uint8_t tick = pad.column + (trackOffset * 8);
         if (tick >= length)
            continue;

         Grooves::Beat beat = localGrooves.getBeat(0);
         beat.at(tick).flip(trackIndex);
         localGrooves.setBeat(0, beat);
      }
   }
}

void GrooveMaestro::updateLaunchpadGrid()
{
   const Grooves& grooves = (OperationMode::Play == operationMode) ? conductor : localGrooves;

   const uint32_t segmentIndex = grooves.getCurrentSegmentIndex();
   const uint8_t currentTick = grooves.getCurrentSegmentTick();
   const uint8_t length = grooves.getSegmentLength(segmentIndex);

   static const std::vector<uint8_t> trackActiveColorList = {12, 20, 36, 44, 52, 4, 28, 73};
   static const std::vector<uint8_t> trackInactiveColorList = {15, 23, 39, 47, 55, 7, 31, 63};

   Grooves::Gates gates = grooves.getGates(segmentIndex);
   for (uint8_t row = 0; row < 8; row++)
   {
      const uint8_t index = 7 - row;
      const Color color = gates.get(index) ? Color::Predefined::Yellow : Color::Predefined::Blue;
      launchpad.setPad(row, 8, Svin::LaunchpadClient::Mode::Steady, color);
   }

   Grooves::Beat beat = grooves.getBeat(segmentIndex);

   const uint8_t lastFullRow = length - (length % 8);
   const uint8_t fullRows = lastFullRow / 8;
   const uint8_t numberOfRows = (length == lastFullRow) ? fullRows : 1 + fullRows;

   const uint8_t maxOffset = 8 * (numberOfRows - 1);
   if (maxOffset < launchpadOffset)
      launchpadOffset = maxOffset;

   for (uint8_t row = 0; row < 8; row++)
   {
      const uint8_t index = launchpadOffset + (7 - row);
      const uint8_t trackOffset = index % numberOfRows;
      const uint8_t trackIndex = (index - trackOffset) / numberOfRows;

      for (uint8_t column = 0; column < 8; column++)
      {
         const uint8_t tick = column + (trackOffset * 8);

         if (tick >= length)
            launchpad.setPad(row, column, Svin::LaunchpadClient::Mode::Off);
         else if (index == currentTick)
            launchpad.setPad(row, column, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::White);
         else if (beat.at(index).get(trackIndex))
            launchpad.setPad(row, column, Svin::LaunchpadClient::Mode::Pulse, trackActiveColorList[trackIndex]);
         else
            launchpad.setPad(row, column, Svin::LaunchpadClient::Mode::Steady, trackInactiveColorList[trackIndex]);
      }
   }
   /*
   for (uint8_t trackIndex = 0; trackIndex < 8; trackIndex++)
   {
      const uint8_t rowOffset = trackIndex * numberOfRows;

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
         else if (beat.at(index).get(trackIndex))
            launchpad.setPad(launchpadOffset + 7 - row, col, Svin::LaunchpadClient::Mode::Pulse, trackActiveColorList[trackIndex]);
         else
            launchpad.setPad(launchpadOffset + 7 - row, col, Svin::LaunchpadClient::Mode::Steady, trackInactiveColorList[trackIndex]);
      }
   }
   */
}

void GrooveMaestro::updateLaunchpadHeader()
{
   launchpad.setAll(0, true);

   if (OperationMode::Passthrough == operationMode)
   {
      launchpad.setPad(8, 0, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::White);
      launchpad.setPad(8, 1, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::White);
      launchpad.setPad(8, 2, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::White);
      launchpad.setPad(8, 3, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::White);
      launchpad.setPad(8, 4, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Red);
      launchpad.setPad(8, 5, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Yellow);
      launchpad.setPad(8, 6, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Cyan.dim(0.1));
      launchpad.setPad(8, 7, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Green.dim(0.1));
      launchpad.setPad(8, 8, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Yellow);
   }
   else if (OperationMode::Remote == operationMode)
   {
      launchpad.setPad(8, 0, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::White);
      launchpad.setPad(8, 1, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::White);
      launchpad.setPad(8, 2, Svin::LaunchpadClient::Mode::Off, Color::Predefined::White);
      launchpad.setPad(8, 3, Svin::LaunchpadClient::Mode::Off, Color::Predefined::White);
      launchpad.setPad(8, 4, Svin::LaunchpadClient::Mode::Off, Color::Predefined::Red);
      launchpad.setPad(8, 5, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Yellow.dim(0.1));
      launchpad.setPad(8, 6, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Cyan);
      launchpad.setPad(8, 7, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Green.dim(0.1));
      launchpad.setPad(8, 8, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Cyan);
   }
   else if (OperationMode::Play == operationMode)
   {
      launchpad.setPad(8, 0, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::White);
      launchpad.setPad(8, 1, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::White);
      launchpad.setPad(8, 2, Svin::LaunchpadClient::Mode::Off, Color::Predefined::White);
      launchpad.setPad(8, 3, Svin::LaunchpadClient::Mode::Off, Color::Predefined::White);
      launchpad.setPad(8, 4, Svin::LaunchpadClient::Mode::Off, Color::Predefined::Red);
      launchpad.setPad(8, 5, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Yellow.dim(0.1));
      launchpad.setPad(8, 6, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Cyan.dim(0.1));
      launchpad.setPad(8, 7, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Green);
      launchpad.setPad(8, 8, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Green);
   }
}

GrooveMaestro::PadFunction GrooveMaestro::getPadFunction(const uint8_t row, const uint8_t column) const
{
   PadFunction padFunction;

   const Grooves& grooves = (OperationMode::Play == operationMode) ? conductor : localGrooves;
   const uint32_t segmentIndex = grooves.getCurrentSegmentIndex();
   const uint8_t length = grooves.getSegmentLength(segmentIndex);

   const uint8_t lastFullRow = length - (length % 8);
   const uint8_t fullRows = lastFullRow / 8;
   const uint8_t numberOfRows = (length == lastFullRow) ? fullRows : 1 + fullRows;

   const uint8_t index = launchpadOffset + (7 - row);
   const uint8_t trackOffset = index % numberOfRows;
   padFunction.trackIndex = (index - trackOffset) / numberOfRows;

   padFunction.tick = column + (trackOffset * 8);
   padFunction.blank = (padFunction.tick >= length);

   return padFunction;
}
