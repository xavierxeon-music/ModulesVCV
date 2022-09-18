#ifndef MidiReplayHPP
#define MidiReplayHPP

#include "MidiReplay.h"

#include <SvinOrigin.h>

struct MidiReplay::Panel
{
   enum ParamId
   {
      // buttons
      Page = 0,
      // switches
      // ledbuttons
      Loop = 1,
      // knobs
      // sliders
      PARAMS_LEN = 2
   };

   enum DisplayId
   {
      // lcd
      // oled
      Pixels_Display = 0,
      DISPLAYS_LEN = 1
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      Reset = 0,
      Play = 1,
      INPUTS_LEN = 2
   };

   enum OutputId
   {
      End = 0,
      OUTPUTS_LEN = 1
   };

   enum LightId
   {
      // leds
      // ledbuttons
      RGB_Loop = 0,
      // sliders
      LIGHTS_LEN = 3
   };

};

void MidiReplay::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Page, "Page");

   configButton(Panel::Loop, "Loop");

   configInput(Panel::Reset, "Reset");
   configInput(Panel::Play, "Play");

   configOutput(Panel::End, "End");
}

void MidiReplayWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/Sequencer/MidiReplay.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(69.99, 51.55), MidiReplay::Panel::Page);

   makeLEDButton(this, Vec(84.33, 261.51), MidiReplay::Panel::Loop, MidiReplay::Panel::RGB_Loop);

   makeInput(this, Vec(35.33, 309.97),  MidiReplay::Panel::Reset, false);
   makeInput(this, Vec(34.94, 262.70),  MidiReplay::Panel::Play, false);

   makeOutput(this, Vec(84.33, 309.97), MidiReplay::Panel::End, false);

   makeOLED(this, Vec(9.00, 68.57), MidiReplay::Panel::Pixels_Display, 100, 135);
}

Model* modelMidiReplay = Svin::Origin::the()->addModule<MidiReplay, MidiReplayWidget>("MidiReplay");

#endif // NOT MidiReplayHPP
