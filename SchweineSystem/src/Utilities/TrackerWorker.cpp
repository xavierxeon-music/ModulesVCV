#include "TrackerWorker.h"
#include "TrackerWorkerPanel.h"

#include <Midi/MidiCommon.h>
#include <Tools/Convert.h>
#include <Tools/File.h>
#include <Tools/SevenBit.h>
#include <Tools/Variable.h>

#include <SvinMaster.h>

TrackerWorker::TrackerWorker()
   : Svin::Module()
   , fileName()
   , project()
   // midi
   , receive(MidiReceive::None)
   , buffer()
   // clock
   , clockInput(this, Panel::Clock)
   , resetInput(this, Panel::Reset)
   , tempo()
   // input
   , inputList(this)
   , voltageToValue(0.0, 10.0, 0, 255)
   // upload
   , uploadInput(this, Panel::Upload)
   // outout
   , valueToVoltage(0.0, 255.0, 0.0, 10.0)
   , outputList(this)
   // display
   // mode
   , operationMode(OperationMode::Passthrough)
   , operationModeButton(this, Panel::ModeManual)
   , remoteValues{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
   , display(this)
{
   setup();

   inputList.append({Panel::Group1_Pass, Panel::Group2_Pass});
   outputList.append({Panel::Group1_Output, Panel::Group2_Output});
}

void TrackerWorker::process(const ProcessArgs& args)
{
   // clock
   const bool isClock = clockInput.isTriggered();
   const bool isReset = resetInput.isTriggered();

   if (isReset)
      tempo.clockReset();
   else if (isClock)
      tempo.clockTick();
   else
      tempo.advance(args.sampleRate);

   // operation mode
   if (operationModeButton.isTriggered())
   {
      static const std::vector<OperationMode> order = {OperationMode::Passthrough, OperationMode::Remote, OperationMode::Internal};
      Variable::Enum<OperationMode> variable(operationMode, order, true);
      variable.increment();
   }

   // do stuff
   if (OperationMode::Passthrough == operationMode)
      processPassthrough();
   else if (OperationMode::Remote == operationMode)
      proccessRemote();
   else if (OperationMode::Internal == operationMode)
      processInternal();
}

void TrackerWorker::loadProject(const std::string& newFileName)
{
   fileName = newFileName;

   const Bytes data = File::load(fileName);
   if (data.empty())
      return;

   using namespace Svin::Json;

   const Object rootObject(data);
}

void TrackerWorker::processPassthrough()
{
   for (uint8_t groupIndex = 0; groupIndex < 2; groupIndex++)
   {
      for (uint8_t channelIndex = 0; channelIndex < 16; channelIndex++)
      {
         const float value = tempo.isRunningOrFirstTick() ? inputList[groupIndex]->getVoltage(channelIndex) : 0.0;
         outputList[groupIndex]->setVoltage(value, channelIndex);
      }
   }

   if (uploadInput.isTriggered())
   {
   }
}

void TrackerWorker::proccessRemote()
{
   for (uint8_t groupIndex = 0; groupIndex < 2; groupIndex++)
   {
      for (uint8_t channelIndex = 0; channelIndex < 16; channelIndex++)
      {
         const float value = tempo.isRunningOrFirstTick() ? remoteValues[16 * groupIndex + channelIndex] : 0.0;
         outputList[groupIndex]->setVoltage(value, channelIndex);
      }
   }
}

void TrackerWorker::processInternal()
{
}

void TrackerWorker::updateDisplays()
{
   display.update();
}

void TrackerWorker::load(const Svin::Json::Object& rootObject)
{
   display.displayMode = static_cast<Display::Mode>(rootObject.get("display").toInt());
   operationMode = static_cast<OperationMode>(rootObject.get("operation").toInt());

   const std::string newFileName = rootObject.get("fileName").toString();
   loadProject(newFileName);
}

void TrackerWorker::save(Svin::Json::Object& rootObject)
{
   rootObject.set("display", static_cast<uint8_t>(display.displayMode));
   rootObject.set("operation", static_cast<uint8_t>(operationMode));

   rootObject.set("fileName", fileName);
}

// widget

TrackerWorkerWidget::TrackerWorkerWidget(TrackerWorker* module)
: Svin::ModuleWidget(module)
{
   setup();

}


Model* modelTrackerWorker = Svin::Master::the()->addModule<TrackerWorker, TrackerWorkerWidget>("TrackerWorker");
