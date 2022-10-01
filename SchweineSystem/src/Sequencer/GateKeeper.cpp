#include "GateKeeper.h"

#include <Tools/File.h>
#include <Tools/Text.h>
#include <Tools/Variable.h>

GateKeeper::GateKeeper()
   : Svin::Module()
   , Svin::MasterClock::Client()
   , Svin::Midi::Output(Midi::Device::DrumTrigger)
   , fileName()
   , grooves()
   , spikes(0)
   , state(0)
   // bank
   , bankIndex(0)
   , bankUpButton(this, Panel::BankUp)
   , bankDownButton(this, Panel::BankDown)
   // input
   , passInput(this, Panel::Pass)
   , noOffsetSwitch(this, Panel::NoOffset)
   // output
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
   , gateOutputList(this)
   , triggerGenerator()
   , pulseActive(0)
   // mode
   , loopButton(this, Panel::Loop, Panel::RGB_Loop)
   , operationMode(OperationMode::Passthrough)
   , operationModeButton(this, Panel::Mode)
   // display
   , controller(this, Panel::Pixels_Display)
   , lastNamedSegement()

{
   setup();
   registerHubClient("GateKeeper");

   controller.onClickedOpenFileFunction(this, &GateKeeper::loadProject, "Projects:json");

   gateOutputList.append({Panel::One_Output,
                          Panel::Two_Output,
                          Panel::Three_Output,
                          Panel::Four_Output,
                          Panel::Five_Output,
                          Panel::Six_Output,
                          Panel::Seven_Output,
                          Panel::Eight_Output});

   loopButton.setDefaultColor(Color{0, 255, 0});

   connectionButton.setDefaultColor(Color{0, 255, 0});
   connectToMidiDevice();
}

void GateKeeper::process(const ProcessArgs& args)
{
   if (connectionButton.isTriggered())
      connectToMidiDevice();

   if (loopButton.isTriggered())
   {
      bool loop = grooves.isLooping();
      loop ^= true;
      grooves.setLooping(loop);
   }
   loopButton.setActive(grooves.isLooping());

   Variable::Integer<uint8_t> varBank(bankIndex, 0, 15, true);
   if (bankUpButton.isTriggered())
      varBank.increment();
   else if (bankDownButton.isTriggered())
      varBank.decrement();

   // operation mode
   if (operationModeButton.isTriggered())
   {
      static const std::vector<OperationMode> order = {OperationMode::Passthrough, OperationMode::Internal};
      Variable::Enum<OperationMode> variable(operationMode, order, true);
      variable.increment();
   }

   // do stuff
   const bool on = getTempo().isRunningOrFirstTick();

   if (OperationMode::Passthrough == operationMode)
   {
      for (uint8_t index = 0; index < 8; index++)
      {
         if (!passInput.isConnected() || !on)
         {
            gateOutputList[index]->setActive(0.0);
            continue;
         }

         const uint8_t inputIndex = noOffsetSwitch.isOn() ? index : index + 8;
         const float voltage = (inputIndex < passInput.getNumberOfChannels()) ? passInput.getVoltage(inputIndex) : 0.0;
         gateOutputList[index]->setActive(voltage > 3.0);
      }
      return;
   }

   if (hasReset())
   {
      grooves.clockReset();
      return;
   }

   while (hasTick())
   {
      grooves.clockTick();

      const uint32_t segmentIndex = grooves.getCurrentSegmentIndex();
      const uint32_t currentTick = grooves.getCurrentSegmentTick();
      spikes = grooves.getSpikes(segmentIndex, currentTick);
      state = grooves.getState(segmentIndex);

      triggerGenerator.trigger();
   }

   const bool pulse = triggerGenerator.process(args.sampleTime);
   static const uint8_t midiBaseNote = Note::availableNotes.at(1).midiValue + 12;

   for (uint8_t index = 0; index < 8; index++)
   {
      gateOutputList[index]->setActive(state.get(index));

      if (!spikes.get(index))
         continue;

      if (pulse == pulseActive.get(index))
         continue;

      if (pulse && !pulseActive.get(index)) // send note on messages
      {
         sendNoteOn(10, Note::fromMidi(midiBaseNote + index), 127);
      }
      else if (!pulse && pulseActive.get(index)) // send note off messsages
      {
         sendNoteOff(10, Note::fromMidi(midiBaseNote + index));
      }

      pulseActive.set(index, pulse);
   }
}

