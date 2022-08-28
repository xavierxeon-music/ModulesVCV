#include "TrackerWorker.h"
#include "TrackerWorkerPanel.h"

#include <osdialog.h>

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
   , displayMode(DisplayMode::StageIndex)
   , displayButton(this, Panel::Display)
   , displayController(this, Panel::Pixels_Display)
   // mode
   , operationMode(OperationMode::Passthrough)
   , operationModeButton(this, Panel::ModeManual)
   , remoteValues{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
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

   // screen mode
   if (displayButton.isTriggered())
   {
      static const std::vector<DisplayMode> order = {DisplayMode::Division, DisplayMode::Length, DisplayMode::StageCount, DisplayMode::StageIndex};
      Variable::Enum<DisplayMode> variable(displayMode, order, true);
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
   displayController.fill();

   if (OperationMode::Passthrough == operationMode)
      updateDisplayPassthrough();
   else if (OperationMode::Remote == operationMode)
      updateDisplayRemote();
   else if (OperationMode::Internal == operationMode)
      updateDisplayInternal();
}

void TrackerWorker::updateDisplayPassthrough()
{
   displayController.setColor(Svin::Color{0, 255, 0});
   displayController.drawRect(0, 0, 100, 10, true);

   displayController.setColor(Svin::Color{0, 0, 0});
   displayController.writeText(5, 1, "Passthrough", Svin::DisplayOLED::Font::Normal);

   displayController.setColor(Svin::Color{0, 255, 0});

   for (uint8_t channelIndex = 0; channelIndex < 16; channelIndex++)
   {
      const uint8_t y = 15 + 10 * channelIndex;

      for (uint8_t groupIndex = 0; groupIndex < 2; groupIndex++)
      {
         const uint8_t x = 50 + groupIndex * 40;

         const float voltage = inputList[groupIndex]->getVoltage(channelIndex);
         const uint8_t value = voltageToValue(voltage);
         const std::string valueText = tempo.isRunningOrFirstTick() ? Convert::text(value) : "off";
         displayController.writeText(x, y, valueText, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Right);
      }
   }
}

void TrackerWorker::updateDisplayRemote()
{
   displayController.setColor(Svin::Color{0, 255, 255});
   displayController.drawRect(0, 0, 100, 10, true);

   displayController.setColor(Svin::Color{0, 0, 0});
   displayController.writeText(5, 1, "Remote", Svin::DisplayOLED::Font::Normal);

   displayController.setColor(Svin::Color{0, 255, 255});

   for (uint8_t channelIndex = 0; channelIndex < 16; channelIndex++)
   {
      const uint8_t y = 15 + 10 * channelIndex;

      for (uint8_t groupIndex = 0; groupIndex < 2; groupIndex++)
      {
         const uint8_t x = 50 + groupIndex * 40;

         const uint8_t value = remoteValues[16 * groupIndex + channelIndex];
         const std::string valueText = tempo.isRunningOrFirstTick() ? Convert::text(value) : "off";
         displayController.writeText(x, y, valueText, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Right);
      }
   }
}

void TrackerWorker::updateDisplayInternal()
{
   displayController.setColor(Svin::Color{255, 255, 255});
   displayController.drawRect(0, 0, 100, 10, true);

   displayController.setColor(Svin::Color{0, 0, 0});

   if (DisplayMode::Division == displayMode)
      displayController.writeText(5, 1, "Step", Svin::DisplayOLED::Font::Normal);
   else if (DisplayMode::Length == displayMode)
      displayController.writeText(5, 1, "Length", Svin::DisplayOLED::Font::Normal);
   else if (DisplayMode::StageCount == displayMode)
      displayController.writeText(5, 1, "Count", Svin::DisplayOLED::Font::Normal);
   else
      displayController.writeText(5, 1, "Current", Svin::DisplayOLED::Font::Normal);

   displayController.setColor(Svin::Color{255, 255, 255});

   displayController.writeText(5, 20, "Hello", Svin::DisplayOLED::Font::Normal);
}

void TrackerWorker::load(const Svin::Json::Object& rootObject)
{
   displayMode = static_cast<DisplayMode>(rootObject.get("display").toInt());
   operationMode = static_cast<OperationMode>(rootObject.get("operation").toInt());

   const std::string newFileName = rootObject.get("fileName").toString();
   loadProject(newFileName);
}

void TrackerWorker::save(Svin::Json::Object& rootObject)
{
   rootObject.set("display", static_cast<uint8_t>(displayMode));
   rootObject.set("operation", static_cast<uint8_t>(operationMode));

   rootObject.set("fileName", fileName);
}

// widget

TrackerWorkerWidget::TrackerWorkerWidget(TrackerWorker* module)
: Svin::ModuleWidget(module)
{
   setup();

   using OLEDWidget = Svin::DisplayOLED::Widget;

   OLEDWidget* oled = OLEDWidget::find(module, TrackerWorker::Panel::Pixels_Display);
   if (oled)
      oled->onClicked(this, &TrackerWorkerWidget::displayClicked);
}

void TrackerWorkerWidget::displayClicked(const float& x, const float& y)
{
   (void)x;
   (void)y;

   TrackerWorker* myModule = dynamic_cast<TrackerWorker*>(getSchweineModule());
   if (!myModule)
      return;

   const char* path = osdialog_file(OSDIALOG_OPEN, nullptr, NULL, osdialog_filters_parse("Projects:json"));
   if (path)
      myModule->loadProject(std::string(path));
}

Model* modelTrackerWorker = Svin::Master::the()->addModule<TrackerWorker, TrackerWorkerWidget>("TrackerWorker");
