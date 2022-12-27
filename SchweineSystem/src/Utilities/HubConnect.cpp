#include "HubConnect.h"

#include <Music/Note.h>

#include <SvinOrigin.h>

HubConnect::HubConnect()
   : Svin::Module()
   , noteList(this)
   , playButton(this, Panel::Play)
   , stopButton(this, Panel::Stop)
   , resetButton(this, Panel::Reset)
   , connectedLight(this, Panel::RGB_Connected)
{
   setup();
   registerHubClient("Clock");

   noteList.append({Panel::RGB_NoteC, Panel::RGB_NoteCs,
                    Panel::RGB_NoteD, Panel::RGB_NoteDs,
                    Panel::RGB_NoteE,
                    Panel::RGB_NoteF, Panel::RGB_NoteFs,
                    Panel::RGB_NoteG, Panel::RGB_NoteGs,
                    Panel::RGB_NoteA, Panel::RGB_NoteAs,
                    Panel::RGB_NoteB});

   for (uint8_t index = 0; index < noteList.size(); index++)
   {
      const Note::Value noteValue = static_cast<Note::Value>(index);
      noteList[index]->setDefaultColor(Note::colorMap.at(noteValue));
      noteList[index]->setOn();
   }

   connectedLight.setDefaultColor(Color::Predefined::Green);
}

void HubConnect::process(const ProcessArgs& args)
{
   if (playButton.isTriggered())
      sendStateToClock(State::Play);
   else if (stopButton.isTriggered())
      sendStateToClock(State::Stop);
   else if (resetButton.isTriggered())
      sendStateToClock(State::Reset);

   connectedLight.setActive(hubConnected());
}

void HubConnect::sendStateToClock(const State& state)
{
   Svin::Json::Object object;
   object.set("_Application", "Clock");
   object.set("_Type", "Action");

   if (State::Play == state)
      object.set("action", "start");
   else if (State::Stop == state)
      object.set("action", "stop");
   else if (State::Reset == state)
      object.set("action", "reset");

   sendDocumentToHub(1, object);
}

// widget

HubConnectWidget::HubConnectWidget(HubConnect* module)
: Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelHubConnect = Svin::Origin::the()->addModule<HubConnect, HubConnectWidget>("HubConnect");

