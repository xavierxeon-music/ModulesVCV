#include "LaunchpadImposter.h"

#include <Tools/Text.h>
#include <Tools/Variable.h>

#include <SvinLaunchpadClient.h>

const LaunchpadImposter::TextMap LaunchpadImposter::textMap = {{19, u8"\u2022"},
                                                               {29, ">"},
                                                               {39, ">"},
                                                               {49, ">"},
                                                               {59, ">"},
                                                               {69, ">"},
                                                               {79, ">"},
                                                               {89, ">"},
                                                               {91, u8"\u25b2"},
                                                               {92, u8"\u25bc"},
                                                               {93, u8"\u25c0"},
                                                               {94, u8"\u25b6"},
                                                               {95, "S"},
                                                               {96, "D"},
                                                               {97, "K"},
                                                               {98, "U"}};

const std::vector<Color> LaunchpadImposter::palette = []()
{
   const std::vector<Color>& sysPalette = Svin::LaunchpadClient::getPalette();

   std::vector<Color> palette(sysPalette.size());
   palette[0] = sysPalette[0];

   for (uint8_t index = 1; index < sysPalette.size(); index++)
   {
      Color color = sysPalette[index];
      float dist = color.distance(Color::Predefined::Black);
      while (dist < 6000)
      {
         color = color.dim(1.1);
         dist = color.distance(Color::Predefined::Black);
      }
      palette[index] = color;
   }
   return palette;
}();

