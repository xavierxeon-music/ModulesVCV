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
   void update();

private:
   friend class TrackerWorker;

private:
   void updatePassthrough();
   void updateRemote();
   void updateInternalOverview();
   void updateInternalCurrent();

   void displayClicked(const float& x, const float& y);

private:
   TrackerWorker* main;
   Svin::DisplayOLED::Controller controller;
};

#endif // NOT DisplayH
