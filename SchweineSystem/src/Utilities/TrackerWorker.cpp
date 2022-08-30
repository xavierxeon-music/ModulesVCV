#include "TrackerWorker.h"
#include "TrackerWorkerPanel.h"

#include <Midi/MidiCommon.h>
#include <Tools/Convert.h>
#include <Tools/File.h>
#include <Tools/SevenBit.h>
#include <Tools/Variable.h>

#include <SvinMasterClock.h>
#include <SvinOrigin.h>

TrackerWorker::TrackerWorker()
   : Svin::Module()
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
   , display(this)
{
   setup();

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
   const Svin::MasterClock* clock = Svin::MasterClock::the();
   if (OperationMode::Passthrough == operationMode)
   {
      processPassthrough();
   }
   else if (OperationMode::Remote == operationMode)
   {
      proccessRemote();
   }
   else if (clock)
   {
      if (Svin::MasterClock::Signal::Reset == clock->getSignal())
         project.clockReset();
      else if (Svin::MasterClock::Signal::Tick == clock->getSignal())
         project.clockTick();

      processInternal();
   }
   else
   {
      zeroOutputs();
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

      project.clear(division, segmentCount);

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
   const Svin::MasterClock* clock = Svin::MasterClock::the();
   if (!clock)
      return zeroOutputs();

   const bool on = clock->getTempo().isRunningOrFirstTick();

   for (uint8_t groupIndex = 0; groupIndex < 2; groupIndex++)
   {
      for (uint8_t channelIndex = 0; channelIndex < 16; channelIndex++)
      {
         const float value = on ? inputList[groupIndex]->getVoltage(channelIndex) : 0.0;
         outputList[groupIndex]->setVoltage(value, channelIndex);
      }
   }

   if (uploadInput.isTriggered())
   {
   }
}

void TrackerWorker::proccessRemote()
{
   const Svin::MasterClock* clock = Svin::MasterClock::the();
   if (!clock)
      return zeroOutputs();

   const bool on = clock->getTempo().isRunningOrFirstTick();

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
   const Svin::MasterClock* clock = Svin::MasterClock::the();
   if (!clock)
      return zeroOutputs();

   const bool on = clock->getTempo().isRunningOrFirstTick();
   const uint32_t currentIndex = project.getCurrentSegmentIndex();
   const float percentage = clock->getTempo().getPercentage(project.getDivison());

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

void TrackerWorker::zeroOutputs()
{
   for (uint8_t groupIndex = 0; groupIndex < 2; groupIndex++)
   {
      for (uint8_t channelIndex = 0; channelIndex < 16; channelIndex++)
      {
         outputList[groupIndex]->setVoltage(0.0, channelIndex);
      }
   }
}

void TrackerWorker::updateDisplays()
{
   display.update();
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
