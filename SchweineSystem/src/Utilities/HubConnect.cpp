#include "HubConnect.h"

#include <Music/Note.h>

#include <SvinOrigin.h>

HubConnect::HubConnect()
   : Svin::Module()
   , Svin::MasterClock::Client()
   , playPauseController(this, Panel::Pixels_PlayPause)
   , isRunning(false)
   , resetController(this, Panel::Pixels_Reset)
   , noteList(this)
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

   using ClickedFunction = Svin::DisplayOLED::Controller::ClickedFunction;

   ClickedFunction playPausePressedFunction = std::bind(&HubConnect::playPausePressed, this, std::placeholders::_1, std::placeholders::_2);
   playPauseController.onPressed(playPausePressedFunction);

   ClickedFunction resetPressedFunction = std::bind(&HubConnect::resetPressed, this, std::placeholders::_1, std::placeholders::_2);
   resetController.onPressed(resetPressedFunction);
}

void HubConnect::process(const ProcessArgs& args)
{
   connectedLight.setActive(hubConnected());
   isRunning = getTempo().isRunningOrFirstTick();
}

void HubConnect::updateDisplays()
{
   //playPauseController.writeText(5, 0, u8"\u23ef", 20); // ⏯ , does not work
   //resetController.writeText(5, 0, u8"\u23ee", 20); // ⏮  , does not work

   playPauseController.fill(Svin::ModuleWidget::BackGroundColor);
   if (isRunning)
   {
      playPauseController.setColor(Color::Predefined::Yellow);
      playPauseController.writeText(2, -8, u8"\u25eb", 30); // pause
   }
   else
   {
      playPauseController.setColor(Color::Predefined::Green);
      playPauseController.writeText(2, -8, u8"\u25b6", 30); // play
   }

   resetController.fill(Svin::ModuleWidget::BackGroundColor);
   resetController.setColor(Color::Predefined::Magenta);
   resetController.writeText(2, -8, u8"\u2302", 30); // home
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

void HubConnect::playPausePressed(const float& x, const float& y)
{
   (void)x;
   (void)y;

   if (isRunning)
      sendStateToClock(State::Stop);
   else
      sendStateToClock(State::Play);
}

void HubConnect::resetPressed(const float& x, const float& y)
{
   (void)x;
   (void)y;

   sendStateToClock(State::Reset);
}

// widget

HubConnectWidget::HubConnectWidget(HubConnect* module)
: Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelHubConnect = Svin::Origin::the()->addModule<HubConnect, HubConnectWidget>("HubConnect");

