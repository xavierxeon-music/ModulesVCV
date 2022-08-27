#include "TrackerWorker.h"
#include "TrackerWorkerPanel.h"

#include <osdialog.h>

#include <Midi/MidiCommon.h>
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
   displayController.setColor(Svin::Color{0, 255, 0});
   displayController.drawRect(0, 0, 100, 10, true);

   displayController.setColor(Svin::Color{0, 0, 0});
   displayController.writeText(5, 1, "Passthrough", Svin::DisplayOLED::Font::Normal);

   displayController.setColor(Svin::Color{0, 255, 0});
   displayController.writeText(5, 20, "Hello", Svin::DisplayOLED::Font::Normal);

   if (uploadInput.isTriggered())
   {
   }
}

void TrackerWorker::proccessRemote()
{
   displayController.setColor(Svin::Color{0, 0, 255});
   displayController.drawRect(0, 0, 100, 10, true);

   displayController.setColor(Svin::Color{0, 0, 0});
   displayController.writeText(5, 1, "Remote", Svin::DisplayOLED::Font::Normal);

   displayController.setColor(Svin::Color{0, 0, 255});
   displayController.writeText(5, 20, "Hello", Svin::DisplayOLED::Font::Normal);
}

void TrackerWorker::processInternal()
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
}

void TrackerWorker::updateDisplayRemote()
{
}

void TrackerWorker::updateDisplayInternal()
{
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
