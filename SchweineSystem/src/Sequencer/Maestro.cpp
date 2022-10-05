#include "Maestro.h"

#include <Tools/File.h>
#include <Tools/Text.h>
#include <Tools/Variable.h>

#include <SvinOrigin.h>

Maestro::Maestro()
   : Svin::Module()
   , Svin::MasterClock::Client()
   , fileName()
   , contourPoly()
   // bank
   , bankIndex(0)
   , bankUpButton(this, Panel::BankUp)
   , bankDownButton(this, Panel::BankDown)
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
   // display
   , controller(this, Panel::Pixels_Display)
   , lastNamedSegement()
{
   setup();
   registerHubClient("Maestro");

   controller.onClickedOpenFileFunction(this, &Maestro::loadProject, "Projects:json");

   loopButton.setDefaultColor(Color{0, 255, 0});
}

void Maestro::process(const ProcessArgs& args)
{
   if (loopButton.isTriggered())
   {
      bool loop = contourPoly.isLooping();
      loop ^= true;
      contourPoly.setLooping(loop);
   }
   loopButton.setActive(contourPoly.isLooping());

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
      return processPassthrough();
   else if (OperationMode::Remote == operationMode)
      return proccessRemote();

   if (hasReset())
   {
      contourPoly.clockReset();
      return;
   }

   bool doProcess = true;
   while (hasTick())
   {
      contourPoly.clockTick();
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
   const Object projectObject = rootObject.get("project").toObject();

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

   contourPoly.clear();
   contourPoly.update(division, segmentCount);

   // header
   {
      Svin::Json::Object headerObject = projectObject.get("header").toObject();
      for (uint32_t segmentIndex = 0; segmentIndex < segmentCount; segmentIndex++)
      {
         const std::string segmentKey = compileSegmentKey(segmentIndex);
         if (!headerObject.hasKey(segmentKey))
            continue;

         Svin::Json::Object segmentObject = headerObject.get(segmentKey).toObject();
         contourPoly.setSegmentName(segmentIndex, segmentObject.get("name").toString());

         if (segmentObject.hasKey("length"))
         {
            contourPoly.setSegmentLength(segmentIndex, segmentObject.get("length").toInt());
         }
         if (segmentObject.hasKey("fgColor"))
         {
            const Svin::Json::Array colorArray = segmentObject.get("fgColor").toArray();
            contourPoly.setSegmentForegroundColor(segmentIndex, compileColor(colorArray));
         }

         if (segmentObject.hasKey("bgColor"))
         {
            const Svin::Json::Array colorArray = segmentObject.get("bgColor").toArray();
            contourPoly.setSegmentBackgroundColor(segmentIndex, compileColor(colorArray));
         }
      }
   }

   // cells
   {
      Array contourArray = projectObject.get("contours").toArray();
      if (contourPoly.getContourCount() != contourArray.size())
      {
         std::cout << newFileName << " " << (uint16_t)contourPoly.getContourCount() << " " << contourArray.size() << std::endl;
         return;
      }

      for (uint8_t contourIndex = 0; contourIndex < contourPoly.getContourCount(); contourIndex++)
      {
         Contour& contour = contourPoly.getContour(contourIndex);
         Object contourObject = contourArray.at(contourIndex).toObject();
         contour.setName(contourObject.get("name").toString());

         for (uint32_t segmentIndex = 0; segmentIndex < segmentCount; segmentIndex++)
         {
            const std::string segmentKey = compileSegmentKey(segmentIndex);
            if (!contourObject.hasKey(segmentKey))
               continue;

            Object segmentObject = contourObject.get(segmentKey).toObject();
            contour.setSegmentSteady(segmentIndex, segmentObject.get("steady").toBool());

            if (segmentObject.hasKey("start"))
               contour.setSegmentStartValue(segmentIndex, segmentObject.get("start").toInt());
            if (segmentObject.hasKey("end"))
               contour.setSegmentEndValue(segmentIndex, segmentObject.get("end").toInt());
         }
      }
   }
}

void Maestro::processPassthrough()
{
   const bool on = getTempo().isRunningOrFirstTick();

   uint8_t passthroughValues[Contour::Poly::contourCount];
   for (uint8_t contourIndex = 0; contourIndex < 16; contourIndex++)
   {
      const float value = on ? input.getVoltage(contourIndex) : 0.0;
      output.setVoltage(value, contourIndex);

      passthroughValues[contourIndex] = voltageToValue(value);
   }

   if (uploadInput.isTriggered())
   {
      Svin::Json::Array stateArray;
      for (uint8_t contourIndex = 0; contourIndex < Contour::Poly::contourCount; contourIndex++)
         stateArray.append(passthroughValues[contourIndex]);

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

   for (uint8_t contourIndex = 0; contourIndex < 16; contourIndex++)
   {
      const uint8_t value = on ? remoteValues[contourIndex] : 0;
      const float voltage = valueToVoltage(value);
      output.setVoltage(voltage, contourIndex);
   }
}

void Maestro::processInternal()
{
   const Tempo tempo = getTempo();
   const bool on = tempo.isRunningOrFirstTick();
   const uint32_t currentIndex = contourPoly.getCurrentSegmentIndex();
   const float tickPercentage = tempo.getPercentage();
   const float segmentPercentage = contourPoly.getCurrentSegmentPrecentage(tickPercentage);

   for (uint8_t contourIndex = 0; contourIndex < 16; contourIndex++)
   {
      const Contour& contour = contourPoly.getContour(contourIndex);

      const uint8_t value = on ? contour.getSegmentValue(currentIndex, segmentPercentage) : 0.0;

      const float voltage = valueToVoltage(value);
      output.setVoltage(voltage, contourIndex);
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

   const uint32_t index = contourPoly.getCurrentSegmentIndex();

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
   controller.setColor(Color{255, 255, 0});
   controller.drawRect(0, 0, 100, 10, true);

   controller.writeText(50, 20, std::to_string(bankIndex), Svin::DisplayOLED::Font::Large, Svin::DisplayOLED::Alignment::Center);

   controller.setColor(Color{0, 0, 0});
   controller.writeText(50, 0, "Passthrough", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   const Tempo tempo = getTempo();
   const bool on = tempo.isRunningOrFirstTick();

   for (uint8_t contourIndex = 0; contourIndex < 16; contourIndex++)
   {
      const Contour& contour = contourPoly.getContour(contourIndex);
      controller.setColor(Color{155, 155, 155});

      const uint8_t column = (contourIndex < 8) ? 0 : 1;
      const uint8_t row = (contourIndex < 8) ? contourIndex : contourIndex - 8;

      const uint8_t y = 55 + 10 * row;

      std::string name = contour.getName();
      if (name.length() > 4)
         name = name.substr(0, 4);
      const uint8_t xName = 4 + (column * 50);
      controller.writeText(xName, y + 1, name, Svin::DisplayOLED::Font::Small, Svin::DisplayOLED::Alignment::Left);

      controller.setColor(Color{255, 255, 255});

      const float voltage = input.getVoltage(contourIndex);
      const uint8_t value = voltageToValue(voltage);
      const std::string valueText = on ? Text::convert(value) : "off";
      const uint8_t xVoltage = 46 + (column * 50);
      controller.writeText(xVoltage, y, valueText, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Right);
   }
}

void Maestro::updateRemote()
{
   controller.setColor(Color{0, 255, 255});
   controller.drawRect(0, 0, 100, 10, true);

   controller.writeText(50, 20, std::to_string(bankIndex), Svin::DisplayOLED::Font::Large, Svin::DisplayOLED::Alignment::Center);

   controller.setColor(Color{0, 0, 0});
   controller.writeText(50, 0, "Remote", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   controller.setColor(Color{255, 255, 255});

   const Tempo tempo = getTempo();
   const bool on = tempo.isRunningOrFirstTick();

   for (uint8_t contourIndex = 0; contourIndex < 16; contourIndex++)
   {
      const Contour& contour = contourPoly.getContour(contourIndex);
      controller.setColor(Color{155, 155, 155});

      const uint8_t column = (contourIndex < 8) ? 0 : 1;
      const uint8_t row = (contourIndex < 8) ? contourIndex : contourIndex - 8;

      const uint8_t y = 55 + 10 * row;

      std::string name = contour.getName();
      if (name.length() > 4)
         name = name.substr(0, 4);
      const uint8_t xName = 4 + (column * 50);
      controller.writeText(xName, y + 1, name, Svin::DisplayOLED::Font::Small, Svin::DisplayOLED::Alignment::Left);

      controller.setColor(Color{255, 255, 255});

      const uint8_t value = remoteValues[contourIndex];
      const std::string valueText = on ? Text::convert(value) : "off";
      const uint8_t xValue = 46 + (column * 50);
      controller.writeText(xValue, y, valueText, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Right);
   }
}

void Maestro::updateInternalOverview()
{
   controller.setColor(Color{255, 0, 255});
   controller.drawRect(0, 0, 100, 10, true);

   controller.setColor(Color{0, 0, 0});
   controller.writeText(50, 0, "Overview", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   const Tempo tempo = getTempo();
   const bool on = tempo.isRunningOrFirstTick();

   const uint32_t segmentCount = contourPoly.getSegmentCount();
   const uint16_t digitCount = Variable::compileDigitCount(segmentCount);

   controller.setColor(Color{255, 255, 255});
   controller.writeText(5, 12, Text::pad(std::to_string(segmentCount), digitCount), Svin::DisplayOLED::Font::Large);
   controller.writeText(7 + 12 * digitCount, 17, "segmemnts", Svin::DisplayOLED::Font::Normal);

   if (0 == segmentCount || !on)
   {
      const uint8_t noOfLines = 10;
      const uint8_t noOfLetters = 14;

      const uint8_t x = 5;
      for (uint8_t counter = 0; counter < noOfLines; counter++)
      {
         const uint8_t row = noOfLines - (counter + 1);
         const uint8_t y = 30 + 10 * row;
         const int8_t index = fileName.length() - ((noOfLines - row) * noOfLetters);
         if (index >= 0)
         {
            const std::string text = fileName.substr(index, noOfLetters);
            controller.writeText(x, y, text, 10);
         }
         else
         {
            const std::string text = fileName.substr(0, noOfLetters + index);
            controller.writeText(x, y, Text::pad(text, noOfLetters, " "), 10);
            break;
         }
      }

      return;
   }

   const uint32_t index = contourPoly.getCurrentSegmentIndex();
   if (index < segmentCount)
   {
      controller.writeText(50, 50, Text::pad(std::to_string(index), digitCount), Svin::DisplayOLED::Font::Huge, Svin::DisplayOLED::Alignment::Center);

      const std::string eventName = contourPoly.getSegmentName(index);
      const std::string eventText = eventName.empty() ? "--" : eventName;
      controller.writeText(50, 80, eventText, Svin::DisplayOLED::Font::Large, Svin::DisplayOLED::Alignment::Center);

      if (eventName.empty())
         controller.writeText(50, 105, lastNamedSegement, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);
      else
         lastNamedSegement = eventName;
   }
   else
   {
      controller.setColor(Color{255, 255, 0});
      controller.writeText(50, 70, "END", Svin::DisplayOLED::Font::Huge, Svin::DisplayOLED::Alignment::Center);
   }
}

void Maestro::updateInternalCurrent()
{
   controller.setColor(Color{0, 255, 0});
   controller.drawRect(0, 0, 100, 10, true);

   controller.setColor(Color{0, 0, 0});
   controller.writeText(50, 0, "Current", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   const Tempo tempo = getTempo();
   const bool on = tempo.isRunningOrFirstTick();
   const uint32_t segmentCount = contourPoly.getSegmentCount();
   const uint16_t digitCount = Variable::compileDigitCount(segmentCount);

   const uint32_t currentIndex = contourPoly.getCurrentSegmentIndex();

   controller.setColor(Color{255, 255, 255});
   controller.writeText(50, 20, Text::pad(std::to_string(currentIndex), digitCount), Svin::DisplayOLED::Font::Large, Svin::DisplayOLED::Alignment::Center);

   const float tickPercentage = tempo.getPercentage();
   const float segmentPercentage = contourPoly.getCurrentSegmentPrecentage(tickPercentage);

   for (uint8_t contourIndex = 0; contourIndex < 16; contourIndex++)
   {
      const Contour& contour = contourPoly.getContour(contourIndex);
      controller.setColor(Color{155, 155, 155});

      const uint8_t column = (contourIndex < 8) ? 0 : 1;
      const uint8_t row = (contourIndex < 8) ? contourIndex : contourIndex - 8;

      const uint8_t y = 55 + 10 * row;

      std::string name = contour.getName();
      if (name.length() > 4)
         name = name.substr(0, 4);
      const uint8_t xName = 4 + (column * 50);
      controller.writeText(xName, y + 1, name, Svin::DisplayOLED::Font::Small, Svin::DisplayOLED::Alignment::Left);

      controller.setColor(Color{255, 255, 255});

      const uint8_t value = on ? contour.getSegmentValue(currentIndex, segmentPercentage) : 0.0;
      const std::string valueText = on ? Text::convert(value) : "off";
      const uint8_t xVoltage = 46 + (column * 50);
      controller.writeText(xVoltage, y, valueText, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Right);
   }
}

void Maestro::receivedDocumentFromHub(const ::Midi::Channel& channel, const Svin::Json::Object& object, const uint8_t docIndex)
{
   if (1 != channel || 0 != docIndex)
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

      for (uint8_t contourIndex = 0; contourIndex < 32; contourIndex++)
      {
         const uint8_t value = stateArray.at(contourIndex).toInt();
         remoteValues[contourIndex] = value;
      }

      const uint32_t index = object.get("index").toInt();
      contourPoly.setCurrentSegmentIndex(index);
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
   contourPoly.setLooping(loop);

   const std::string newFileName = rootObject.get("fileName").toString();
   loadProject(newFileName);
}

void Maestro::save(Svin::Json::Object& rootObject)
{
   rootObject.set("bank", bankIndex);
   rootObject.set("operation", static_cast<uint8_t>(operationMode));
   rootObject.set("loop", contourPoly.isLooping());

   rootObject.set("fileName", fileName);
}

// widget

MaestroWidget::MaestroWidget(Maestro* module)
   : Svin::ModuleWidget(module)
{
   setup();
}
// create module
Model* modelMaestro = Svin::Origin::the()->addModule<Maestro, MaestroWidget>("Maestro");
