#ifndef WavPlayerH
#define WavPlayerH

#include <rack.hpp>
using namespace rack;

#include <Sound/Sample.h>

#include <SchweineSystemDisplayOLED.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class WavPlayer : public SchweineSystem::Module
{
public:
   struct Panel;

public:
   WavPlayer();

public:
   void process(const ProcessArgs& args) override;
   void updateDisplays() override;
   void setWavFileName(const std::string& newFileName);

private:
   void setup();
   void load();
   json_t* dataToJson() override;
   void dataFromJson(json_t* rootJson) override;

private:
   SchweineSystem::DisplayOLED::Controller displayController;
   // file
   std::string fileName;
   Sample::Meta meta;
   // play
   Data audio;
   size_t playhead;
};

// widget

class WavPlayerWidget : public SchweineSystem::ModuleWidget
{
public:
   WavPlayerWidget(WavPlayer* module);

private:
   void setup();
   void displayClicked(const float& x, const float& y);   
};

#endif // NOT WavPlayerH
