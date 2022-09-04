#include "TrackerWorker.h"
#include "TrackerWorkerPanel.h"

#include <Midi/MidiCommon.h>
#include <Tools/Convert.h>
#include <Tools/File.h>
#include <Tools/SevenBit.h>
#include <Tools/Variable.h>

#include <SvinOrigin.h>

TrackerWorker::TrackerWorker()
   : Svin::Module()
   , Svin::Midi::Input("Tracker", true)
   , Svin::Midi::Output("Tracker", true)
   , Svin::MasterClock::Client()
   , fileName()
   , project()
   , eventNameList()
   // midi
   , receive(MidiReceive::None)
   , buffer()
   // input
   , inputList(this)
   , voltageToValue(0.0, 10.0, 0, 255)
   // upload
   , uploadInput(this, Panel::Upload)
   // outout
   , valueToVoltage(0.0, 255.0, 0.0, 10.0)
   , outputList(this)
   // mode
   , loopButton(this, Panel::Loop, Panel::RGB_Loop)
   , operationMode(OperationMode::Passthrough)
   , operationModeButton(this, Panel::Mode)
   , remoteValues{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
   , controller(this, TrackerWorker::Panel::Pixels_Display)
{
   setup();
   controller.onClickedOpenFileFunction(this, &TrackerWorker::loadProject, "Projects:json");

   inputList.append({Panel::Group1_Pass, Panel::Group2_Pass});
   outputList.append({Panel::Group1_Output, Panel::Group2_Output});

   loopButton.setDefaultColor(Svin::Color{0, 255, 0});
}

void TrackerWorker::process(const ProcessArgs& args)
{
   if (loopButton.isTriggered())
   {
      bool loop = project.isLooping();
      loop ^= true;
      project.setLooping(loop);
   }
   loopButton.setActive(project.isLooping());

   // operation mode
   if (operationModeButton.isTriggered())
   {
      static const std::vector<OperationMode> order = {OperationMode::Passthrough, OperationMode::Remote, OperationMode::InternalOverview, OperationMode::InternalCurrent};
      Variable::Enum<OperationMode> variable(operationMode, order, true);
      variable.increment();
   }

   for (uint8_t groupIndex = 0; groupIndex < 2; groupIndex++)
   {
      if (16 != outputList[groupIndex]->getNumberOfChannels())
         outputList[groupIndex]->setNumberOfChannels(16);
   }

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
   }
   else
   {
      bool doProcess = true;
      while (hasTick())
      {
         project.clockTick();
         doProcess = false;
      }
      if (doProcess)
         processInternal();
   }
}

