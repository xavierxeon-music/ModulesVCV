#include "MetroControl.h"

MetroControl::MetroControl()
   : Svin::Module()
   , Svin::MasterClock::Client()
   , Svin::MidiOutput("MetropolixControl")
   , playPauseController(this, Panel::Pixels_PlayPause)
   , isRunning(false)
   , resetController(this, Panel::Pixels_Reset)
   , connectedLight(this, Panel::RGB_Connected)
{
   setup();
   registerHubClient("Clock");
   open();

   using ClickedFunction = Svin::DisplayOLED::Controller::ClickedFunction;

   ClickedFunction playPausePressedFunction = std::bind(&MetroControl::playPausePressed, this, std::placeholders::_1, std::placeholders::_2);
   playPauseController.onPressed(playPausePressedFunction);

   ClickedFunction resetPressedFunction = std::bind(&MetroControl::resetPressed, this, std::placeholders::_1, std::placeholders::_2);
   resetController.onPressed(resetPressedFunction);

   connectedLight.setDefaultColor(Color::Predefined::Green);
}

void MetroControl::process(const ProcessArgs& args)
{
   connectedLight.setActive(connected());
   isRunning = getTempo().isRunningOrFirstTick();
}

void MetroControl::updateDisplays()
{
   //playPauseController.writeText(5, 0, u8"\u23ef", 20); // ⏯ , does not work
   //resetController.writeText(5, 0, u8"\u23ee", 20); // ⏮  , does not work

   playPauseController.fill(Color::Predefined::Black);
   if (isRunning)
   {
      playPauseController.setColor(Color::Predefined::Cyan);
      playPauseController.writeText(3, -4, u8"\u25eb", 25); // pause
   }
   else
   {
      playPauseController.setColor(Color::Predefined::Green);
      playPauseController.writeText(4, -3, u8"\u25b6", 24); // play
   }

   resetController.fill(Color::Predefined::Black);
   resetController.setColor(Color::Predefined::Magenta);
   resetController.writeText(3, -4, u8"\u2302", 25); // home
}

void MetroControl::sendStateToClock(const State& state)
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

void MetroControl::playPausePressed(const float& x, const float& y)
{
   (void)x;
   (void)y;

   if (isRunning)
      sendControllerChange(1, Midi::User01, 0);
   else
      sendControllerChange(1, Midi::User01, 1);
}

void MetroControl::resetPressed(const float& x, const float& y)
{
   (void)x;
   (void)y;

   sendControllerChange(1, Midi::User02, 0);
}

// widget

MetroControlWidget::MetroControlWidget(MetroControl* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelMetroControl = Svin::Origin::the()->addModule<MetroControl, MetroControlWidget>("MetroControl");
