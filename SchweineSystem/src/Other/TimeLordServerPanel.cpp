#include "TimeLordServer.h"
#include "TimeLordServerPanel.h"

#include "SchweineSystemMaster.h"

void TimeLordServer::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configInput(Panel::Reset, "Reset");
   configInput(Panel::Clock, "Clock");

   configOutput(Panel::Channel16_Output, "Channel16_Output");
   configOutput(Panel::Channel8_Output, "Channel8_Output");
   configOutput(Panel::Channel15_Output, "Channel15_Output");
   configOutput(Panel::Channel7_Output, "Channel7_Output");
   configOutput(Panel::Channel14_Output, "Channel14_Output");
   configOutput(Panel::Channel6_Output, "Channel6_Output");
   configOutput(Panel::Channel13_Output, "Channel13_Output");
   configOutput(Panel::Channel5_Output, "Channel5_Output");
   configOutput(Panel::Channel12_Output, "Channel12_Output");
   configOutput(Panel::Channel4_Output, "Channel4_Output");
   configOutput(Panel::Channel11_Output, "Channel11_Output");
   configOutput(Panel::Channel3_Output, "Channel3_Output");
   configOutput(Panel::Channel10_Output, "Channel10_Output");
   configOutput(Panel::Channel2_Output, "Channel2_Output");
   configOutput(Panel::Channel9_Output, "Channel9_Output");
   configOutput(Panel::Channel1_Output, "Channel1_Output");

}