void TrackerWorker::loadProject(const std::string& newFileName)
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
         eventNameList[index] = eventArray.get(index).toString();
   }
   {
      const Object projectObject = rootObject.get("project").toObject();

      const Tempo::Division division = static_cast<Tempo::Division>(projectObject.get("division").toInt());
      const uint32_t segmentCount = projectObject.get("segments").toInt();
      const uint16_t digitCount = Convert::compileDigitCount(segmentCount);

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
         Object laneObject = laneArray.get(laneIndex).toObject();
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

void TrackerWorker::processPassthrough()
{
   const bool on = getTempo().isRunningOrFirstTick();

   for (uint8_t groupIndex = 0; groupIndex < 2; groupIndex++)
   {
      for (uint8_t channelIndex = 0; channelIndex < 16; channelIndex++)
      {
         const float value = on ? inputList[groupIndex]->getVoltage(channelIndex) : 0.0;
         outputList[groupIndex]->setVoltage(value, channelIndex);
      }
   }

   if (uploadInput.isTriggered())
      uploadState();
}

void TrackerWorker::proccessRemote()
{
   const bool on = getTempo().isRunningOrFirstTick();

   for (uint8_t groupIndex = 0; groupIndex < 2; groupIndex++)
   {
      for (uint8_t channelIndex = 0; channelIndex < 16; channelIndex++)
      {
         const uint8_t laneIndex = 16 * groupIndex + channelIndex;
         const uint8_t value = on ? remoteValues[laneIndex] : 0;
         const float voltage = valueToVoltage(value);
         outputList[groupIndex]->setVoltage(voltage, channelIndex);
      }
   }
}

void TrackerWorker::processInternal()
{
   const Tempo tempo = getTempo();
   const bool on = tempo.isRunningOrFirstTick();
   const uint32_t currentIndex = project.getCurrentSegmentIndex();
   const float percentage = tempo.getPercentage(project.getDivison());

   for (uint8_t groupIndex = 0; groupIndex < 2; groupIndex++)
   {
      for (uint8_t channelIndex = 0; channelIndex < 16; channelIndex++)
      {
         const uint8_t laneIndex = 16 * groupIndex + channelIndex;
         const Tracker::Lane& lane = project.getLane(laneIndex);

         const uint8_t value = on ? lane.getSegmentValue(currentIndex, percentage) : 0.0;

         const float voltage = valueToVoltage(value);
         outputList[groupIndex]->setVoltage(voltage, channelIndex);
      }
   }
}

void TrackerWorker::updateDisplays()
{
   controller.fill();

   if (TrackerWorker::OperationMode::Passthrough == operationMode)
      updatePassthrough();
   else if (TrackerWorker::OperationMode::Remote == operationMode)
      updateRemote();
   else if (TrackerWorker::OperationMode::InternalOverview == operationMode)
      updateInternalOverview();
   else if (TrackerWorker::OperationMode::InternalCurrent == operationMode)
      updateInternalCurrent();
}

void TrackerWorker::updatePassthrough()
{
   controller.setColor(Svin::Color{0, 255, 0});
   controller.drawRect(0, 0, 100, 10, true);

   controller.setColor(Svin::Color{0, 0, 0});
   controller.writeText(50, 0, "Passthrough", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   controller.setColor(Svin::Color{255, 255, 255});

   const Tempo tempo = getTempo();
   const bool on = tempo.isRunningOrFirstTick();

   for (uint8_t channelIndex = 0; channelIndex < 16; channelIndex++)
   {
      const uint8_t y = 15 + 10 * channelIndex;

      for (uint8_t groupIndex = 0; groupIndex < 2; groupIndex++)
      {
         const uint8_t x = 50 + groupIndex * 40;

         const float voltage = inputList[groupIndex]->getVoltage(channelIndex);
         const uint8_t value = voltageToValue(voltage);
         const std::string valueText = on ? Convert::text(value) : "off";
         controller.writeText(x, y, valueText, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Right);
      }
   }
}

void TrackerWorker::updateRemote()
{
   controller.setColor(Svin::Color{0, 255, 255});
   controller.drawRect(0, 0, 100, 10, true);

   controller.setColor(Svin::Color{0, 0, 0});
   controller.writeText(50, 0, "Remote", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   controller.setColor(Svin::Color{255, 255, 255});

   const Tempo tempo = getTempo();
   const bool on = tempo.isRunningOrFirstTick();

   for (uint8_t channelIndex = 0; channelIndex < 16; channelIndex++)
   {
      const uint8_t y = 15 + 10 * channelIndex;

      for (uint8_t groupIndex = 0; groupIndex < 2; groupIndex++)
      {
         const uint8_t x = 50 + groupIndex * 40;

         const uint8_t value = remoteValues[16 * groupIndex + channelIndex];
         const std::string valueText = on ? Convert::text(value) : "off";
         controller.writeText(x, y, valueText, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Right);
      }
   }
}

void TrackerWorker::updateInternalOverview()
{
   controller.setColor(Svin::Color{255, 255, 0});
   controller.drawRect(0, 0, 100, 10, true);

   controller.setColor(Svin::Color{0, 0, 0});
   controller.writeText(50, 0, "Overview", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   controller.setColor(Svin::Color{255, 255, 255});
   controller.writeText(0, 175, fileName, 3);

   const uint32_t segmentCount = project.getSegmentCount();
   controller.writeText(5, 15, std::to_string(segmentCount) + " segments", Svin::DisplayOLED::Font::Normal);

   const std::string divName = Tempo::getName(project.getDivison());
   controller.writeText(5, 30, "@ " + divName, Svin::DisplayOLED::Font::Normal);

   const uint32_t index = project.getCurrentSegmentIndex();
   if (index < segmentCount)
   {
      controller.writeText(50, 70, std::to_string(index), Svin::DisplayOLED::Font::Huge, Svin::DisplayOLED::Alignment::Center);

      const std::string eventName = eventNameList.at(index);
      const std::string eventText = eventName.empty() ? "--" : eventName;
      controller.writeText(50, 100, eventText, Svin::DisplayOLED::Font::Large, Svin::DisplayOLED::Alignment::Center);
   }
   else
   {
      controller.setColor(Svin::Color{255, 255, 0});
      controller.writeText(50, 70, "END", Svin::DisplayOLED::Font::Huge, Svin::DisplayOLED::Alignment::Center);
   }
}

void TrackerWorker::updateInternalCurrent()
{
   controller.setColor(Svin::Color{255, 0, 255});
   controller.drawRect(0, 0, 100, 10, true);

   controller.setColor(Svin::Color{0, 0, 0});
   controller.writeText(50, 0, "Current", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   controller.setColor(Svin::Color{255, 255, 255});
   controller.writeText(0, 15, "Hello", Svin::DisplayOLED::Font::Normal);
}

void TrackerWorker::document(const ::Midi::Channel& channel, const Svin::Json::Object& object, const uint8_t docIndex)
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

      for (uint8_t laneIndex = 0; laneIndex < 32; laneIndex++)
      {
         const uint8_t value = stateArray.get(laneIndex).toInt();
         remoteValues[laneIndex] = value;
      }
   }
   else if ("Reload" == object.get("_Type").toString())
   {
      const std::string fileName = object.get("fileName").toString();
      loadProject(fileName);
   }
}

void TrackerWorker::uploadState()
{
   Svin::Json::Array stateArray;

   Svin::Json::Object object;
   object.set("_Application", "Tracker");
   object.set("_Type", "State");
   object.set("state", stateArray);

   sendDocument(1, object);
}

void TrackerWorker::load(const Svin::Json::Object& rootObject)
{
   operationMode = static_cast<OperationMode>(rootObject.get("operation").toInt());

   bool loop = rootObject.get("loop").toBool();
   project.setLooping(loop);

   const std::string newFileName = rootObject.get("fileName").toString();
   loadProject(newFileName);
}

void TrackerWorker::save(Svin::Json::Object& rootObject)
{
   rootObject.set("operation", static_cast<uint8_t>(operationMode));
   rootObject.set("loop", project.isLooping());

   rootObject.set("fileName", fileName);
}

// widget

TrackerWorkerWidget::TrackerWorkerWidget(TrackerWorker* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

Model* modelTrackerWorker = Svin::Origin::the()->addModule<TrackerWorker, TrackerWorkerWidget>("TrackerWorker");
