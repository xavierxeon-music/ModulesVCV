#include "VCMCReceiver.h"
#include "VCMCReceiverPanel.h"

#include "SchweineSystemMaster.h"

void VCMCReceiver::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::TestDown, "TestDown");
   configButton(Panel::TestUp, "TestUp");

   configOutput(Panel::Reset, "Reset");
   configOutput(Panel::Clock, "Clock");
   configOutput(Panel::Channel8_Gate8_BitOut1, "Channel8_Gate8_BitOut1");
   configOutput(Panel::Channel8_Slider8_Output, "Channel8_Slider8_Output");
   configOutput(Panel::Channel8_CV8_Output, "Channel8_CV8_Output");
   configOutput(Panel::Channel7_Gate7_BitOut1, "Channel7_Gate7_BitOut1");
   configOutput(Panel::Channel7_Slider7_Output, "Channel7_Slider7_Output");
   configOutput(Panel::Channel7_CV7_Output, "Channel7_CV7_Output");
   configOutput(Panel::Channel6_Gate6_BitOut1, "Channel6_Gate6_BitOut1");
   configOutput(Panel::Channel6_Slider6_Output, "Channel6_Slider6_Output");
   configOutput(Panel::Channel6_CV6_Output, "Channel6_CV6_Output");
   configOutput(Panel::Channel5_Gate5_BitOut1, "Channel5_Gate5_BitOut1");
   configOutput(Panel::Channel5_Slider5_Output, "Channel5_Slider5_Output");
   configOutput(Panel::Channel5_CV5_Output, "Channel5_CV5_Output");
   configOutput(Panel::Channel4_Gate4_BitOut1, "Channel4_Gate4_BitOut1");
   configOutput(Panel::Channel4_Slider4_Output, "Channel4_Slider4_Output");
   configOutput(Panel::Channel4_CV4_Output, "Channel4_CV4_Output");
   configOutput(Panel::Channel3_Gate3_BitOut1, "Channel3_Gate3_BitOut1");
   configOutput(Panel::Channel3_Slider3_Output, "Channel3_Slider3_Output");
   configOutput(Panel::Channel3_CV3_Output, "Channel3_CV3_Output");
   configOutput(Panel::Channel2_Gate2_BitOut1, "Channel2_Gate2_BitOut1");
   configOutput(Panel::Channel2_Slider2_Output, "Channel2_Slider2_Output");
   configOutput(Panel::Channel2_CV2_Output, "Channel2_CV2_Output");
   configOutput(Panel::Channel1_Gate1_BitOut1, "Channel1_Gate1_BitOut1");
   configOutput(Panel::Channel1_Slider1_Output, "Channel1_Slider1_Output");
   configOutput(Panel::Channel1_CV1_Output, "Channel1_CV1_Output");

}

