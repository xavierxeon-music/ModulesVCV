#include "TimeLord.h"
#include "TimeLordPanel.h"

#include <SchweineSystemMaster.h>
#include <SchweineSystemLCDDisplay.h>
#include <limits>

void TimeLord::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configParam(Panel::Value_Bank_Display, 0.f, 10, 0.f, "");
   configParam(Panel::Value_Channel8_Display, 0.f, 1000, 0.f, "");
   configParam(Panel::Value_Channel7_Display, 0.f, 1000, 0.f, "");
   configParam(Panel::Value_Channel6_Display, 0.f, 1000, 0.f, "");
   configParam(Panel::Value_Channel5_Display, 0.f, 1000, 0.f, "");
   configParam(Panel::Value_Channel4_Display, 0.f, 1000, 0.f, "");
   configParam(Panel::Value_Channel3_Display, 0.f, 1000, 0.f, "");
   configParam(Panel::Value_Channel2_Display, 0.f, 1000, 0.f, "");
   configParam(Panel::Value_Channel1_Display, 0.f, 1000, 0.f, "");

   configButton(Panel::Mode, "Mode");
   configButton(Panel::Bank_Up, "Bank_Up");

   configParam(Panel::Knob_Turn, -1.f, 1.f, 0.f, "");

   configInput(Panel::Reset, "Reset");
   configInput(Panel::Clock, "Clock");

   configOutput(Panel::Channel8_Output, "Channel8_Output");
   configOutput(Panel::Channel7_Output, "Channel7_Output");
   configOutput(Panel::Channel6_Output, "Channel6_Output");
   configOutput(Panel::Channel5_Output, "Channel5_Output");
   configOutput(Panel::Channel4_Output, "Channel4_Output");
   configOutput(Panel::Channel3_Output, "Channel3_Output");
   configOutput(Panel::Channel2_Output, "Channel2_Output");
   configOutput(Panel::Channel1_Output, "Channel1_Output");
}

