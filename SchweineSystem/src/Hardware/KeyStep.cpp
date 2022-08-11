#include "KeyStep.h"
#include "KeyStepPanel.h"

#include <SchweineSystemJson.h>
#include <SchweineSystemMaster.h>

KeyStep::KeyStep()
   : SchweineSystem::Module()
   , SchweineSystem::MidiOutput(Midi::Device::KeyStep1)
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
   , midiChannelSwitch(this, Panel::Channel1_Drums)
   , inputList(inputs)
   , patterns{0, 0, 0, 0}
   , channelSwitch(CvSwitch::ChannelCount::Sixteen)
   , displayList(this)
   , downButtonList(this)
   , upButtonList(this)
   , resetTrigger()
{
   setup();

   inputList.append({Panel::Channel1_Select,
                     Panel::Channel2_Select,
                     Panel::Channel3_Select,
                     Panel::Channel4_Select});

   displayList.append({{Panel::Text_Channel1_Pattern, Panel::RGB_Channel1_Pattern},
                       {Panel::Text_Channel2_Pattern, Panel::RGB_Channel2_Pattern},
                       {Panel::Text_Channel3_Pattern, Panel::RGB_Channel3_Pattern},
                       {Panel::Text_Channel4_Pattern, Panel::RGB_Channel4_Pattern}});

   downButtonList.append({Panel::Channel1_Down,
                          Panel::Channel2_Down,
                          Panel::Channel3_Down,
                          Panel::Channel4_Down});

   upButtonList.append({Panel::Channel1_Up,
                        Panel::Channel2_Up,
                        Panel::Channel3_Up,
                        Panel::Channel4_Up});

   for (uint8_t channel = 0; channel < 4; channel++)
   {
      displayList[channel]->setColor(SchweineSystem::Color{255, 255, 0});
      updateDisplay(channel);
   }

   connectionButton.setDefaultColor(SchweineSystem::Color{0, 255, 0});
   connectToMidiDevice();
}

void KeyStep::process(const ProcessArgs& args)
{
   if (connectionButton.isTriggered())
      connectToMidiDevice();

   const bool isReset = resetTrigger.process(inputs[Panel::Reset].getVoltage() > 3.0);
   if (isReset)
      sendClockReset();

   for (uint8_t channel = 0; channel < 4; channel++)
   {
      uint8_t newPattern = patterns[channel];

      if (!inputList[channel]->isConnected())
      {
         if (downButtonList[channel]->isTriggered())
         {
            if (0 == newPattern)
               newPattern = 15;
            else
               newPattern--;
         }
         else if (upButtonList[channel]->isTriggered())
         {
            if (15 == newPattern)
               newPattern = 0;
            else
               newPattern++;
         }
      }
      else
      {
         const float voltage = inputList[channel]->getVoltage();
         newPattern = channelSwitch.index(voltage);
      }

      if (patterns[channel] == newPattern)
         continue;

      patterns[channel] = newPattern;
      updateDisplay(channel);

      if (connected())
         sendProgramChange(channel);
   }
}

void KeyStep::connectToMidiDevice()
{
   if (connected())
   {
      connectionButton.setOn();
      return;
   }

   connectionButton.setOff();
   if (!open())
      return;

   connectionButton.setOn();

   for (uint8_t channel = 0; channel < 4; channel++)
   {
      if (connected())
         sendProgramChange(channel);
   }
}

void KeyStep::sendProgramChange(uint8_t channel)
{
   Midi::Channel midiChannel = Midi::Device::KeyStep1 + channel;
   if (0 == channel && midiChannelSwitch.isOn())
      midiChannel = Midi::Device::DrumTrigger;

   std::cout << (uint16_t)midiChannel << std::endl;

   std::vector<unsigned char> progChangeMessage(2);
   progChangeMessage[0] = (Midi::Event::ProgrammChange | (midiChannel - 1));
   progChangeMessage[1] = patterns[channel];
   sendMessage(progChangeMessage);
}

void KeyStep::sendClockReset()
{
   std::vector<unsigned char> startMessage(1);
   startMessage[0] = Midi::Event::Start;
   sendMessage(startMessage);
}

void KeyStep::updateDisplay(uint8_t channel)
{
   std::string text = std::to_string(patterns[channel] + 1);
   if (1 == text.size())
      text = "0" + text;
   displayList[channel]->setText(text);
}

json_t* KeyStep::dataToJson()
{
   using namespace SchweineSystem::Json;

   Array patternArray;
   for (uint8_t channel = 0; channel < 4; channel++)
      patternArray.append(Value(patterns[channel]));

   Object rootObject;
   rootObject.set("patterns", patternArray);
   rootObject.set("channel1Mode", midiChannelSwitch.isOn());

   return rootObject.toJson();
}

void KeyStep::dataFromJson(json_t* rootJson)
{
   using namespace SchweineSystem::Json;

   Object rootObject(rootJson);

   Array patternArray = rootObject.get("patterns").toArray();
   for (uint8_t channel = 0; channel < 4; channel++)
   {
      patterns[channel] = patternArray.get(channel).toInt();
      if (connected())
         sendProgramChange(channel);
      updateDisplay(channel);
   }

   const bool channel1Mode = rootObject.get("channel1Mode").toBool();
   midiChannelSwitch.setState(channel1Mode);
}

// widget

KeyStepWidget::KeyStepWidget(KeyStep* module)
   : SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelKeyStep = SchweineSystem::Master::the()->addModule<KeyStep, KeyStepWidget>("KeyStep");