SvgPanel* VCMCReceiverWidget::setup(VCMCReceiver* module)
{
   setModule(module);
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/VCMCReceiver.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(157.740002668, 306.41075080999997), module, VCMCReceiver::Panel::TestDown, VCMCReceiver::Panel::Red_TestDown));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(187.403002668, 306.41075080999997), module, VCMCReceiver::Panel::TestUp, VCMCReceiver::Panel::Red_TestUp));

   addOutput(createOutputCentered<PJ301MPort>(Vec(60.162144858000005, 345.37097080999996), module, VCMCReceiver::Panel::Reset));
   addOutput(createOutputCentered<PJ301MPort>(Vec(60.162144858000005, 306.51897081), module, VCMCReceiver::Panel::Clock));
   addOutput(createOutputCentered<PJ301MPort>(Vec(39.43334485800001, 262.57647381000004), module, VCMCReceiver::Panel::Channel8_Gate8_BitOut1));
   addOutput(createOutputCentered<PJ301MPort>(Vec(125.94934485800003, 263.16915081), module, VCMCReceiver::Panel::Channel8_Slider8_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(86.960594858, 263.16915081), module, VCMCReceiver::Panel::Channel8_CV8_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(39.43334485800001, 230.13657381000002), module, VCMCReceiver::Panel::Channel7_Gate7_BitOut1));
   addOutput(createOutputCentered<PJ301MPort>(Vec(125.94934485800003, 230.72925081), module, VCMCReceiver::Panel::Channel7_Slider7_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(86.960594858, 230.72925081), module, VCMCReceiver::Panel::Channel7_CV7_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(39.43334485800001, 197.69671381000003), module, VCMCReceiver::Panel::Channel6_Gate6_BitOut1));
   addOutput(createOutputCentered<PJ301MPort>(Vec(125.94934485800003, 198.28939081000001), module, VCMCReceiver::Panel::Channel6_Slider6_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(86.960594858, 198.28939081000001), module, VCMCReceiver::Panel::Channel6_CV6_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(39.43334485800001, 165.25687381000003), module, VCMCReceiver::Panel::Channel5_Gate5_BitOut1));
   addOutput(createOutputCentered<PJ301MPort>(Vec(125.94934485800003, 165.84955081), module, VCMCReceiver::Panel::Channel5_Slider5_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(86.960594858, 165.84955081), module, VCMCReceiver::Panel::Channel5_CV5_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(39.43334485800001, 132.81697381000004), module, VCMCReceiver::Panel::Channel4_Gate4_BitOut1));
   addOutput(createOutputCentered<PJ301MPort>(Vec(125.94934485800003, 133.40965081000002), module, VCMCReceiver::Panel::Channel4_Slider4_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(86.960594858, 133.40965081000002), module, VCMCReceiver::Panel::Channel4_CV4_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(39.43334485800001, 100.37707381000003), module, VCMCReceiver::Panel::Channel3_Gate3_BitOut1));
   addOutput(createOutputCentered<PJ301MPort>(Vec(125.94934485800003, 100.96975081000001), module, VCMCReceiver::Panel::Channel3_Slider3_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(86.960594858, 100.96975081000001), module, VCMCReceiver::Panel::Channel3_CV3_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(39.43334485800001, 67.93757381000002), module, VCMCReceiver::Panel::Channel2_Gate2_BitOut1));
   addOutput(createOutputCentered<PJ301MPort>(Vec(125.94934485800003, 68.53025081), module, VCMCReceiver::Panel::Channel2_Slider2_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(86.960594858, 68.53025081), module, VCMCReceiver::Panel::Channel2_CV2_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(39.43334485800001, 35.497573810000034), module, VCMCReceiver::Panel::Channel1_Gate1_BitOut1));
   addOutput(createOutputCentered<PJ301MPort>(Vec(125.94934485800003, 36.090250810000015), module, VCMCReceiver::Panel::Channel1_Slider1_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(86.960594858, 36.090250810000015), module, VCMCReceiver::Panel::Channel1_CV1_Output));

   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(187.404, 344.60186999999996), module, VCMCReceiver::Panel::Red_Connection2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(179.387, 344.60186999999996), module, VCMCReceiver::Panel::Red_Connection1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(63.61860000000003, 262.576723), module, VCMCReceiver::Panel::Red_Channel8_Gate8_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(188.36114458249995, 269.0929), module, VCMCReceiver::Panel::Red_Channel8_Slider8_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(178.94864458250004, 269.0929), module, VCMCReceiver::Panel::Red_Channel8_Slider8_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(169.53539458249998, 269.0929), module, VCMCReceiver::Panel::Red_Channel8_Slider8_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(160.12214458249997, 269.0929), module, VCMCReceiver::Panel::Red_Channel8_Slider8_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(150.70889458249997, 269.0929), module, VCMCReceiver::Panel::Red_Channel8_Slider8_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(188.36114458249995, 256.65389999999996), module, VCMCReceiver::Panel::Red_Channel8_CV8_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(178.94864458250004, 256.65389999999996), module, VCMCReceiver::Panel::Red_Channel8_CV8_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(169.53539458249998, 256.65389999999996), module, VCMCReceiver::Panel::Red_Channel8_CV8_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(160.12214458249997, 256.65389999999996), module, VCMCReceiver::Panel::Red_Channel8_CV8_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(150.70889458249997, 256.65389999999996), module, VCMCReceiver::Panel::Red_Channel8_CV8_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(63.61860000000003, 230.136823), module, VCMCReceiver::Panel::Red_Channel7_Gate7_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(188.36114458249995, 236.653), module, VCMCReceiver::Panel::Red_Channel7_Slider7_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(178.94864458250004, 236.653), module, VCMCReceiver::Panel::Red_Channel7_Slider7_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(169.53539458249998, 236.653), module, VCMCReceiver::Panel::Red_Channel7_Slider7_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(160.12214458249997, 236.653), module, VCMCReceiver::Panel::Red_Channel7_Slider7_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(150.70889458249997, 236.653), module, VCMCReceiver::Panel::Red_Channel7_Slider7_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(188.36114458249995, 224.21399999999997), module, VCMCReceiver::Panel::Red_Channel7_CV7_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(178.94864458250004, 224.21399999999997), module, VCMCReceiver::Panel::Red_Channel7_CV7_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(169.53539458249998, 224.21399999999997), module, VCMCReceiver::Panel::Red_Channel7_CV7_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(160.12214458249997, 224.21399999999997), module, VCMCReceiver::Panel::Red_Channel7_CV7_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(150.70889458249997, 224.21399999999997), module, VCMCReceiver::Panel::Red_Channel7_CV7_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(63.61860000000003, 197.696963), module, VCMCReceiver::Panel::Red_Channel6_Gate6_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(188.36114458249995, 204.21314), module, VCMCReceiver::Panel::Red_Channel6_Slider6_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(178.94864458250004, 204.21314), module, VCMCReceiver::Panel::Red_Channel6_Slider6_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(169.53539458249998, 204.21314), module, VCMCReceiver::Panel::Red_Channel6_Slider6_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(160.12214458249997, 204.21314), module, VCMCReceiver::Panel::Red_Channel6_Slider6_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(150.70889458249997, 204.21314), module, VCMCReceiver::Panel::Red_Channel6_Slider6_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(188.36114458249995, 191.77414), module, VCMCReceiver::Panel::Red_Channel6_CV6_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(178.94864458250004, 191.77414), module, VCMCReceiver::Panel::Red_Channel6_CV6_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(169.53539458249998, 191.77414), module, VCMCReceiver::Panel::Red_Channel6_CV6_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(160.12214458249997, 191.77414), module, VCMCReceiver::Panel::Red_Channel6_CV6_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(150.70889458249997, 191.77414), module, VCMCReceiver::Panel::Red_Channel6_CV6_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(63.61860000000003, 165.257123), module, VCMCReceiver::Panel::Red_Channel5_Gate5_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(188.36114458249995, 171.7733), module, VCMCReceiver::Panel::Red_Channel5_Slider5_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(178.94864458250004, 171.7733), module, VCMCReceiver::Panel::Red_Channel5_Slider5_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(169.53539458249998, 171.7733), module, VCMCReceiver::Panel::Red_Channel5_Slider5_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(160.12214458249997, 171.7733), module, VCMCReceiver::Panel::Red_Channel5_Slider5_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(150.70889458249997, 171.7733), module, VCMCReceiver::Panel::Red_Channel5_Slider5_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(188.36114458249995, 159.33429999999998), module, VCMCReceiver::Panel::Red_Channel5_CV5_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(178.94864458250004, 159.33429999999998), module, VCMCReceiver::Panel::Red_Channel5_CV5_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(169.53539458249998, 159.33429999999998), module, VCMCReceiver::Panel::Red_Channel5_CV5_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(160.12214458249997, 159.33429999999998), module, VCMCReceiver::Panel::Red_Channel5_CV5_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(150.70889458249997, 159.33429999999998), module, VCMCReceiver::Panel::Red_Channel5_CV5_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(63.61860000000003, 132.817223), module, VCMCReceiver::Panel::Red_Channel4_Gate4_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(188.36114458249995, 139.33339999999998), module, VCMCReceiver::Panel::Red_Channel4_Slider4_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(178.94864458250004, 139.33339999999998), module, VCMCReceiver::Panel::Red_Channel4_Slider4_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(169.53539458249998, 139.33339999999998), module, VCMCReceiver::Panel::Red_Channel4_Slider4_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(160.12214458249997, 139.33339999999998), module, VCMCReceiver::Panel::Red_Channel4_Slider4_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(150.70889458249997, 139.33339999999998), module, VCMCReceiver::Panel::Red_Channel4_Slider4_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(188.36114458249995, 126.89439999999998), module, VCMCReceiver::Panel::Red_Channel4_CV4_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(178.94864458250004, 126.89439999999998), module, VCMCReceiver::Panel::Red_Channel4_CV4_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(169.53539458249998, 126.89439999999998), module, VCMCReceiver::Panel::Red_Channel4_CV4_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(160.12214458249997, 126.89439999999998), module, VCMCReceiver::Panel::Red_Channel4_CV4_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(150.70889458249997, 126.89439999999998), module, VCMCReceiver::Panel::Red_Channel4_CV4_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(63.61860000000003, 100.377323), module, VCMCReceiver::Panel::Red_Channel3_Gate3_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(188.36114458249995, 106.8935), module, VCMCReceiver::Panel::Red_Channel3_Slider3_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(178.94864458250004, 106.8935), module, VCMCReceiver::Panel::Red_Channel3_Slider3_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(169.53539458249998, 106.8935), module, VCMCReceiver::Panel::Red_Channel3_Slider3_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(160.12214458249997, 106.8935), module, VCMCReceiver::Panel::Red_Channel3_Slider3_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(150.70889458249997, 106.8935), module, VCMCReceiver::Panel::Red_Channel3_Slider3_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(188.36114458249995, 94.45449999999998), module, VCMCReceiver::Panel::Red_Channel3_CV3_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(178.94864458250004, 94.45449999999998), module, VCMCReceiver::Panel::Red_Channel3_CV3_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(169.53539458249998, 94.45449999999998), module, VCMCReceiver::Panel::Red_Channel3_CV3_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(160.12214458249997, 94.45449999999998), module, VCMCReceiver::Panel::Red_Channel3_CV3_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(150.70889458249997, 94.45449999999998), module, VCMCReceiver::Panel::Red_Channel3_CV3_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(63.61860000000003, 67.937823), module, VCMCReceiver::Panel::Red_Channel2_Gate2_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(188.36114458249995, 74.454), module, VCMCReceiver::Panel::Red_Channel2_Slider2_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(178.94864458250004, 74.454), module, VCMCReceiver::Panel::Red_Channel2_Slider2_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(169.53539458249998, 74.454), module, VCMCReceiver::Panel::Red_Channel2_Slider2_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(160.12214458249997, 74.454), module, VCMCReceiver::Panel::Red_Channel2_Slider2_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(150.70889458249997, 74.454), module, VCMCReceiver::Panel::Red_Channel2_Slider2_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(188.36114458249995, 62.01499999999997), module, VCMCReceiver::Panel::Red_Channel2_CV2_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(178.94864458250004, 62.01499999999997), module, VCMCReceiver::Panel::Red_Channel2_CV2_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(169.53539458249998, 62.01499999999997), module, VCMCReceiver::Panel::Red_Channel2_CV2_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(160.12214458249997, 62.01499999999997), module, VCMCReceiver::Panel::Red_Channel2_CV2_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(150.70889458249997, 62.01499999999997), module, VCMCReceiver::Panel::Red_Channel2_CV2_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(63.61860000000003, 35.49782300000001), module, VCMCReceiver::Panel::Red_Channel1_Gate1_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(188.36114458249995, 42.01400000000001), module, VCMCReceiver::Panel::Red_Channel1_Slider1_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(178.94864458250004, 42.01400000000001), module, VCMCReceiver::Panel::Red_Channel1_Slider1_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(169.53539458249998, 42.01400000000001), module, VCMCReceiver::Panel::Red_Channel1_Slider1_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(160.12214458249997, 42.01400000000001), module, VCMCReceiver::Panel::Red_Channel1_Slider1_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(150.70889458249997, 42.01400000000001), module, VCMCReceiver::Panel::Red_Channel1_Slider1_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(188.36114458249995, 29.57499999999999), module, VCMCReceiver::Panel::Red_Channel1_CV1_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(178.94864458250004, 29.57499999999999), module, VCMCReceiver::Panel::Red_Channel1_CV1_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(169.53539458249998, 29.57499999999999), module, VCMCReceiver::Panel::Red_Channel1_CV1_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(160.12214458249997, 29.57499999999999), module, VCMCReceiver::Panel::Red_Channel1_CV1_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(150.70889458249997, 29.57499999999999), module, VCMCReceiver::Panel::Red_Channel1_CV1_Status1));

   return mainPanel;
}

