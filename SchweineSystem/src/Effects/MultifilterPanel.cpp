#include "Multifilter.h"
#include "MultifilterPanel.h"

#include <SvinOrigin.h>

void Multifilter::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configSwitch(Panel::Mode, 0.0f, 1.0f, 0.0f, "Mode");

   configButton(Panel::Quantize, "Quantize");

   configParam(Panel::Offset, -1.f, 1.f, 0.f, "Offset");
   configParam(Panel::Drive, -1.f, 1.f, 0.f, "Drive");
   configParam(Panel::Reso, -1.f, 1.f, 0.f, "Reso");

   configInput(Panel::In, "In");
   configInput(Panel::Pitch, "Pitch");
   configInput(Panel::OffsetOverride, "OffsetOverride");
   configInput(Panel::DriveOverride, "DriveOverride");
   configInput(Panel::ResoOverride, "ResoOverride");

   configOutput(Panel::Out, "Out");
}

void MultifilterWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/Effects/Multifilter.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeSlider(this, Vec(85.20, 330.00), Multifilter::Panel::Mode, Multifilter::Panel::RGB_Mode);

   makeLEDButton(this, Vec(85.09, 263.91), Multifilter::Panel::Quantize, Multifilter::Panel::RGB_Quantize);

   makeKnob(this, Vec(107.14, 227.36), Multifilter::Panel::Offset, 3);
   makeKnob(this, Vec(107.14, 145.09), Multifilter::Panel::Drive, 4);
   makeKnob(this, Vec(107.14, 75.82), Multifilter::Panel::Reso, 5);

   makeInput(this, Vec(51.09, 318.30),  Multifilter::Panel::In, true);
   makeInput(this, Vec(51.09, 264.34),  Multifilter::Panel::Pitch, true);
   makeInput(this, Vec(50.97, 227.36),  Multifilter::Panel::OffsetOverride, false);
   makeInput(this, Vec(52.60, 143.66),  Multifilter::Panel::DriveOverride, false);
   makeInput(this, Vec(52.60, 74.38),  Multifilter::Panel::ResoOverride, false);

   makeOutput(this, Vec(51.09, 355.83), Multifilter::Panel::Out, true);
}

