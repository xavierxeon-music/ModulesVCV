#include "Mapper.h"

#include <Tools/Variable.h>

//section

Mapper::Section::Section(Mapper* module, const uint16_t modeId, const uint16_t& fiveVoltId, const uint16_t eightVoltId, const uint16_t tenVoltId, const uint8_t rangeId)
   : modeButton(module, modeId)
   , voltLights(module)
   , rangeSwitch(module, rangeId)
   , maxVoltage(VoltageTen)
{
   voltLights.append({fiveVoltId, eightVoltId, tenVoltId});
}

void Mapper::Section::setup()
{
   for (uint8_t index = 0; index < 3; index++)
      voltLights[index]->setDefaultColor(Color{255, 255, 0});
}

Mapper::MinMax Mapper::Section::compileMinMax()
{
   static const std::map<Max, float> voltageMap = {{VoltageFive, 5.0}, {VoltageEight, 8.0}, {VoltageTen, 10.0}};

   if (modeButton.isTriggered())
   {
      static const std::vector<Max> voltageList = {VoltageFive, VoltageEight, VoltageTen};
      Variable::Enum<Max> variable(maxVoltage, voltageList, true);
      variable.increment();
   }

   for (uint8_t index = 0; index < 3; index++)
      voltLights[index]->setActive(index == maxVoltage);

   const float value = voltageMap.at(maxVoltage);

   if (rangeSwitch.isOn()) // bipolar
      return {-value, value};

   return {0.0, value};
}

void Mapper::Section::load(const std::string& key, const Svin::Json::Object& rootObject)
{
   const Svin::Json::Object sectionObject = rootObject.get(key).toObject();
   maxVoltage = static_cast<Max>(sectionObject.get("max").toInt());
   rangeSwitch.setState(sectionObject.get("full_range").toBool());
}

void Mapper::Section::save(const std::string& key, Svin::Json::Object& rootObject)
{
   Svin::Json::Object sectionObject;
   sectionObject.set("max", static_cast<uint8_t>(maxVoltage));
   sectionObject.set("full_range", rangeSwitch.isOn());

   rootObject.set(key, sectionObject);
}

// mapper

Mapper::Mapper()
   : Svin::Module()
   , inputSection(this, Panel::Input_Max, Panel::RGB_Input_5V, Panel::RGB_Input_8V, Panel::RGB_Input_10V, Panel::Input_Range)
   , cvInput(this, Panel::Input_In)
   , outputSection(this, Panel::Output_Max, Panel::RGB_Output_5V, Panel::RGB_Output_8V, Panel::RGB_Output_10V, Panel::Output_Range)
   , cvOutput(this, Panel::Output_Out)
   , mapper(0, 1, 0, 1)
{
   setup();
   inputSection.setup();
   outputSection.setup();
}

void Mapper::process(const ProcessArgs& args)
{
   const MinMax inMinMax = inputSection.compileMinMax();
   mapper.setMinInput(inMinMax.min);
   mapper.setMaxInput(inMinMax.max);

   const MinMax outMinMax = outputSection.compileMinMax();
   mapper.setMinOutput(outMinMax.min);
   mapper.setMaxOutput(outMinMax.max);

   const uint8_t noOfChannels = cvInput.getNumberOfChannels();
   cvOutput.setNumberOfChannels(noOfChannels);

   for (uint8_t channel = 0; channel < noOfChannels; channel++)
   {
      const float inVoltage = cvInput.getVoltage(channel);
      const float outVoltage = mapper(inVoltage);
      cvOutput.setVoltage(outVoltage, channel);
   }
}

void Mapper::load(const Svin::Json::Object& rootObject)
{
   inputSection.load("input", rootObject);
   outputSection.load("output", rootObject);
}

void Mapper::save(Svin::Json::Object& rootObject)
{
   inputSection.save("input", rootObject);
   outputSection.save("output", rootObject);
}

// widget

MapperWidget::MapperWidget(Mapper* module)
: Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelMapper = Svin::Origin::the()->addModule<Mapper, MapperWidget>("Mapper");

