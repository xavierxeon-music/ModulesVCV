#include "LaunchpadImposter.h"

#include <Tools/Text.h>
#include <Tools/Variable.h>

#include <SvinLaunchpadClient.h>

LaunchpadImposter::LaunchpadImposter()
   : Svin::Module()
   , Svin::Midi::Input(true)
   , Svin::Midi::Output(true)
   , deviceId(0)
   , deviceIdDisplay(this, Panel::Text_DeviceId)
   , deviceIdUpButton(this, Panel::DeviceIdUp)
   , deviceIdDownButton(this, Panel::DeviceIdDown)
   , buttonList(this)
   , statusLED(this, Panel::RGB_RowNine_Logo)
{
   setup();

   deviceIdDisplay.setColor(Color::Predefined::Yellow);

   buttonList.append({{Panel::RowOne_ColOne, Panel::RGB_RowOne_ColOne},
                      {Panel::RowOne_ColTwo, Panel::RGB_RowOne_ColTwo},
                      {Panel::RowOne_ColThree, Panel::RGB_RowOne_ColThree},
                      {Panel::RowOne_ColFour, Panel::RGB_RowOne_ColFour},
                      {Panel::RowOne_ColFive, Panel::RGB_RowOne_ColFive},
                      {Panel::RowOne_ColSix, Panel::RGB_RowOne_ColSix},
                      {Panel::RowOne_ColSeven, Panel::RGB_RowOne_ColSeven},
                      {Panel::RowOne_ColEight, Panel::RGB_RowOne_ColEight},
                      {Panel::RowOne_ColNine, Panel::RGB_RowOne_ColNine},
                      {Panel::RowTwo_ColOne, Panel::RGB_RowTwo_ColOne},
                      {Panel::RowTwo_ColTwo, Panel::RGB_RowTwo_ColTwo},
                      {Panel::RowTwo_ColThree, Panel::RGB_RowTwo_ColThree},
                      {Panel::RowTwo_ColFour, Panel::RGB_RowTwo_ColFour},
                      {Panel::RowTwo_ColFive, Panel::RGB_RowTwo_ColFive},
                      {Panel::RowTwo_ColSix, Panel::RGB_RowTwo_ColSix},
                      {Panel::RowTwo_ColSeven, Panel::RGB_RowTwo_ColSeven},
                      {Panel::RowTwo_ColEight, Panel::RGB_RowTwo_ColEight},
                      {Panel::RowTwo_ColNine, Panel::RGB_RowTwo_ColNine},
                      {Panel::RowThree_ColOne, Panel::RGB_RowThree_ColOne},
                      {Panel::RowThree_ColTwo, Panel::RGB_RowThree_ColTwo},
                      {Panel::RowThree_ColThree, Panel::RGB_RowThree_ColThree},
                      {Panel::RowThree_ColFour, Panel::RGB_RowThree_ColFour},
                      {Panel::RowThree_ColFive, Panel::RGB_RowThree_ColFive},
                      {Panel::RowThree_ColSix, Panel::RGB_RowThree_ColSix},
                      {Panel::RowThree_ColSeven, Panel::RGB_RowThree_ColSeven},
                      {Panel::RowThree_ColEight, Panel::RGB_RowThree_ColEight},
                      {Panel::RowThree_ColNine, Panel::RGB_RowThree_ColNine},
                      {Panel::RowFour_ColOne, Panel::RGB_RowFour_ColOne},
                      {Panel::RowFour_ColTwo, Panel::RGB_RowFour_ColTwo},
                      {Panel::RowFour_ColThree, Panel::RGB_RowFour_ColThree},
                      {Panel::RowFour_ColFour, Panel::RGB_RowFour_ColFour},
                      {Panel::RowFour_ColFive, Panel::RGB_RowFour_ColFive},
                      {Panel::RowFour_ColSix, Panel::RGB_RowFour_ColSix},
                      {Panel::RowFour_ColSeven, Panel::RGB_RowFour_ColSeven},
                      {Panel::RowFour_ColEight, Panel::RGB_RowFour_ColEight},
                      {Panel::RowFour_ColNine, Panel::RGB_RowFour_ColNine},
                      {Panel::RowFive_ColOne, Panel::RGB_RowFive_ColOne},
                      {Panel::RowFive_ColTwo, Panel::RGB_RowFive_ColTwo},
                      {Panel::RowFive_ColThree, Panel::RGB_RowFive_ColThree},
                      {Panel::RowFive_ColFour, Panel::RGB_RowFive_ColFour},
                      {Panel::RowFive_ColFive, Panel::RGB_RowFive_ColFive},
                      {Panel::RowFive_ColSix, Panel::RGB_RowFive_ColSix},
                      {Panel::RowFive_ColSeven, Panel::RGB_RowFive_ColSeven},
                      {Panel::RowFive_ColEight, Panel::RGB_RowFive_ColEight},
                      {Panel::RowFive_ColNine, Panel::RGB_RowFive_ColNine},
                      {Panel::RowSix_ColOne, Panel::RGB_RowSix_ColOne},
                      {Panel::RowSix_ColTwo, Panel::RGB_RowSix_ColTwo},
                      {Panel::RowSix_ColThree, Panel::RGB_RowSix_ColThree},
                      {Panel::RowSix_ColFour, Panel::RGB_RowSix_ColFour},
                      {Panel::RowSix_ColFive, Panel::RGB_RowSix_ColFive},
                      {Panel::RowSix_ColSix, Panel::RGB_RowSix_ColSix},
                      {Panel::RowSix_ColSeven, Panel::RGB_RowSix_ColSeven},
                      {Panel::RowSix_ColEight, Panel::RGB_RowSix_ColEight},
                      {Panel::RowSix_ColNine, Panel::RGB_RowSix_ColNine},
                      {Panel::RowSeven_ColOne, Panel::RGB_RowSeven_ColOne},
                      {Panel::RowSeven_ColTwo, Panel::RGB_RowSeven_ColTwo},
                      {Panel::RowSeven_ColThree, Panel::RGB_RowSeven_ColThree},
                      {Panel::RowSeven_ColFour, Panel::RGB_RowSeven_ColFour},
                      {Panel::RowSeven_ColFive, Panel::RGB_RowSeven_ColFive},
                      {Panel::RowSeven_ColSix, Panel::RGB_RowSeven_ColSix},
                      {Panel::RowSeven_ColSeven, Panel::RGB_RowSeven_ColSeven},
                      {Panel::RowSeven_ColEight, Panel::RGB_RowSeven_ColEight},
                      {Panel::RowSeven_ColNine, Panel::RGB_RowSeven_ColNine},
                      {Panel::RowEight_ColOne, Panel::RGB_RowEight_ColOne},
                      {Panel::RowEight_ColTwo, Panel::RGB_RowEight_ColTwo},
                      {Panel::RowEight_ColThree, Panel::RGB_RowEight_ColThree},
                      {Panel::RowEight_ColFour, Panel::RGB_RowEight_ColFour},
                      {Panel::RowEight_ColFive, Panel::RGB_RowEight_ColFive},
                      {Panel::RowEight_ColSix, Panel::RGB_RowEight_ColSix},
                      {Panel::RowEight_ColSeven, Panel::RGB_RowEight_ColSeven},
                      {Panel::RowEight_ColEight, Panel::RGB_RowEight_ColEight},
                      {Panel::RowEight_ColNine, Panel::RGB_RowEight_ColNine},
                      {Panel::RowNine_ColOne, Panel::RGB_RowNine_ColOne},
                      {Panel::RowNine_ColTwo, Panel::RGB_RowNine_ColTwo},
                      {Panel::RowNine_ColThree, Panel::RGB_RowNine_ColThree},
                      {Panel::RowNine_ColFour, Panel::RGB_RowNine_ColFour},
                      {Panel::RowNine_ColFive, Panel::RGB_RowNine_ColFive},
                      {Panel::RowNine_ColSix, Panel::RGB_RowNine_ColSix},
                      {Panel::RowNine_ColSeven, Panel::RGB_RowNine_ColSeven},
                      {Panel::RowNine_ColEight, Panel::RGB_RowNine_ColEight}});

   uint8_t buttonIndex = 0;
   for (uint8_t row = 0; row < 9; row++)
   {
      for (uint8_t column = 0; column < 9; column++)
      {
         const uint8_t midiNote = (10 * (row + 1)) + (column + 1);

         indexToMidiNote[buttonIndex] = midiNote;
         midiNoteToIndex[midiNote] = buttonIndex;

         buttonIndex++;
         if (buttonIndex >= buttonList.size())
            break;
      }
   }

   createLaunchpad();
}

