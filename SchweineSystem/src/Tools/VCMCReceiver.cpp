#include "VCMCReceiver.h"
#include "VCMCReceiverPanel.h"

#include "SchweineSystemLCDDisplay.h"
#include "SchweineSystemMaster.h"

VCMCReceiver::VCMCReceiver()
   : Module()
   , bpm(12)
   , lightMeterListCV(lights)
   , lightMeterListSlider(lights)
   , lightListGate(lights)
   , downTrigger()
   , upTrigger()

{
   setup();

   lightMeterListCV.append({{Panel::Red_Channel8_CV8_Status1, Panel::Red_Channel8_CV8_Status2, Panel::Red_Channel8_CV8_Status3, Panel::Red_Channel8_CV8_Status4, Panel::Red_Channel8_CV8_Status5},
                            {Panel::Red_Channel7_CV7_Status1, Panel::Red_Channel7_CV7_Status2, Panel::Red_Channel7_CV7_Status3, Panel::Red_Channel7_CV7_Status4, Panel::Red_Channel7_CV7_Status5},
                            {Panel::Red_Channel6_CV6_Status1, Panel::Red_Channel6_CV6_Status2, Panel::Red_Channel6_CV6_Status3, Panel::Red_Channel6_CV6_Status4, Panel::Red_Channel6_CV6_Status5},
                            {Panel::Red_Channel5_CV5_Status1, Panel::Red_Channel5_CV5_Status2, Panel::Red_Channel5_CV5_Status3, Panel::Red_Channel5_CV5_Status4, Panel::Red_Channel5_CV5_Status5},
                            {Panel::Red_Channel4_CV4_Status1, Panel::Red_Channel4_CV4_Status2, Panel::Red_Channel4_CV4_Status3, Panel::Red_Channel4_CV4_Status4, Panel::Red_Channel4_CV4_Status5},
                            {Panel::Red_Channel3_CV3_Status1, Panel::Red_Channel3_CV3_Status2, Panel::Red_Channel3_CV3_Status3, Panel::Red_Channel3_CV3_Status4, Panel::Red_Channel3_CV3_Status5},
                            {Panel::Red_Channel2_CV2_Status1, Panel::Red_Channel2_CV2_Status2, Panel::Red_Channel2_CV2_Status3, Panel::Red_Channel2_CV2_Status4, Panel::Red_Channel2_CV2_Status5},
                            {Panel::Red_Channel1_CV1_Status1, Panel::Red_Channel1_CV1_Status2, Panel::Red_Channel1_CV1_Status3, Panel::Red_Channel1_CV1_Status4, Panel::Red_Channel1_CV1_Status5}});

   lightMeterListSlider.append({{Panel::Red_Channel8_Slider8_Status1, Panel::Red_Channel8_Slider8_Status2, Panel::Red_Channel8_Slider8_Status3, Panel::Red_Channel8_Slider8_Status4, Panel::Red_Channel8_Slider8_Status5},
                                {Panel::Red_Channel7_Slider7_Status1, Panel::Red_Channel7_Slider7_Status2, Panel::Red_Channel7_Slider7_Status3, Panel::Red_Channel7_Slider7_Status4, Panel::Red_Channel7_Slider7_Status5},
                                {Panel::Red_Channel6_Slider6_Status1, Panel::Red_Channel6_Slider6_Status2, Panel::Red_Channel6_Slider6_Status3, Panel::Red_Channel6_Slider6_Status4, Panel::Red_Channel6_Slider6_Status5},
                                {Panel::Red_Channel5_Slider5_Status1, Panel::Red_Channel5_Slider5_Status2, Panel::Red_Channel5_Slider5_Status3, Panel::Red_Channel5_Slider5_Status4, Panel::Red_Channel5_Slider5_Status5},
                                {Panel::Red_Channel4_Slider4_Status1, Panel::Red_Channel4_Slider4_Status2, Panel::Red_Channel4_Slider4_Status3, Panel::Red_Channel4_Slider4_Status4, Panel::Red_Channel4_Slider4_Status5},
                                {Panel::Red_Channel3_Slider3_Status1, Panel::Red_Channel3_Slider3_Status2, Panel::Red_Channel3_Slider3_Status3, Panel::Red_Channel3_Slider3_Status4, Panel::Red_Channel3_Slider3_Status5},
                                {Panel::Red_Channel2_Slider2_Status1, Panel::Red_Channel2_Slider2_Status2, Panel::Red_Channel2_Slider2_Status3, Panel::Red_Channel2_Slider2_Status4, Panel::Red_Channel2_Slider2_Status5},
                                {Panel::Red_Channel1_Slider1_Status1, Panel::Red_Channel1_Slider1_Status2, Panel::Red_Channel1_Slider1_Status3, Panel::Red_Channel1_Slider1_Status4, Panel::Red_Channel1_Slider1_Status5}});

   lightListGate.append({Panel::Red_Channel8_Gate8_Status1, Panel::Red_Channel7_Gate7_Status1, Panel::Red_Channel6_Gate6_Status1, Panel::Red_Channel5_Gate5_Status1, Panel::Red_Channel4_Gate4_Status1, Panel::Red_Channel3_Gate3_Status1, Panel::Red_Channel2_Gate2_Status1, Panel::Red_Channel1_Gate1_Status1});

   for (uint8_t index = 0; index < 8; index++)
   {
      lightMeterListCV[index]->setMaxValue(15);
      lightMeterListCV[0]->setMeter(bpm);
      lightMeterListSlider[index]->setMaxValue(127);
   }
}

VCMCReceiver::~VCMCReceiver()
{
}

void VCMCReceiver::process(const ProcessArgs& args)
{
   if (bpm > 0 && downTrigger.process(params[Panel::TestDown].getValue()))
   {
      bpm -= 1;
      lightMeterListCV[0]->setMeter(bpm);
   }

   if (bpm < 15 && upTrigger.process(params[Panel::TestUp].getValue()))
   {
      bpm += 1;
      lightMeterListCV[0]->setMeter(bpm);
   }
}

VCMCReceiverWidget::VCMCReceiverWidget(VCMCReceiver* module)
   : ModuleWidget()
{
   SvgPanel* mainPanel = setup(module);
   (void)mainPanel;

   SchweineSystem::LCDDisplay* bpmDisplay = new SchweineSystem::LCDDisplay();
   bpmDisplay->setPosition(90, 297);
   if (module)
      bpmDisplay->setup(&(module->bpm), 3);
   bpmDisplay->setDigitColor(SchweineSystem::Color{0, 255, 255});

   addChild(bpmDisplay);
}

Model* modelVCMCReceiver = SchweineSystem::Master::the()->addModule<VCMCReceiver, VCMCReceiverWidget>("VCMCReceiver");

