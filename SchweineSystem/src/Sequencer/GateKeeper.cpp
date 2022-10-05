#include "GateKeeper.h"

#include <Tools/File.h>
#include <Tools/Text.h>
#include <Tools/Variable.h>

GateKeeper::GateKeeper()
   : Svin::Module()
   , Svin::MasterClock::Client()
   , fileName()
   , grooves()
   , tickTriggers(0)
   , segmentGates(0)
   // bank
   , bankIndex(0)
   , bankUpButton(this, Panel::BankUp)
   , bankDownButton(this, Panel::BankDown)
   // input
   , passInput(this, Panel::Pass)
   , noOffsetSwitch(this, Panel::NoOffset)
   // output
   , output(this, Panel::One_Output)
   , triggerGenerator()
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

   controller.onClickedOpenFileFunction(this, &GateKeeper::loadProject, "Projects:gatekeeper");

   loopButton.setDefaultColor(Color{0, 255, 0});
}

void GateKeeper::process(const ProcessArgs& args)
{
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

   output.setNumberOfChannels(16);

   // do stuff
   const bool on = getTempo().isRunningOrFirstTick();

   BoolField16 values(0);

   if (OperationMode::Passthrough == operationMode)
   {
      for (uint8_t index = 0; index < 8; index++)
      {
         if (!passInput.isConnected() || !on)
            continue;

         const uint8_t inputIndex = noOffsetSwitch.isOn() ? index : index + 8;
         const float voltage = (inputIndex < passInput.getNumberOfChannels()) ? passInput.getVoltage(inputIndex) : 0.0;

         values.set(index + 8, (voltage > 3.0));
      }
      return;
   }
   else
   {
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
         tickTriggers = grooves.getTriggers(segmentIndex, currentTick);
         segmentGates = grooves.getGates(segmentIndex);

         triggerGenerator.trigger();
      }

      const bool pulse = triggerGenerator.process(args.sampleTime);

      for (uint8_t index = 0; index < 8; index++)
      {
         if (tickTriggers.get(index))
            values.set(index + 0, pulse);

         values.set(index + 8, segmentGates.get(index));
      }
   }

   for (uint8_t index = 0; index < 16; index++)
      output.setActive(values.get(index), index);
}

