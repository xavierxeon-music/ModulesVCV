#ifndef DisplayH
#define DisplayH

#include <rack.hpp>
using namespace rack;

#include <SvinButton.h>
#include <SvinDisplayOLED.h>

class TrackerWorker;

class Display
{
public:
   Display(TrackerWorker* main);

public:
   void process(const Module::ProcessArgs& args);
   void update();

private:
   enum class Mode
   {
      Division,
      Length,
      StageCount,
      StageIndex
   };

   friend class TrackerWorker;

private:
   void updatePassthrough();
   void updateRemote();
   void updateInternal();

private:
   TrackerWorker* main;

   Mode displayMode;
   Svin::Button displayButton;
   Svin::DisplayOLED::Controller displayController;
};

#endif // NOT DisplayH
