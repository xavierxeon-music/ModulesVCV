#include "AturiaStep.h"
#include "AturiaStepPanel.h"

#include <Tools/Variable.h>

#include <SvinMaster.h>

AturiaStep::AturiaStep()
   : Svin::Module()
   , MidiBusModule(Midi::Device::KeyStep1, this)
   , useDrumChannel(false)
   , drumButon(this, Panel::Drums, Panel::RGB_Drums)
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
   , inputList(this)
   , patterns{0, 0, 0, 0}
   , channelSwitch(CvSwitch::ChannelCount::Sixteen)
   , displayList(this)
   , downButtonList(this)
   , upButtonList(this)
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
      displayList[channel]->setColor(Svin::Color{255, 255, 0});
      updateDisplay(channel);
   }

   drumButon.setDefaultColor(Svin::Color{0, 0, 255});
   drumButon.setActive(useDrumChannel);

   connectionButton.setDefaultColor(Svin::Color{0, 255, 0});
   connectToMidiDevice();
}

void AturiaStep::process(const ProcessArgs& args)
{
   BusMidi busMessage = receiveFromLeft();
   sendToRight(busMessage);

   if (connectionButton.isTriggered())
      connectToMidiDevice();

   if (connected())
      processBusMessage(busMessage);

   if (drumButon.isTriggered())
      useDrumChannel ^= true;
   drumButon.setActive(useDrumChannel);

   for (uint8_t channel = 0; channel < 4; channel++)
   {
      uint8_t newPattern = patterns[channel];

      if (!inputList[channel]->isConnected())
      {
         Variable::Integer<uint8_t> var(newPattern, 0, 15, true);
         if (downButtonList[channel]->isTriggered())
            var.increment();
         else if (upButtonList[channel]->isTriggered())
            var.decrement();
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

void AturiaStep::connectToMidiDevice()
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

void AturiaStep::sendProgramChange(uint8_t channel)
{
   Midi::Channel midiChannel = Midi::Device::KeyStep1 + channel;
   if (0 == channel && useDrumChannel)
      midiChannel = Midi::Device::DrumTrigger;

   std::cout << (uint16_t)midiChannel << std::endl;

   std::vector<unsigned char> progChangeMessage(2);
   progChangeMessage[0] = (Midi::Event::ProgrammChange | (midiChannel - 1));
   progChangeMessage[1] = patterns[channel];
   sendMessage(progChangeMessage);
}

void AturiaStep::updateDisplay(uint8_t channel)
{
   std::string text = std::to_string(patterns[channel] + 1);
   if (1 == text.size())
      text = "0" + text;

   displayList[channel]->setText(text);
}

void AturiaStep::load(const Svin::Json::Object& rootObject)
{
   Svin::Json::Array patternArray = rootObject.get("patterns").toArray();
   for (uint8_t channel = 0; channel < 4; channel++)
   {
      patterns[channel] = patternArray.get(channel).toInt();
      if (connected())
         sendProgramChange(channel);
      updateDisplay(channel);
   }

   useDrumChannel = rootObject.get("channel1Mode").toBool();
}

void AturiaStep::save(Svin::Json::Object& rootObject)
{
   Svin::Json::Array patternArray;
   for (uint8_t channel = 0; channel < 4; channel++)
      patternArray.append(patterns[channel]);

   rootObject.set("patterns", patternArray);
   rootObject.set("channel1Mode", useDrumChannel);
}

// widget

AturiaStepWidget::AturiaStepWidget(AturiaStep* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

Model* modelAturiaStep = Svin::Master::the()->addModule<AturiaStep, AturiaStepWidget>("AturiaStep");