void GateKeeper::loadProject(const std::string& newFileName)
{
   fileName = newFileName;

   const Bytes data = File::load(fileName);
   if (data.empty())
      return;

   const Svin::Json::Object rootObject(data);

   Svin::Json::Object projectObject = rootObject.get("project").toObject();

   const uint32_t segmentCount = projectObject.get("segments").toInt();
   const uint16_t digitCount = Variable::compileDigitCount(segmentCount);
   const uint8_t division = projectObject.get("division").toInt();

   auto compileSegmentKey = [&](const uint32_t segmentIndex)
   {
      return Text::pad(std::to_string(segmentIndex), digitCount);
   };

   auto compileColor = [](const Svin::Json::Array& array)
   {
      uint8_t red = array.at(0).toInt();
      uint8_t green = array.at(1).toInt();
      uint8_t blue = array.at(2).toInt();

      return Color{red, green, blue};
   };

   grooves.update(division, segmentCount);

   // header
   {
      Svin::Json::Object headerObject = projectObject.get("header").toObject();
      for (uint32_t segmentIndex = 0; segmentIndex < segmentCount; segmentIndex++)
      {
         const std::string segmentKey = compileSegmentKey(segmentIndex);
         if (!headerObject.hasKey(segmentKey))
            continue;

         Svin::Json::Object segmentObject = headerObject.get(segmentKey).toObject();
         grooves.setSegmentName(segmentIndex, segmentObject.get("name").toString());

         if (segmentObject.hasKey("length"))
         {
            grooves.setSegmentLength(segmentIndex, segmentObject.get("length").toInt());
         }
         if (segmentObject.hasKey("fgColor"))
         {
            const Svin::Json::Array colorArray = segmentObject.get("fgColor").toArray();
            grooves.setSegmentForegroundColor(segmentIndex, compileColor(colorArray));
         }

         if (segmentObject.hasKey("bgColor"))
         {
            const Svin::Json::Array colorArray = segmentObject.get("bgColor").toArray();
            grooves.setSegmentBackgroundColor(segmentIndex, compileColor(colorArray));
         }
      }
   }

   // gates
   {
      Svin::Json::Object gatesObject = projectObject.get("gates").toObject();
      for (uint32_t segmentIndex = 0; segmentIndex < segmentCount; segmentIndex++)
      {
         const std::string segmentKey = compileSegmentKey(segmentIndex);
         if (!gatesObject.hasKey(segmentKey))
            continue;

         const BoolField8 gates = gatesObject.get(segmentKey).toInt();
         grooves.setGates(segmentIndex, gates);
      }
   }

   // beats
   {
      Svin::Json::Object beatsObject = projectObject.get("beats").toObject();
      for (uint32_t segmentIndex = 0; segmentIndex < segmentCount; segmentIndex++)
      {
         const std::string segmentKey = compileSegmentKey(segmentIndex);
         if (!beatsObject.hasKey(segmentKey))
            continue;

         Svin::Json::Array beatArray = beatsObject.get(segmentKey).toArray();

         const uint8_t beatLength = beatArray.size();
         if (beatLength != grooves.getSegmentLength(segmentIndex))
            continue;

         Grooves::Beat beat(beatLength, BoolField8(0));
         for (uint8_t tick = 0; tick < beatLength; tick++)
         {
            const BoolField8 triggers = beatArray.at(tick).toInt();
            beat[tick] = triggers;
         }
         grooves.setBeat(segmentIndex, beat);
      }
   }

   bankIndex = rootObject.get("bank").toInt();
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
   controller.setColor(Color{255, 255, 0});
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
      else if (output.getVoltage(index + 8) > 3.0)
         controller.writeText(x + 10, y, "H", Svin::DisplayOLED::Font::Large);
      else
         controller.writeText(x + 10, y, "_", Svin::DisplayOLED::Font::Large);
   }
}

void GateKeeper::updateInternal()
{
   controller.setColor(Color{0, 255, 0});
   controller.drawRect(0, 0, 130, 10, true);

   controller.setColor(Color{0, 0, 0});
   controller.writeText(65, 0, "Current", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   const Tempo tempo = getTempo();
   const bool on = tempo.isRunningOrFirstTick();
   const uint32_t segmentCount = grooves.getSegmentCount();
   const uint16_t digitCount = Variable::compileDigitCount(segmentCount);

   // top row
   const uint32_t segmentIndex = grooves.getCurrentSegmentIndex();

   controller.setColor(Color{255, 255, 255});
   controller.writeText(5, 12, Text::pad(std::to_string(segmentIndex), digitCount), Svin::DisplayOLED::Font::Large);

   const std::string eventName = grooves.getSegmentName(segmentIndex);
   const std::string eventText = eventName.empty() ? "--" : eventName;
   controller.writeText(50, 12, eventText, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   if (eventName.empty())
      controller.writeText(100, 12, lastNamedSegement, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);
   else
      lastNamedSegement = eventName;

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

      controller.setColor(Color{0, 255, 0});

      const uint8_t x = 35 + col * 12;
      const uint8_t y = 30;
      controller.drawRect(x, y, x + 8, y + 4, true);

      break;
   }

   for (uint8_t row = 0; row < 8; row++)
   {
      const uint8_t y = 37 + row * 12;

      if (hasGates)
         controller.setColor(Color{255, 255, 255});
      else
         controller.setColor(Color{155, 155, 200});

      if (gates.get(row))
         controller.drawRect(5, y, 20, y + 8, true);
      else
         controller.drawRect(5, y, 20, y + 8, false);

      if (hasBeat)
         controller.setColor(Color{255, 255, 255});
      else
         controller.setColor(Color{155, 155, 200});

      for (uint8_t col = 0; col < 8; col++)
      {
         const uint tick = offset + col;
         const uint8_t x = 35 + col * 12;

         if (tick >= length)
            break;

         if (beat[tick].get(row))
            controller.drawRect(x, y, x + 8, y + 8, true);
      }
   }
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