LaunchpadImposter::LaunchpadImposter()
   : Svin::Module()
   , Svin::Midi::Input(true)
   , Svin::Midi::Output(true)
   , deviceId(1)
   , deviceIdDisplay(this, Panel::Text_DeviceId)
   , deviceIdUpButton(this, Panel::DeviceIdUp)
   , deviceIdDownButton(this, Panel::DeviceIdDown)
   , buttonList(this)
   , statusLED(this, Panel::RGB_Logo)
{
   setup();

   deviceIdDisplay.setColor(Color::Predefined::Yellow);

   buttonList.append({Panel::Pixels_RowOne_ColOne,
                      Panel::Pixels_RowOne_ColTwo,
                      Panel::Pixels_RowOne_ColThree,
                      Panel::Pixels_RowOne_ColFour,
                      Panel::Pixels_RowOne_ColFive,
                      Panel::Pixels_RowOne_ColSix,
                      Panel::Pixels_RowOne_ColSeven,
                      Panel::Pixels_RowOne_ColEight,
                      Panel::Pixels_RowOne_ColNine,
                      Panel::Pixels_RowTwo_ColOne,
                      Panel::Pixels_RowTwo_ColTwo,
                      Panel::Pixels_RowTwo_ColThree,
                      Panel::Pixels_RowTwo_ColFour,
                      Panel::Pixels_RowTwo_ColFive,
                      Panel::Pixels_RowTwo_ColSix,
                      Panel::Pixels_RowTwo_ColSeven,
                      Panel::Pixels_RowTwo_ColEight,
                      Panel::Pixels_RowTwo_ColNine,
                      Panel::Pixels_RowThree_ColOne,
                      Panel::Pixels_RowThree_ColTwo,
                      Panel::Pixels_RowThree_ColThree,
                      Panel::Pixels_RowThree_ColFour,
                      Panel::Pixels_RowThree_ColFive,
                      Panel::Pixels_RowThree_ColSix,
                      Panel::Pixels_RowThree_ColSeven,
                      Panel::Pixels_RowThree_ColEight,
                      Panel::Pixels_RowThree_ColNine,
                      Panel::Pixels_RowFour_ColOne,
                      Panel::Pixels_RowFour_ColTwo,
                      Panel::Pixels_RowFour_ColThree,
                      Panel::Pixels_RowFour_ColFour,
                      Panel::Pixels_RowFour_ColFive,
                      Panel::Pixels_RowFour_ColSix,
                      Panel::Pixels_RowFour_ColSeven,
                      Panel::Pixels_RowFour_ColEight,
                      Panel::Pixels_RowFour_ColNine,
                      Panel::Pixels_RowFive_ColOne,
                      Panel::Pixels_RowFive_ColTwo,
                      Panel::Pixels_RowFive_ColThree,
                      Panel::Pixels_RowFive_ColFour,
                      Panel::Pixels_RowFive_ColFive,
                      Panel::Pixels_RowFive_ColSix,
                      Panel::Pixels_RowFive_ColSeven,
                      Panel::Pixels_RowFive_ColEight,
                      Panel::Pixels_RowFive_ColNine,
                      Panel::Pixels_RowSix_ColOne,
                      Panel::Pixels_RowSix_ColTwo,
                      Panel::Pixels_RowSix_ColThree,
                      Panel::Pixels_RowSix_ColFour,
                      Panel::Pixels_RowSix_ColFive,
                      Panel::Pixels_RowSix_ColSix,
                      Panel::Pixels_RowSix_ColSeven,
                      Panel::Pixels_RowSix_ColEight,
                      Panel::Pixels_RowSix_ColNine,
                      Panel::Pixels_RowSeven_ColOne,
                      Panel::Pixels_RowSeven_ColTwo,
                      Panel::Pixels_RowSeven_ColThree,
                      Panel::Pixels_RowSeven_ColFour,
                      Panel::Pixels_RowSeven_ColFive,
                      Panel::Pixels_RowSeven_ColSix,
                      Panel::Pixels_RowSeven_ColSeven,
                      Panel::Pixels_RowSeven_ColEight,
                      Panel::Pixels_RowSeven_ColNine,
                      Panel::Pixels_RowEight_ColOne,
                      Panel::Pixels_RowEight_ColTwo,
                      Panel::Pixels_RowEight_ColThree,
                      Panel::Pixels_RowEight_ColFour,
                      Panel::Pixels_RowEight_ColFive,
                      Panel::Pixels_RowEight_ColSix,
                      Panel::Pixels_RowEight_ColSeven,
                      Panel::Pixels_RowEight_ColEight,
                      Panel::Pixels_RowEight_ColNine,
                      Panel::Pixels_RowNine_ColOne,
                      Panel::Pixels_RowNine_ColTwo,
                      Panel::Pixels_RowNine_ColThree,
                      Panel::Pixels_RowNine_ColFour,
                      Panel::Pixels_RowNine_ColFive,
                      Panel::Pixels_RowNine_ColSix,
                      Panel::Pixels_RowNine_ColSeven,
                      Panel::Pixels_RowNine_ColEight});

   uint8_t buttonIndex = 0;
   for (uint8_t row = 0; row < 9; row++)
   {
      for (uint8_t column = 0; column < 9; column++)
      {
         const uint8_t midiNote = (10 * (row + 1)) + (column + 1);

         indexToMidiNote[buttonIndex] = midiNote;
         midiNoteToIndex[midiNote] = buttonIndex;

         Svin::DisplayOLED::Controller::ClickedFunction pressedFunction = std::bind(&LaunchpadImposter::buttonPressed, this, buttonIndex, std::placeholders::_1, std::placeholders::_2);
         buttonList[buttonIndex]->onPressed(pressedFunction);

         Svin::DisplayOLED::Controller::ClickedFunction releasedFunction = std::bind(&LaunchpadImposter::buttonReleased, this, buttonIndex, std::placeholders::_1, std::placeholders::_2);
         buttonList[buttonIndex]->onReleased(releasedFunction);

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
   Variable::Integer<uint8_t> varBank(tmpDeviceId, 1, 15, true);
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


   for (uint8_t index = 0; index < buttonList.size(); index++)
   {
      Svin::DisplayOLED::Controller* controller = buttonList[index];
      controller->fill();

      const uint8_t midiNote = indexToMidiNote[index];
      if (textMap.find(midiNote) == textMap.end())
      {
         controller->drawRect(0, 0, 20, 20, true);
      }
      else
      {
         controller->writeText(5, 0, textMap.at(midiNote), 20);
      }
   }
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
   using Mode = Svin::LaunchpadClient::Mode;

   const Mode mode = static_cast<Mode>(channel - 1);
   Color color = palette.at(velocity);

   if (Mode::Off == mode)
      color = Color::Predefined::Black;

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

void LaunchpadImposter::buttonPressed(const uint8_t index, const float& x, const float& y)
{
   (void)x;
   (void)y;
   sendNoteOn(1, indexToMidiNote[index], 127);
}

void LaunchpadImposter::buttonReleased(const uint8_t index, const float& x, const float& y)
{
   (void)x;
   (void)y;
   sendNoteOn(1, indexToMidiNote[index], 0);
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
