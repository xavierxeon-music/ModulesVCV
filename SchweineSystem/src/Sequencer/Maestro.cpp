#include "Maestro.h"

#include <Midi/MidiCommon.h>
#include <Tools/File.h>
#include <Tools/SevenBit.h>
#include <Tools/Text.h>
#include <Tools/Variable.h>

#include <SvinOrigin.h>

Maestro::Maestro()
   : Svin::Module()
   , Svin::MasterClock::Client()
   , fileName()
   , project()
   , eventNameList()
   // bank
   , bankIndex(0)
   , bankUpButton(this, Panel::BankUp)
   , bankDownButton(this, Panel::BankDown)
   // midi
   , buffer()
   // input
   , input(this, Panel::Pass)
   , voltageToValue(0.0, 10.0, 0, 255)
   // upload
   , uploadInput(this, Panel::Upload)
   // outout
   , valueToVoltage(0.0, 255.0, 0.0, 10.0)
   , output(this, Panel::Output)
   // mode
   , loopButton(this, Panel::Loop, Panel::RGB_Loop)
   , operationMode(OperationMode::Passthrough)
   , operationModeButton(this, Panel::Mode)
   , remoteValues{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
   , controller(this, Maestro::Panel::Pixels_Display)
   , lastNamedSegement()
{
   setup();
   registerHubClient("Maestro");

   controller.onClickedOpenFileFunction(this, &Maestro::loadProject, "Projects:json");

   loopButton.setDefaultColor(Svin::Color{0, 255, 0});
}

void Maestro::process(const ProcessArgs& args)
{
   if (loopButton.isTriggered())
   {
      bool loop = project.isLooping();
      loop ^= true;
      project.setLooping(loop);
   }
   loopButton.setActive(project.isLooping());

   Variable::Integer<uint8_t> varBank(bankIndex, 0, 15, true);
   if (bankUpButton.isTriggered())
      varBank.increment();
   else if (bankDownButton.isTriggered())
      varBank.decrement();

   // operation mode
   if (operationModeButton.isTriggered())
   {
      static const std::vector<OperationMode> order = {OperationMode::Passthrough, OperationMode::Remote, OperationMode::InternalOverview, OperationMode::InternalCurrent};
      Variable::Enum<OperationMode> variable(operationMode, order, true);
      variable.increment();

      Svin::Json::Object object;
      object.set("_Application", "Maestro");
      object.set("_Type", "Mode");
      object.set("bank", bankIndex);
      object.set("mode", static_cast<uint8_t>(operationMode));

      sendDocumentToHub(1, object);
   }

   output.setNumberOfChannels(16);

   // do stuff
   if (OperationMode::Passthrough == operationMode)
   {
      return processPassthrough();
   }
   else if (OperationMode::Remote == operationMode)
   {
      return proccessRemote();
   }

   if (hasReset())
   {
      project.clockReset();
      return;
   }

   bool doProcess = true;
   while (hasTick())
   {
      project.clockTick();
      doProcess = false;
   }
   if (doProcess)
      processInternal();
}

void Maestro::loadProject(const std::string& newFileName)
{
   fileName = newFileName;

   const Bytes data = File::load(fileName);
   if (data.empty())
      return;

   using namespace Svin::Json;

   const Object rootObject(data);
   {
      const Array eventArray = rootObject.get("events").toArray();
      eventNameList.resize(eventArray.size());
      for (size_t index = 0; index < eventArray.size(); index++)
         eventNameList[index] = eventArray.at(index).toString();
   }
   {
      const Object projectObject = rootObject.get("project").toObject();

      const Tempo::Division division = static_cast<Tempo::Division>(projectObject.get("division").toInt());
      const uint32_t segmentCount = projectObject.get("segments").toInt();
      const uint16_t digitCount = Variable::compileDigitCount(segmentCount);

      project.clear();
      project.update(division, segmentCount);

      Array laneArray = projectObject.get("lanes").toArray();
      if (project.getLaneCount() != laneArray.size())
      {
         std::cout << newFileName << " " << (uint16_t)project.getLaneCount() << " " << laneArray.size() << std::endl;
         return;
      }

      for (uint8_t laneIndex = 0; laneIndex < project.getLaneCount(); laneIndex++)
      {
         Tracker::Lane& lane = project.getLane(laneIndex);
         Object laneObject = laneArray.at(laneIndex).toObject();
         lane.setName(laneObject.get("name").toString());

         for (uint32_t segmentIndex = 0; segmentIndex < segmentCount; segmentIndex++)
         {
            std::string segmentKey = std::to_string(segmentIndex);
            while (segmentKey.length() < digitCount)
               segmentKey = "0" + segmentKey;

            if (!laneObject.hasKey(segmentKey))
               continue;

            Object segmentObject = laneObject.get(segmentKey).toObject();
            lane.setSegmentSteady(segmentIndex, segmentObject.get("steady").toBool());

            if (segmentObject.hasKey("start"))
               lane.setSegmentStartValue(segmentIndex, segmentObject.get("start").toInt());
            if (segmentObject.hasKey("end"))
               lane.setSegmentEndValue(segmentIndex, segmentObject.get("end").toInt());
         }
      }
   }
}

void Maestro::processPassthrough()
{
   const bool on = getTempo().isRunningOrFirstTick();

   uint8_t passthroughValues[Tracker::Project::laneCount];
   for (uint8_t laneIndex = 0; laneIndex < 16; laneIndex++)
   {
      const float value = on ? input.getVoltage(laneIndex) : 0.0;
      output.setVoltage(value, laneIndex);

      passthroughValues[laneIndex] = voltageToValue(value);
   }

   if (uploadInput.isTriggered())
   {
      Svin::Json::Array stateArray;
      for (uint8_t laneIndex = 0; laneIndex < Tracker::Project::laneCount; laneIndex++)
         stateArray.append(passthroughValues[laneIndex]);

      Svin::Json::Object object;
      object.set("_Application", "Tracker");
      object.set("_Type", "State");
      object.set("bank", bankIndex);
      object.set("state", stateArray);

      sendDocumentToHub(1, object);
   }
}

void Maestro::proccessRemote()
{
   const bool on = getTempo().isRunningOrFirstTick();

   for (uint8_t laneIndex = 0; laneIndex < 16; laneIndex++)
   {
      const uint8_t value = on ? remoteValues[laneIndex] : 0;
      const float voltage = valueToVoltage(value);
      output.setVoltage(voltage, laneIndex);
   }
}

void Maestro::processInternal()
{
   const Tempo tempo = getTempo();
   const bool on = tempo.isRunningOrFirstTick();
   const uint32_t currentIndex = project.getCurrentSegmentIndex();
   const float tickPercentage = tempo.getPercentage();
   const float segmentPercentage = project.getCurrentSegmentPrecentage(tickPercentage);

   for (uint8_t laneIndex = 0; laneIndex < 16; laneIndex++)
   {
      const Tracker::Lane& lane = project.getLane(laneIndex);

      const uint8_t value = on ? lane.getSegmentValue(currentIndex, segmentPercentage) : 0.0;

      const float voltage = valueToVoltage(value);
      output.setVoltage(voltage, laneIndex);
   }
}

void Maestro::updateDisplays()
{
   controller.fill();

   if (Maestro::OperationMode::Passthrough == operationMode)
      updatePassthrough();
   else if (Maestro::OperationMode::Remote == operationMode)
      updateRemote();
   else if (Maestro::OperationMode::InternalOverview == operationMode)
      updateInternalOverview();
   else if (Maestro::OperationMode::InternalCurrent == operationMode)
      updateInternalCurrent();

   const uint32_t index = project.getCurrentSegmentIndex();

   Svin::Json::Object object;
   object.set("_Application", "Tracker");
   object.set("_Type", "Index");
   object.set("index", index);
   object.set("bank", bankIndex);
   object.set("mode", static_cast<uint8_t>(operationMode));

   sendDocumentToHub(1, object);
}

void Maestro::updatePassthrough()
{
   controller.setColor(Svin::Color{0, 255, 0});
   controller.drawRect(0, 0, 100, 10, true);

   controller.writeText(50, 20, std::to_string(bankIndex), Svin::DisplayOLED::Font::Large, Svin::DisplayOLED::Alignment::Center);

   controller.setColor(Svin::Color{0, 0, 0});
   controller.writeText(50, 0, "Passthrough", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   const Tempo tempo = getTempo();
   const bool on = tempo.isRunningOrFirstTick();

   for (uint8_t laneIndex = 0; laneIndex < 16; laneIndex++)
   {
      const Tracker::Lane& lane = project.getLane(laneIndex);
      controller.setColor(Svin::Color{155, 155, 155});

      const uint8_t column = (laneIndex < 8) ? 0 : 1;
      const uint8_t row = (laneIndex < 8) ? laneIndex : laneIndex - 8;

      const uint8_t y = 55 + 10 * row;

      std::string name = lane.getName();
      if (name.length() > 4)
         name = name.substr(0, 4);
      const uint8_t xName = 4 + (column * 50);
      controller.writeText(xName, y + 1, name, Svin::DisplayOLED::Font::Small, Svin::DisplayOLED::Alignment::Left);

      controller.setColor(Svin::Color{255, 255, 255});

      const float voltage = input.getVoltage(laneIndex);
      const uint8_t value = voltageToValue(voltage);
      const std::string valueText = on ? Text::convert(value) : "off";
      const uint8_t xVoltage = 46 + (column * 50);
      controller.writeText(xVoltage, y, valueText, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Right);
   }
}

void Maestro::updateRemote()
{
   controller.setColor(Svin::Color{0, 255, 255});
   controller.drawRect(0, 0, 100, 10, true);

   controller.writeText(50, 20, std::to_string(bankIndex), Svin::DisplayOLED::Font::Large, Svin::DisplayOLED::Alignment::Center);

   controller.setColor(Svin::Color{0, 0, 0});
   controller.writeText(50, 0, "Remote", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   controller.setColor(Svin::Color{255, 255, 255});

   const Tempo tempo = getTempo();
   const bool on = tempo.isRunningOrFirstTick();

   for (uint8_t laneIndex = 0; laneIndex < 16; laneIndex++)
   {
      const Tracker::Lane& lane = project.getLane(laneIndex);
      controller.setColor(Svin::Color{155, 155, 155});

      const uint8_t column = (laneIndex < 8) ? 0 : 1;
      const uint8_t row = (laneIndex < 8) ? laneIndex : laneIndex - 8;

      const uint8_t y = 55 + 10 * row;

      std::string name = lane.getName();
      if (name.length() > 4)
         name = name.substr(0, 4);
      const uint8_t xName = 4 + (column * 50);
      controller.writeText(xName, y + 1, name, Svin::DisplayOLED::Font::Small, Svin::DisplayOLED::Alignment::Left);

      controller.setColor(Svin::Color{255, 255, 255});

      const uint8_t value = remoteValues[laneIndex];
      const std::string valueText = on ? Text::convert(value) : "off";
      const uint8_t xValue = 46 + (column * 50);
      controller.writeText(xValue, y, valueText, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Right);
   }
}

void Maestro::updateInternalOverview()
{
   controller.setColor(Svin::Color{255, 255, 0});
   controller.drawRect(0, 0, 100, 10, true);

   controller.setColor(Svin::Color{0, 0, 0});
   controller.writeText(50, 0, "Overview", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   controller.setColor(Svin::Color{255, 255, 255});
   controller.writeText(0, 175, fileName, 3);

   const uint32_t segmentCount = project.getSegmentCount();
   controller.writeText(5, 15, std::to_string(segmentCount) + " segments", Svin::DisplayOLED::Font::Normal);

   //const std::string divName = Tempo::getName(project.getDefaultDivison());
   //controller.writeText(5, 30, "@ " + divName, Svin::DisplayOLED::Font::Normal);

   const uint32_t index = project.getCurrentSegmentIndex();
   if (index < segmentCount)
   {
      controller.writeText(50, 70, std::to_string(index), Svin::DisplayOLED::Font::Huge, Svin::DisplayOLED::Alignment::Center);

      const std::string eventName = eventNameList.at(index);
      const std::string eventText = eventName.empty() ? "--" : eventName;
      controller.writeText(50, 100, eventText, Svin::DisplayOLED::Font::Large, Svin::DisplayOLED::Alignment::Center);

      if (eventName.empty())
         controller.writeText(50, 125, lastNamedSegement, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);
      else
         lastNamedSegement = eventName;
   }
   else
   {
      controller.setColor(Svin::Color{255, 255, 0});
      controller.writeText(50, 70, "END", Svin::DisplayOLED::Font::Huge, Svin::DisplayOLED::Alignment::Center);
   }
}

void Maestro::updateInternalCurrent()
{
   controller.setColor(Svin::Color{255, 0, 255});
   controller.drawRect(0, 0, 100, 10, true);

   controller.writeText(50, 20, std::to_string(bankIndex), Svin::DisplayOLED::Font::Large, Svin::DisplayOLED::Alignment::Center);

   controller.setColor(Svin::Color{0, 0, 0});
   controller.writeText(50, 0, "Current", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   const Tempo tempo = getTempo();
   const bool on = tempo.isRunningOrFirstTick();
   const uint32_t currentIndex = project.getCurrentSegmentIndex();
   const float tickPercentage = tempo.getPercentage();
   const float segmentPercentage = project.getCurrentSegmentPrecentage(tickPercentage);

   for (uint8_t laneIndex = 0; laneIndex < 16; laneIndex++)
   {
      const Tracker::Lane& lane = project.getLane(laneIndex);
      controller.setColor(Svin::Color{155, 155, 155});

      const uint8_t column = (laneIndex < 8) ? 0 : 1;
      const uint8_t row = (laneIndex < 8) ? laneIndex : laneIndex - 8;

      const uint8_t y = 55 + 10 * row;

      std::string name = lane.getName();
      if (name.length() > 4)
         name = name.substr(0, 4);
      const uint8_t xName = 4 + (column * 50);
      controller.writeText(xName, y + 1, name, Svin::DisplayOLED::Font::Small, Svin::DisplayOLED::Alignment::Left);

      controller.setColor(Svin::Color{255, 255, 255});

      const uint8_t value = on ? lane.getSegmentValue(currentIndex, segmentPercentage) : 0.0;
      const std::string valueText = on ? Text::convert(value) : "off";
      const uint8_t xVoltage = 46 + (column * 50);
      controller.writeText(xVoltage, y, valueText, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Right);
   }
}

void Maestro::receivedDocumentFromHub(const ::Midi::Channel& channel, const Svin::Json::Object& object, const uint8_t docIndex)
{
   if (1 != channel || 0 != docIndex)
      return;

   if ("Tracker" != object.get("_Application").toString())
      return;

   if ("Remote" == object.get("_Type").toString())
   {
      Svin::Json::Array stateArray = object.get("state").toArray();
      if (32 != stateArray.size())
      {
         std::cout << "malformed state array from remote" << std::endl;
         return;
      }

      const uint8_t objectBankIndex = object.get("bank").toInt();
      if (objectBankIndex != bankIndex)
         return;

      for (uint8_t laneIndex = 0; laneIndex < 32; laneIndex++)
      {
         const uint8_t value = stateArray.at(laneIndex).toInt();
         remoteValues[laneIndex] = value;
      }

      const uint32_t index = object.get("index").toInt();
      project.setCurrentSegmentIndex(index);
   }
   else if ("Reload" == object.get("_Type").toString())
   {
      const uint8_t objectBankIndex = object.get("bank").toInt();
      if (objectBankIndex != bankIndex)
         return;

      const std::string fileName = object.get("fileName").toString();
      loadProject(fileName);
   }
}

void Maestro::load(const Svin::Json::Object& rootObject)
{
   bankIndex = rootObject.get("bank").toInt();
   operationMode = static_cast<OperationMode>(rootObject.get("operation").toInt());   

   bool loop = rootObject.get("loop").toBool();
   project.setLooping(loop);

   const std::string newFileName = rootObject.get("fileName").toString();
   loadProject(newFileName);
}

void Maestro::save(Svin::Json::Object& rootObject)
{
   rootObject.set("bank", bankIndex);
   rootObject.set("operation", static_cast<uint8_t>(operationMode));
   rootObject.set("loop", project.isLooping());

   rootObject.set("fileName", fileName);
}

// widget

MaestroWidget::MaestroWidget(Maestro* module)
   : Svin::ModuleWidget(module)
{
   setup();
}
// creete module
Model* modelMaestro = Svin::Origin::the()->addModule<Maestro, MaestroWidget>("Maestro");
