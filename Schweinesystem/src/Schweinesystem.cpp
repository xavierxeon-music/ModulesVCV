#include "Schweinesystem.h"

#include "RandomWalk.h"

Plugin* pluginInstance = nullptr;

void init(Plugin* p)
{
   pluginInstance = p;

   // Add modules here
   Model* modelRandomWalk = createModel<RandomWalk, RandomWalkWidget>("RandomWalk");
   p->addModel(modelRandomWalk);

   // Any other plugin initialization may go here.
   // As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
