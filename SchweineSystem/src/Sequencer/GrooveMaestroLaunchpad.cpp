#include "GrooveMaestro.h"

GrooveMaestro::Launchpad::Launchpad(GrooveMaestro* gm)
   : client()
   , wantConnection(WantConnection::Maybe)
   , connectionPrompt()
   , gm(gm)
   , offset(0)
   , connectionButton(gm, Panel::Connect, Panel::RGB_Connect)
{
}

void GrooveMaestro::Launchpad::process()
{
   if (connectionButton.isTriggered())
      connectionPrompt.arm();

   if (connectionPrompt.reset())
      toggleConnection();
}

void GrooveMaestro::Launchpad::updateButton()
{
   if (WantConnection::No == wantConnection)
      connectionButton.setColor(Color::Predefined::Blue);
   else if (WantConnection::Yes == wantConnection)
      connectionButton.setColor(Color::Predefined::Green);
   else
      connectionButton.setColor(Color::Predefined::Black);
}

void GrooveMaestro::Launchpad::read()
{
   Grooves& localGrooves = gm->localGrooves;
   for (const Svin::LaunchpadClient::Pad& pad : client.triggeredPads())
   {
      const bool pressed = (Svin::LaunchpadClient::Button::Off != pad.button);
      if (!pressed)
         continue;

      if (8 == pad.column && OperationMode::Passthrough == gm->operationMode)
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
            offset += 4;
            client.setAll(0);
         }
         else if (0 == pad.column)
         {
            if (4 < offset)
               offset -= 4;
            else
               offset = 0;
            client.setAll(0);
         }
         else if (2 == pad.column && OperationMode::Passthrough == gm->operationMode)
         {
            uint8_t length = localGrooves.getSegmentLength(0);
            const uint8_t tick = localGrooves.getCurrentSegmentTick();
            if (1 < length && tick + 1 < length)
            {
               length--;
               localGrooves.setSegmentLength(0, length);
               client.setAll(0);
            }
         }
         else if (3 == pad.column && OperationMode::Passthrough == gm->operationMode)
         {
            uint8_t length = localGrooves.getSegmentLength(0);
            length++;
            localGrooves.setSegmentLength(0, length);
            client.setAll(0);
         }
         else if (4 == pad.column && OperationMode::Passthrough == gm->operationMode)
         {
            gm->uploadToHub();
         }
         else if (5 == pad.column)
         {
            gm->operationMode = OperationMode::Passthrough;
            updateHeader();
         }
         else if (6 == pad.column)
         {
            gm->operationMode = OperationMode::Remote;
            updateHeader();
         }
         else if (7 == pad.column)
         {
            gm->operationMode = OperationMode::Play;
            updateHeader();
         }
      }
      else if (OperationMode::Passthrough == gm->operationMode)
      {
         const uint8_t length = localGrooves.getSegmentLength(0);

         const uint8_t lastFullRow = length - (length % 8);
         const uint8_t fullRows = lastFullRow / 8;
         const uint8_t numberOfRows = (length == lastFullRow) ? fullRows : 1 + fullRows;

         const uint8_t index = offset + (7 - pad.row);
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

void GrooveMaestro::Launchpad::readStopped()
{
   for (const Svin::LaunchpadClient::Pad& pad : client.triggeredPads())
   {
      const bool pressed = (Svin::LaunchpadClient::Button::Off != pad.button);
      if (!pressed)
         continue;

      if (8 == pad.row)
      {
         if (5 == pad.column)
         {
            gm->operationMode = OperationMode::Passthrough;
            updateHeader();
         }
         else if (6 == pad.column)
         {
            gm->operationMode = OperationMode::Remote;
            updateHeader();
         }
         else if (7 == pad.column)
         {
            gm->operationMode = OperationMode::Play;
            updateHeader();
         }
      }
   }
}

void GrooveMaestro::Launchpad::updateGrid()
{
   const Grooves& grooves = (OperationMode::Play == gm->operationMode) ? gm->conductor : gm->localGrooves;

   const uint32_t segmentIndex = grooves.getCurrentSegmentIndex();
   const uint8_t currentTick = grooves.getCurrentSegmentTick();
   const uint8_t length = grooves.getSegmentLength(segmentIndex);

   static const std::vector<uint8_t> trackActiveColorList = {12, 20, 36, 44, 52, 4, 28, 73};
   static const std::vector<uint8_t> trackInactiveColorList = {15, 23, 39, 47, 55, 7, 31, 63};

   Grooves::Gates gates = grooves.getGates(segmentIndex);
   for (uint8_t row = 0; row < 8; row++)
   {
      const uint8_t index = 7 - row;
      if (gates.get(index))
         client.setPad(row, 8, Svin::LaunchpadClient::Mode::Flash, 3);
      else
         client.setPad(row, 8, Svin::LaunchpadClient::Mode::Steady, trackInactiveColorList[index]);
   }

   const uint8_t lastFullRow = length - (length % 8);
   const uint8_t fullRows = lastFullRow / 8;
   const uint8_t numberOfRows = (length == lastFullRow) ? fullRows : 1 + fullRows;

   const uint8_t maxOffset = 8 * (numberOfRows - 1);
   if (maxOffset < offset)
      offset = maxOffset;

   for (uint8_t row = 0; row < 8; row++)
   {
      const uint8_t index = offset + (7 - row);
      const uint8_t trackOffset = index % numberOfRows;
      const uint8_t trackIndex = (index - trackOffset) / numberOfRows;

      for (uint8_t column = 0; column < 8; column++)
      {
         const uint8_t tick = column + (trackOffset * 8);

         if (tick >= length)
            client.setPad(row, column, Svin::LaunchpadClient::Mode::Off);
         else if (tick == currentTick)
            client.setPad(row, column, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::White);
         else if (grooves.getTriggers(segmentIndex, tick).get(trackIndex))
            client.setPad(row, column, Svin::LaunchpadClient::Mode::Pulse, trackActiveColorList[trackIndex]);
         else
            client.setPad(row, column, Svin::LaunchpadClient::Mode::Steady, trackInactiveColorList[trackIndex]);
      }
   }
}

void GrooveMaestro::Launchpad::updateHeader()
{
   client.setAll(0, true);

   if (OperationMode::Passthrough == gm->operationMode)
   {
      client.setPad(8, 0, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::White);
      client.setPad(8, 1, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::White);
      client.setPad(8, 2, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::White);
      client.setPad(8, 3, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::White);
      client.setPad(8, 4, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Red);
      client.setPad(8, 5, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Yellow);
      client.setPad(8, 6, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Cyan.dim(0.1));
      client.setPad(8, 7, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Green.dim(0.1));
      client.setPad(8, 8, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Yellow);
   }
   else if (OperationMode::Remote == gm->operationMode)
   {
      client.setPad(8, 0, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::White);
      client.setPad(8, 1, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::White);
      client.setPad(8, 2, Svin::LaunchpadClient::Mode::Off, Color::Predefined::White);
      client.setPad(8, 3, Svin::LaunchpadClient::Mode::Off, Color::Predefined::White);
      client.setPad(8, 4, Svin::LaunchpadClient::Mode::Off, Color::Predefined::Red);
      client.setPad(8, 5, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Yellow.dim(0.1));
      client.setPad(8, 6, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Cyan);
      client.setPad(8, 7, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Green.dim(0.1));
      client.setPad(8, 8, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Cyan);
   }
   else if (OperationMode::Play == gm->operationMode)
   {
      client.setPad(8, 0, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::White);
      client.setPad(8, 1, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::White);
      client.setPad(8, 2, Svin::LaunchpadClient::Mode::Off, Color::Predefined::White);
      client.setPad(8, 3, Svin::LaunchpadClient::Mode::Off, Color::Predefined::White);
      client.setPad(8, 4, Svin::LaunchpadClient::Mode::Off, Color::Predefined::Red);
      client.setPad(8, 5, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Yellow.dim(0.1));
      client.setPad(8, 6, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Cyan.dim(0.1));
      client.setPad(8, 7, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Green);
      client.setPad(8, 8, Svin::LaunchpadClient::Mode::Steady, Color::Predefined::Green);
   }
}

void GrooveMaestro::Launchpad::toggleConnection()
{
   if (client.isConnected())
   {
      client.setAll(0, false);

      client.disconnect();
      wantConnection = WantConnection::No;
   }
   else
   {
      client.connect(gm->deviceId);
      if (!client.isConnected())
         return;

      client.setAll(0, false);

      updateHeader();
      wantConnection = WantConnection::Yes;
   }
}
