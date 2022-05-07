#ifndef BitBusMeterAndFreezeH
#define BitBusMeterAndFreezeH

#include "BitBusCommon.h"
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

#include <Tools/BoolField.h>
#include <Tools/RingBuffer.h>

#include <SchweineSystemLED.h>

static constexpr uint16_t AverageBufferSize = 4800;

class BitBusMeterAndFreeze : public SchweineSystem::Module, public BitBusCommon
{
public:
   struct Panel;

public:
   BitBusMeterAndFreeze();
   ~BitBusMeterAndFreeze();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();

   void onAdd(const AddEvent& e) override;
   json_t* dataToJson() override;
   void dataFromJson(json_t* rootJson) override;

private:
   SchweineSystem::LED::List lightList;
   dsp::BooleanTrigger freezTrigger;
   bool freezeMode;
   BoolField8 freezeBuffer;
   dsp::BooleanTrigger sampleTrigger;     
};

class BitBusMeterAndFreezeWidget : public SchweineSystem::ModuleWidget
{
public:
   BitBusMeterAndFreezeWidget(BitBusMeterAndFreeze* module);

private:
   void setup();
};

#endif // NOT BitBusMeterAndFreezeH