void GateKeeper::loadProject(const std::string& newFileName)
{
   fileName = newFileName;

   const Bytes data = File::load(fileName);
   if (data.empty())
      return;

   using namespace Svin::Json;

   const Object rootObject(data);

   // TODO
}

void GateKeeper::connectToMidiDevice()
{
   if (connected())
   {
      connectionButton.setOn();
      return;
   }

   connectionButton.setOff();
   if (!open())
      return;

   connectionButton.setOn();
}

void GateKeeper::updateDisplays()
{
   controller.fill();

   if (GateKeeper::OperationMode::Passthrough == operationMode)
      updatePassthrough();
   else if (GateKeeper::OperationMode::Internal == operationMode)
      updateInternal();

   const uint32_t index = grooves.getCurrentSegmentIndex();

   Svin::Json::Object object;
   object.set("_Application", "GateKeeper");
   object.set("_Type", "Index");
   object.set("index", index);
   object.set("bank", bankIndex);
   object.set("mode", static_cast<uint8_t>(operationMode));

   sendDocumentToHub(1, object);
}

void GateKeeper::updatePassthrough()
{
   controller.setColor(Color{0, 255, 0});
   controller.drawRect(0, 0, 130, 10, true);

   controller.writeText(10, 50, std::to_string(bankIndex), Svin::DisplayOLED::Font::Huge, Svin::DisplayOLED::Alignment::Left);

   controller.setColor(Color{0, 0, 0});
   controller.writeText(65, 0, "Passthrough", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   const Tempo tempo = getTempo();
   const bool on = tempo.isRunningOrFirstTick();

   for (uint8_t index = 0; index < 8; index++)
   {
      const uint8_t column = (index < 4) ? 0 : 1;
      const uint8_t row = (index < 4) ? index : index - 4;

      const uint8_t x = 50 + column * 50;
      const uint8_t y = 25 + row * 20;

      controller.setColor(Color{155, 155, 155});
      controller.writeText(x, y, std::to_string(index + 1), Svin::DisplayOLED::Font::Large, Svin::DisplayOLED::Alignment::Right);

      controller.setColor(Color{255, 255, 255});
      if (!on)
         controller.writeText(x + 10, y, ".", Svin::DisplayOLED::Font::Large);
      else if (gateOutputList[index]->getVoltage(index) > 3.0)
         controller.writeText(x + 10, y, "H", Svin::DisplayOLED::Font::Large);
      else
         controller.writeText(x + 10, y, "_", Svin::DisplayOLED::Font::Large);
   }
}

void GateKeeper::updateInternal()
{
   controller.setColor(Color{255, 0, 255});
   controller.drawRect(0, 0, 130, 10, true);

   controller.setColor(Color{0, 0, 0});
   controller.writeText(65, 0, "Current", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   const Tempo tempo = getTempo();
   const bool on = tempo.isRunningOrFirstTick();
}

void GateKeeper::receivedDocumentFromHub(const ::Midi::Channel& channel, const Svin::Json::Object& object, const uint8_t docIndex)
{
   if (1 != channel || 0 != docIndex)
      return;

   if ("Reload" == object.get("_Type").toString())
   {
      const uint8_t objectBankIndex = object.get("bank").toInt();
      if (objectBankIndex != bankIndex)
         return;

      const std::string fileName = object.get("fileName").toString();
      loadProject(fileName);
   }
}

void GateKeeper::load(const Svin::Json::Object& rootObject)
{
   bankIndex = rootObject.get("bank").toInt();
   operationMode = static_cast<OperationMode>(rootObject.get("operation").toInt());

   const bool loop = rootObject.get("loop").toBool();
   grooves.setLooping(loop);

   const bool no_offset = rootObject.get("no_offset").toBool();
   noOffsetSwitch.setState(no_offset);

   const std::string newFileName = rootObject.get("fileName").toString();
   loadProject(newFileName);
}

void GateKeeper::save(Svin::Json::Object& rootObject)
{
   rootObject.set("bank", bankIndex);
   rootObject.set("operation", static_cast<uint8_t>(operationMode));
   rootObject.set("loop", grooves.isLooping());
   rootObject.set("no_offset", noOffsetSwitch.isOn());

   rootObject.set("fileName", fileName);
}

// widget

GateKeeperWidget::GateKeeperWidget(GateKeeper* module)
: Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelGateKeeper = Svin::Origin::the()->addModule<GateKeeper, GateKeeperWidget>("GateKeeper");

