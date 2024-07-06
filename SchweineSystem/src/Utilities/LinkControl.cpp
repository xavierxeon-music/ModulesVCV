#include "LinkControl.h"

#include <Music/Note.h>
#include <Tools/Text.h>

#include <SvinOrigin.h>

LinkControl::LinkControl()
   : Svin::Module()
   , link(120)
   , tempoDisplay(this, Panel::Text_Tempo)
   , tempoUpHundredButton(this, Panel::Hundred_Up)
   , tempoDownHundredButton(this, Panel::Hundred_Down)
   , tempoUpTenButton(this, Panel::Ten_Up)
   , tempoDownTenButton(this, Panel::Ten_Down)
   , tempoUpOneButton(this, Panel::One_Up)
   , tempoDownOneButton(this, Panel::One_Down)
   , playButton(this, Panel::Active, Panel::RGB_Active)
   , syncMeter(this, Panel::Value_Sync)
{
   setup();

   playButton.setDefaultColor(Color::Predefined::Green);
   syncMeter.setMaxValue(25);

   link.enable(true);
   link.enableStartStopSync(true);
}

LinkControl::~LinkControl()
{
   link.enable(false);
}

void LinkControl::process(const ProcessArgs& args)
{
   bool update = false;
   ableton::Link::SessionState state = link.captureAudioSessionState();

   if (playButton.isTriggered())
   {
      const bool play = state.isPlaying();
      state.setIsPlaying(!play, std::chrono::microseconds(0));

      update = true;
   }

   int tempo = static_cast<int>(state.tempo());
   auto proccessTempo = [&](Svin::Button& button, const int diff)
   {
      if (!button.isTriggered())
         return;

      tempo += diff;
      if (tempo < 20)
         tempo = 20;
      else if (tempo > 400)
         tempo = 400;

      state.setTempo(tempo, std::chrono::microseconds(0));
      update = true;
   };

   proccessTempo(tempoUpHundredButton, 100);
   proccessTempo(tempoDownHundredButton, -100);
   proccessTempo(tempoUpTenButton, 10);
   proccessTempo(tempoDownTenButton, -10);
   proccessTempo(tempoUpOneButton, 1);
   proccessTempo(tempoDownOneButton, -1);

   if (update)
      link.commitAudioSessionState(state);
}

void LinkControl::updateDisplays()
{
   ableton::Link::SessionState state = link.captureAppSessionState();

   // tempo
   if (link.numPeers() < 2)
      tempoDisplay.setColor(Color::Predefined::Blue);
   else
      tempoDisplay.setColor(Color::Predefined::Yellow);

   std::string tempoString = Text::convert(state.tempo(), 0);
   tempoString = Text::pad(tempoString, 3);
   tempoDisplay.setText(tempoString);

   // play
   playButton.setActive(state.isPlaying());

   const std::chrono::microseconds timeNow = link.clock().micros();
   const double phase = state.phaseAtTime(timeNow, 4.0); // 4 beats per bar

   const int value = static_cast<int>(10.0 * phase / 4.0);
   syncMeter.setValue(value);
}

// widget

LinkControlWidget::LinkControlWidget(LinkControl* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelLinkControl = Svin::Origin::the()->addModule<LinkControl, LinkControlWidget>("LinkControl");
