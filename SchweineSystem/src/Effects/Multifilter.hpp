#ifndef MultifilterHPP
#define MultifilterHPP

#include "Multifilter.h"

#include <SvinOrigin.h>

struct Multifilter::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      Quantize = 0,
      // knobs
      Offset = 1,
      Drive = 2,
      DriveAttenuate = 3,
      Reso = 4,
      ResoAttenuator = 5,
      // sliders
      Mode = 6,
      PARAMS_LEN = 7
   };

   enum DisplayId
   {
      // lcd
      // oled
      DISPLAYS_LEN = 0
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      In = 0,
      Pitch = 1,
      OffsetOverride = 2,
      DriveModulate = 3,
      ResoModulate = 4,
      INPUTS_LEN = 5
   };

   enum OutputId
   {
      Out = 0,
      OUTPUTS_LEN = 1
   };

   enum LightId
   {
      // leds
      // ledbuttons
      RGB_Quantize = 0,
      // sliders
      RGB_Mode = 3,
      LIGHTS_LEN = 6
   };

};

void Multifilter::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configSwitch(Panel::Mode, 0.0f, 1.0f, 0.0f, "Mode");

   configButton(Panel::Quantize, "Quantize");

   configParam(Panel::Offset, -1.f, 1.f, 0.f, "Offset");
   configParam(Panel::Drive, -1.f, 1.f, 0.f, "Drive");
   configParam(Panel::DriveAttenuate, -1.f, 1.f, 0.f, "DriveAttenuate");
   configParam(Panel::Reso, -1.f, 1.f, 0.f, "Reso");
   configParam(Panel::ResoAttenuator, -1.f, 1.f, 0.f, "ResoAttenuator");

   configInput(Panel::In, "In");
   configInput(Panel::Pitch, "Pitch");
   configInput(Panel::OffsetOverride, "OffsetOverride");
   configInput(Panel::DriveModulate, "DriveModulate");
   configInput(Panel::ResoModulate, "ResoModulate");

   configOutput(Panel::Out, "Out");
}

void MultifilterWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/Effects/Multifilter.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeSlider(this, Vec(107.14, 330.00), Multifilter::Panel::Mode, Multifilter::Panel::RGB_Mode);

   makeLEDButton(this, Vec(121.03, 257.54), Multifilter::Panel::Quantize, Multifilter::Panel::RGB_Quantize);

   makeKnob(this, Vec(107.14, 222.36), Multifilter::Panel::Offset, 3);
   makeKnob(this, Vec(107.14, 149.09), Multifilter::Panel::Drive, 4);
   makeKnob(this, Vec(52.60, 167.94), Multifilter::Panel::DriveAttenuate, 1);
   makeKnob(this, Vec(107.14, 75.82), Multifilter::Panel::Reso, 5);
   makeKnob(this, Vec(52.60, 94.66), Multifilter::Panel::ResoAttenuator, 1);

   makeInput(this, Vec(51.09, 318.30),  Multifilter::Panel::In, true);
   makeInput(this, Vec(51.09, 259.34),  Multifilter::Panel::Pitch, true);
   makeInput(this, Vec(50.97, 222.36),  Multifilter::Panel::OffsetOverride, false);
   makeInput(this, Vec(52.60, 141.44),  Multifilter::Panel::DriveModulate, false);
   makeInput(this, Vec(52.60, 68.12),  Multifilter::Panel::ResoModulate, false);

   makeOutput(this, Vec(51.09, 355.83), Multifilter::Panel::Out, true);
}

Model* modelMultifilter = Svin::Origin::the()->addModule<Multifilter, MultifilterWidget>("Multifilter");

#endif // NOT MultifilterHPP
