#ifndef MapperH
#define MapperH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <Tools/Range.h>

#include <SvinButton.h>
#include <SvinLED.h>
#include <SvinSwitch.h>
#include <SvinInput.h>
#include <SvinOutput.h>

class Mapper : public Svin::Module
{
public:
   struct Panel;

public:
   Mapper();

public:
   void process(const ProcessArgs& args) override;

private:
   struct MinMax
   {
      float min;
      float max;
   };

   class Section
   {
   public:
      Section(Mapper* module, const uint16_t modeId, const uint16_t& fiveVoltId, const uint16_t eightVoltId, const uint16_t tenVoltId, const uint8_t rangeId);

   public:
      void setup();
      MinMax compileMinMax();

      void load(const std::string& key, const Svin::Json::Object& rootObject);
      void save(const std::string& key, Svin::Json::Object& rootObject);

   private:
      enum Max
      {
         VoltageFive = 0,
         VoltageEight = 1,
         VoltageTen = 2
      };

   private:
      Svin::Button modeButton;
      Svin::LED::List voltLights;
      Svin::Switch rangeSwitch;
      Max maxVoltage;
   };

private:
   inline void setup();

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   Section inputSection;
   Svin::Input cvInput;

   Section outputSection;
   Svin::Output cvOutput;

   Range::Mapper mapper;
};

// widget

class MapperWidget : public Svin::ModuleWidget
{
public:
   MapperWidget(Mapper* module);

private:
   inline void setup();
};

#ifndef MapperHPP
#include "Mapper.hpp"
#endif // NOT MapperHPP

#endif // NOT MapperH