SvgPanel* TimeLordServerWidget::setup(TimeLordServer* module)
{
   setModule(module);
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/TimeLordServer.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   addInput(createInputCentered<PJ301MPort>(Vec(38.691244858000005, 344.74015081), module, TimeLordServer::Panel::Reset));
   addInput(createInputCentered<PJ301MPort>(Vec(38.691144858, 298.64460081), module, TimeLordServer::Panel::Clock));

   addOutput(createOutputCentered<PJ301MPort>(Vec(155.00044485799998, 344.44875081), module, TimeLordServer::Panel::Channel16_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(97.646744858, 344.44875081), module, TimeLordServer::Panel::Channel8_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(155.00044485799998, 298.69475080999996), module, TimeLordServer::Panel::Channel15_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(97.646744858, 298.69475080999996), module, TimeLordServer::Panel::Channel7_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(155.00044485799998, 252.94075081), module, TimeLordServer::Panel::Channel14_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(97.646744858, 252.94075081), module, TimeLordServer::Panel::Channel6_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(155.00044485799998, 207.18775080999998), module, TimeLordServer::Panel::Channel13_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(97.646744858, 207.18775080999998), module, TimeLordServer::Panel::Channel5_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(155.00044485799998, 161.43375081), module, TimeLordServer::Panel::Channel12_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(97.646744858, 161.43375081), module, TimeLordServer::Panel::Channel4_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(155.00044485799998, 115.68025080999999), module, TimeLordServer::Panel::Channel11_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(97.646744858, 115.68025080999999), module, TimeLordServer::Panel::Channel3_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(155.00044485799998, 69.92655080999998), module, TimeLordServer::Panel::Channel10_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(97.646744858, 69.92655080999998), module, TimeLordServer::Panel::Channel2_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(155.00044485799998, 24.172950809999985), module, TimeLordServer::Panel::Channel9_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(97.646744858, 24.172950809999985), module, TimeLordServer::Panel::Channel1_Output));

   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(42.80461630561056, 117.88366537652172), module, TimeLordServer::Panel::Red_LoadB));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(34.579328342410555, 117.88366537652172), module, TimeLordServer::Panel::Red_LoadA));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(166.17974458249995, 366.181), module, TimeLordServer::Panel::Red_Channel16_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(156.76724458250004, 366.181), module, TimeLordServer::Panel::Red_Channel16_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(147.35399458249998, 366.181), module, TimeLordServer::Panel::Red_Channel16_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(137.94074458249997, 366.181), module, TimeLordServer::Panel::Red_Channel16_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(128.52749458249997, 366.181), module, TimeLordServer::Panel::Red_Channel16_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(108.82604458249995, 366.181), module, TimeLordServer::Panel::Red_Channel8_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(99.41354458250004, 366.181), module, TimeLordServer::Panel::Red_Channel8_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(90.00029458249998, 366.181), module, TimeLordServer::Panel::Red_Channel8_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(80.58704458249997, 366.181), module, TimeLordServer::Panel::Red_Channel8_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(71.17379458249997, 366.181), module, TimeLordServer::Panel::Red_Channel8_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(166.17974458249995, 320.42699999999996), module, TimeLordServer::Panel::Red_Channel15_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(156.76724458250004, 320.42699999999996), module, TimeLordServer::Panel::Red_Channel15_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(147.35399458249998, 320.42699999999996), module, TimeLordServer::Panel::Red_Channel15_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(137.94074458249997, 320.42699999999996), module, TimeLordServer::Panel::Red_Channel15_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(128.52749458249997, 320.42699999999996), module, TimeLordServer::Panel::Red_Channel15_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(108.82604458249995, 320.42699999999996), module, TimeLordServer::Panel::Red_Channel7_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(99.41354458250004, 320.42699999999996), module, TimeLordServer::Panel::Red_Channel7_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(90.00029458249998, 320.42699999999996), module, TimeLordServer::Panel::Red_Channel7_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(80.58704458249997, 320.42699999999996), module, TimeLordServer::Panel::Red_Channel7_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(71.17379458249997, 320.42699999999996), module, TimeLordServer::Panel::Red_Channel7_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(166.17974458249995, 274.673), module, TimeLordServer::Panel::Red_Channel14_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(156.76724458250004, 274.673), module, TimeLordServer::Panel::Red_Channel14_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(147.35399458249998, 274.673), module, TimeLordServer::Panel::Red_Channel14_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(137.94074458249997, 274.673), module, TimeLordServer::Panel::Red_Channel14_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(128.52749458249997, 274.673), module, TimeLordServer::Panel::Red_Channel14_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(108.82604458249995, 274.673), module, TimeLordServer::Panel::Red_Channel6_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(99.41354458250004, 274.673), module, TimeLordServer::Panel::Red_Channel6_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(90.00029458249998, 274.673), module, TimeLordServer::Panel::Red_Channel6_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(80.58704458249997, 274.673), module, TimeLordServer::Panel::Red_Channel6_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(71.17379458249997, 274.673), module, TimeLordServer::Panel::Red_Channel6_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(166.17974458249995, 228.91999999999996), module, TimeLordServer::Panel::Red_Channel13_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(156.76724458250004, 228.91999999999996), module, TimeLordServer::Panel::Red_Channel13_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(147.35399458249998, 228.91999999999996), module, TimeLordServer::Panel::Red_Channel13_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(137.94074458249997, 228.91999999999996), module, TimeLordServer::Panel::Red_Channel13_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(128.52749458249997, 228.91999999999996), module, TimeLordServer::Panel::Red_Channel13_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(108.82604458249995, 228.91999999999996), module, TimeLordServer::Panel::Red_Channel5_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(99.41354458250004, 228.91999999999996), module, TimeLordServer::Panel::Red_Channel5_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(90.00029458249998, 228.91999999999996), module, TimeLordServer::Panel::Red_Channel5_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(80.58704458249997, 228.91999999999996), module, TimeLordServer::Panel::Red_Channel5_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(71.17379458249997, 228.91999999999996), module, TimeLordServer::Panel::Red_Channel5_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(166.17974458249995, 183.16599999999997), module, TimeLordServer::Panel::Red_Channel12_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(156.76724458250004, 183.16599999999997), module, TimeLordServer::Panel::Red_Channel12_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(147.35399458249998, 183.16599999999997), module, TimeLordServer::Panel::Red_Channel12_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(137.94074458249997, 183.16599999999997), module, TimeLordServer::Panel::Red_Channel12_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(128.52749458249997, 183.16599999999997), module, TimeLordServer::Panel::Red_Channel12_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(108.82604458249995, 183.16599999999997), module, TimeLordServer::Panel::Red_Channel4_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(99.41354458250004, 183.16599999999997), module, TimeLordServer::Panel::Red_Channel4_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(90.00029458249998, 183.16599999999997), module, TimeLordServer::Panel::Red_Channel4_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(80.58704458249997, 183.16599999999997), module, TimeLordServer::Panel::Red_Channel4_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(71.17379458249997, 183.16599999999997), module, TimeLordServer::Panel::Red_Channel4_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(166.17974458249995, 137.41249999999997), module, TimeLordServer::Panel::Red_Channel11_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(156.76724458250004, 137.41249999999997), module, TimeLordServer::Panel::Red_Channel11_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(147.35399458249998, 137.41249999999997), module, TimeLordServer::Panel::Red_Channel11_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(137.94074458249997, 137.41249999999997), module, TimeLordServer::Panel::Red_Channel11_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(128.52749458249997, 137.41249999999997), module, TimeLordServer::Panel::Red_Channel11_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(108.82604458249995, 137.41249999999997), module, TimeLordServer::Panel::Red_Channel3_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(99.41354458250004, 137.41249999999997), module, TimeLordServer::Panel::Red_Channel3_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(90.00029458249998, 137.41249999999997), module, TimeLordServer::Panel::Red_Channel3_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(80.58704458249997, 137.41249999999997), module, TimeLordServer::Panel::Red_Channel3_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(71.17379458249997, 137.41249999999997), module, TimeLordServer::Panel::Red_Channel3_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(166.17974458249995, 91.65879999999996), module, TimeLordServer::Panel::Red_Channel10_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(156.76724458250004, 91.65879999999996), module, TimeLordServer::Panel::Red_Channel10_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(147.35399458249998, 91.65879999999996), module, TimeLordServer::Panel::Red_Channel10_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(137.94074458249997, 91.65879999999996), module, TimeLordServer::Panel::Red_Channel10_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(128.52749458249997, 91.65879999999996), module, TimeLordServer::Panel::Red_Channel10_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(108.82604458249995, 91.65879999999996), module, TimeLordServer::Panel::Red_Channel2_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(99.41354458250004, 91.65879999999996), module, TimeLordServer::Panel::Red_Channel2_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(90.00029458249998, 91.65879999999996), module, TimeLordServer::Panel::Red_Channel2_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(80.58704458249997, 91.65879999999996), module, TimeLordServer::Panel::Red_Channel2_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(71.17379458249997, 91.65879999999996), module, TimeLordServer::Panel::Red_Channel2_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(166.17974458249995, 45.905199999999965), module, TimeLordServer::Panel::Red_Channel9_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(156.76724458250004, 45.905199999999965), module, TimeLordServer::Panel::Red_Channel9_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(147.35399458249998, 45.905199999999965), module, TimeLordServer::Panel::Red_Channel9_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(137.94074458249997, 45.905199999999965), module, TimeLordServer::Panel::Red_Channel9_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(128.52749458249997, 45.905199999999965), module, TimeLordServer::Panel::Red_Channel9_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(108.82604458249995, 45.905199999999965), module, TimeLordServer::Panel::Red_Channel1_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(99.41354458250004, 45.905199999999965), module, TimeLordServer::Panel::Red_Channel1_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(90.00029458249998, 45.905199999999965), module, TimeLordServer::Panel::Red_Channel1_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(80.58704458249997, 45.905199999999965), module, TimeLordServer::Panel::Red_Channel1_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(71.17379458249997, 45.905199999999965), module, TimeLordServer::Panel::Red_Channel1_Status1));

   return mainPanel;
}

