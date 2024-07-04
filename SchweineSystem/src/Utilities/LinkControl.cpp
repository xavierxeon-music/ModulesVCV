#include "LinkControl.h"

#include <Music/Note.h>

#include <SvinOrigin.h>

#include <ableton/Link.hpp>

LinkControl::LinkControl()
   : Svin::Module()
   , displayController(this, Panel::Pixels_Display)
   , playButton(this, Panel::Active, Panel::RGB_Active)
   , tempoUpButton(this, Panel::Up)
   , tempoDownButton(this, Panel::Down)
   , link(nullptr)
{
   setup();

   playButton.setDefaultColor(Color::Predefined::Green);

   link = new ableton::Link(120);
   link->enable(true);
   link->enableStartStopSync(true);
}

LinkControl::~LinkControl()
{
   link->enable(false);

   delete link;
   link = nullptr;
}

void LinkControl::process(const ProcessArgs& args)

{
}

void LinkControl::updateDisplays()
{
   ableton::Link::SessionState state = link->captureAppSessionState();
   playButton.setActive(state.isPlaying());

   displayController.fill();
   const double dPhase = state.phaseAtTime(state.timeForIsPlaying(), 53);

   displayController.drawRect(0, 12, static_cast<int>(dPhase), 14, true);

   displayController.setColor(Color::Predefined::White);

   std::string peerMessage = std::to_string(link->numPeers()) + " peers";
   displayController.writeText(1, 1, peerMessage, Svin::DisplayOLED::Font::Small);

   const int tempo = static_cast<int>(state.tempo());
   std::string tempoMessage = std::to_string(tempo) + " bpm";
   displayController.writeText(1, 20, tempoMessage, Svin::DisplayOLED::Font::Small);
}

// widget

LinkControlWidget::LinkControlWidget(LinkControl* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelLinkControl = Svin::Origin::the()->addModule<LinkControl, LinkControlWidget>("LinkControl");