void LaunchpadImposter::process(const ProcessArgs& args)
{
   uint8_t tmpDeviceId = deviceId;
   Variable::Integer<uint8_t> varBank(tmpDeviceId, 0, 15, true);
   if (deviceIdUpButton.isTriggered())
      varBank.increment();
   else if (deviceIdDownButton.isTriggered())
      varBank.decrement();

   if (tmpDeviceId != deviceId)
   {
      deviceId = tmpDeviceId;
      createLaunchpad();
   }
}

void LaunchpadImposter::updateDisplays()
{
   static const std::vector<Color> palette = Svin::LaunchpadClient::getPalette();

   deviceIdDisplay.setText(Text::pad(std::to_string(deviceId + 1), 2));
}

void LaunchpadImposter::createLaunchpad()
{
   const std::string deviceName = "LPMiniMK3 MIDI " + std::to_string(deviceId);

   if (Svin::Midi::Input::connected())
      Svin::Midi::Input::close();
   Svin::Midi::Input::setTargetDeviceName(deviceName);
   Svin::Midi::Input::open();

   if (Svin::Midi::Output::connected())
      Svin::Midi::Output::close();
   Svin::Midi::Output::setTargetDeviceName(deviceName);
   Svin::Midi::Output::open();
}

void LaunchpadImposter::clockTick()
{
}

void LaunchpadImposter::noteOn(const ::Midi::Channel& channel, const uint8_t& midiNote, const ::Midi::Velocity& velocity)
{
   const Svin::LaunchpadClient::Mode mode = static_cast<Svin::LaunchpadClient::Mode>(channel - 1);
   static const std::vector<Color>& palette = Svin::LaunchpadClient::getPalette();
   const Color color = palette.at(velocity);

   if (99 == midiNote)
   {
      statusLED.setColor(color);
   }
   else
   {
      const uint8_t index = midiNoteToIndex[midiNote];
      buttonList[index]->setColor(color);
   }
}

void LaunchpadImposter::controllerChange(const ::Midi::Channel& channel, const ::Midi::ControllerMessage& controllerMessage, const uint8_t& value)
{
}

void LaunchpadImposter::load(const Svin::Json::Object& rootObject)
{
   deviceId = rootObject.get("deviceId").toInt();
   createLaunchpad();
}

void LaunchpadImposter::save(Svin::Json::Object& rootObject)
{
   rootObject.set("deviceId", deviceId);
}

// widget

LaunchpadImposterWidget::LaunchpadImposterWidget(LaunchpadImposter* module)
: Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelLaunchpadImposter = Svin::Origin::the()->addModule<LaunchpadImposter, LaunchpadImposterWidget>("LaunchpadImposter");

