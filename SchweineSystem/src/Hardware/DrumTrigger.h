#ifndef DrumTriggerH
#define DrumTriggerH

#include <rack.hpp>
using namespace rack;

#include <SvinMidi.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <Tools/Flank.h>

#include <SvinButton.h>
#include <SvinButtonLED.h>
#include <SvinInput.h>
#include <SvinLED.h>

class DrumTrigger : public Svin::Module, public Svin::MidiOutput
{
public:
   struct Panel;

public:
   DrumTrigger();

public:
   void process(const ProcessArgs& args) override;

private:
   struct DeviceId
   {
      enum Value
      {
         Erika = 0,
         BitBox2 = 1,
         BitBoxMini = 2
      };
   };

   using DeviceMap = std::map<DeviceId::Value, Midi::Device::Channel>;
   using DeviceOrder = std::vector<DeviceId::Value>;

private:
   inline void setup();
   void updateDisplays() override;
   void connectToMidiDevice();

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   static const DeviceMap deviceMap;
   static const DeviceOrder deviceOrder;

   Svin::Button deviceButton;
   Svin::LED::List deviceLightList;
   DeviceId::Value deviceId;

   Svin::Input input;
   Svin::ButtonLED connectionButton;
   Flank flank[16];
};

// widget

class DrumTriggerWidget : public Svin::ModuleWidget
{
public:
   DrumTriggerWidget(DrumTrigger* module);

private:
   inline void setup();
};

#ifndef DrumTriggerHPP
#include "DrumTrigger.hpp"
#endif // NOT DrumTriggerHPP

#endif // NOT DrumTriggerH