SvgPanel* TimeLordWidget::setup(TimeLord* module)
{
   setModule(module);
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/TimeLord.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(38.700342668, 247.47255081), module, TimeLord::Panel::Mode, TimeLord::Panel::Red_Mode));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(38.227227668, 117.31075081), module, TimeLord::Panel::Bank_Up, TimeLord::Panel::Red_Bank_Up));

   addParam(createParamCentered<RoundSmallBlackKnob>(Vec(71.033602668, 183.21775080999998), module, TimeLord::Panel::Knob_Turn));

   addInput(createInputCentered<PJ301MPort>(Vec(38.691244858000005, 344.74015081), module, TimeLord::Panel::Reset));
   addInput(createInputCentered<PJ301MPort>(Vec(38.691144858, 298.64460081), module, TimeLord::Panel::Clock));

   addOutput(createOutputCentered<PJ301MPort>(Vec(155.00044485799998, 344.44875081), module, TimeLord::Panel::Channel8_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(155.00044485799998, 298.69475080999996), module, TimeLord::Panel::Channel7_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(155.00044485799998, 252.94105080999998), module, TimeLord::Panel::Channel6_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(155.00044485799998, 207.18745080999997), module, TimeLord::Panel::Channel5_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(155.00044485799998, 161.43375081), module, TimeLord::Panel::Channel4_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(155.00044485799998, 115.68015080999999), module, TimeLord::Panel::Channel3_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(155.00044485799998, 69.92675080999999), module, TimeLord::Panel::Channel2_Output));
   addOutput(createOutputCentered<PJ301MPort>(Vec(155.00044485799998, 24.172750809999968), module, TimeLord::Panel::Channel1_Output));

   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(39.147365, 225.19129999999998), module, TimeLord::Panel::Red_Current));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(39.147365, 201.58139999999997), module, TimeLord::Panel::Red_Count));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(38.98576, 177.46149999999997), module, TimeLord::Panel::Red_Length));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(38.98575999999998, 153.34159999999997), module, TimeLord::Panel::Red_Division));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(166.17974458249995, 366.1809999999999), module, TimeLord::Panel::Red_Channel8_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(156.76724458250004, 366.1809999999999), module, TimeLord::Panel::Red_Channel8_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(147.35399458249998, 366.1809999999999), module, TimeLord::Panel::Red_Channel8_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(137.94074458249997, 366.1809999999999), module, TimeLord::Panel::Red_Channel8_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(128.52749458249997, 366.1809999999999), module, TimeLord::Panel::Red_Channel8_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(166.17974458249995, 320.42699999999996), module, TimeLord::Panel::Red_Channel7_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(156.76724458250004, 320.42699999999996), module, TimeLord::Panel::Red_Channel7_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(147.35399458249998, 320.42699999999996), module, TimeLord::Panel::Red_Channel7_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(137.94074458249997, 320.42699999999996), module, TimeLord::Panel::Red_Channel7_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(128.52749458249997, 320.42699999999996), module, TimeLord::Panel::Red_Channel7_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(166.17974458249995, 274.6732999999999), module, TimeLord::Panel::Red_Channel6_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(156.76724458250004, 274.6732999999999), module, TimeLord::Panel::Red_Channel6_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(147.35399458249998, 274.6732999999999), module, TimeLord::Panel::Red_Channel6_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(137.94074458249997, 274.6732999999999), module, TimeLord::Panel::Red_Channel6_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(128.52749458249997, 274.6732999999999), module, TimeLord::Panel::Red_Channel6_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(166.17974458249995, 228.91969999999995), module, TimeLord::Panel::Red_Channel5_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(156.76724458250004, 228.91969999999995), module, TimeLord::Panel::Red_Channel5_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(147.35399458249998, 228.91969999999995), module, TimeLord::Panel::Red_Channel5_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(137.94074458249997, 228.91969999999995), module, TimeLord::Panel::Red_Channel5_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(128.52749458249997, 228.91969999999995), module, TimeLord::Panel::Red_Channel5_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(166.17974458249995, 183.16599999999997), module, TimeLord::Panel::Red_Channel4_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(156.76724458250004, 183.16599999999997), module, TimeLord::Panel::Red_Channel4_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(147.35399458249998, 183.16599999999997), module, TimeLord::Panel::Red_Channel4_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(137.94074458249997, 183.16599999999997), module, TimeLord::Panel::Red_Channel4_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(128.52749458249997, 183.16599999999997), module, TimeLord::Panel::Red_Channel4_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(166.17974458249995, 137.41239999999996), module, TimeLord::Panel::Red_Channel3_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(156.76724458250004, 137.41239999999996), module, TimeLord::Panel::Red_Channel3_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(147.35399458249998, 137.41239999999996), module, TimeLord::Panel::Red_Channel3_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(137.94074458249997, 137.41239999999996), module, TimeLord::Panel::Red_Channel3_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(128.52749458249997, 137.41239999999996), module, TimeLord::Panel::Red_Channel3_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(166.17974458249995, 91.65899999999996), module, TimeLord::Panel::Red_Channel2_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(156.76724458250004, 91.65899999999996), module, TimeLord::Panel::Red_Channel2_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(147.35399458249998, 91.65899999999996), module, TimeLord::Panel::Red_Channel2_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(137.94074458249997, 91.65899999999996), module, TimeLord::Panel::Red_Channel2_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(128.52749458249997, 91.65899999999996), module, TimeLord::Panel::Red_Channel2_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(166.17974458249995, 45.904999999999944), module, TimeLord::Panel::Red_Channel1_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(156.76724458250004, 45.904999999999944), module, TimeLord::Panel::Red_Channel1_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(147.35399458249998, 45.904999999999944), module, TimeLord::Panel::Red_Channel1_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(137.94074458249997, 45.904999999999944), module, TimeLord::Panel::Red_Channel1_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(128.52749458249997, 45.904999999999944), module, TimeLord::Panel::Red_Channel1_Status1));
   addChild(createLightCentered<SmallLight<RedGreenBlueLight>>(Vec(13.898535520000001, 366.572515207), module, TimeLord::Panel::Red_Segment1_Strip));
   addChild(createLightCentered<SmallLight<RedGreenBlueLight>>(Vec(19.898535520000003, 366.572515207), module, TimeLord::Panel::Red_Segment2_Strip));
   addChild(createLightCentered<SmallLight<RedGreenBlueLight>>(Vec(25.898535520000003, 366.572515207), module, TimeLord::Panel::Red_Segment3_Strip));
   addChild(createLightCentered<SmallLight<RedGreenBlueLight>>(Vec(31.898535520000003, 366.572515207), module, TimeLord::Panel::Red_Segment4_Strip));
   addChild(createLightCentered<SmallLight<RedGreenBlueLight>>(Vec(37.89853552, 366.572515207), module, TimeLord::Panel::Red_Segment5_Strip));

   addChild(new SchweineSystem::LCDDisplay::Widget(Vec(29.227170487999995, 79.7880156), module, 1, TimeLord::Panel::Value_Bank_Display, TimeLord::Panel::Red_Bank_Display));
   addChild(new SchweineSystem::LCDDisplay::Widget(Vec(86.99789936, 332.8730156), module, 3, TimeLord::Panel::Value_Channel8_Display, TimeLord::Panel::Red_Channel8_Display));
   addChild(new SchweineSystem::LCDDisplay::Widget(Vec(86.99789936, 287.1190156), module, 3, TimeLord::Panel::Value_Channel7_Display, TimeLord::Panel::Red_Channel7_Display));
   addChild(new SchweineSystem::LCDDisplay::Widget(Vec(86.99789936, 241.36531559999997), module, 3, TimeLord::Panel::Value_Channel6_Display, TimeLord::Panel::Red_Channel6_Display));
   addChild(new SchweineSystem::LCDDisplay::Widget(Vec(86.99789936, 195.61171559999997), module, 3, TimeLord::Panel::Value_Channel5_Display, TimeLord::Panel::Red_Channel5_Display));
   addChild(new SchweineSystem::LCDDisplay::Widget(Vec(86.99789936, 149.8580156), module, 3, TimeLord::Panel::Value_Channel4_Display, TimeLord::Panel::Red_Channel4_Display));
   addChild(new SchweineSystem::LCDDisplay::Widget(Vec(86.99789936, 104.10441559999998), module, 3, TimeLord::Panel::Value_Channel3_Display, TimeLord::Panel::Red_Channel3_Display));
   addChild(new SchweineSystem::LCDDisplay::Widget(Vec(86.99789936, 58.35101559999998), module, 3, TimeLord::Panel::Value_Channel2_Display, TimeLord::Panel::Red_Channel2_Display));
   addChild(new SchweineSystem::LCDDisplay::Widget(Vec(86.99789936, 12.597015599999963), module, 3, TimeLord::Panel::Value_Channel1_Display, TimeLord::Panel::Red_Channel1_Display));

   return mainPanel;
}

