#ifndef MaxPatchH
#define MaxPatchH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButton.h>
#include <SvinLED.h>
#include <SvinDisplayOLED.h>

class MaxPatch : public Svin::Module
{
public:
   struct Panel;

public:
   MaxPatch();
   ~MaxPatch();

public:
   void process(const ProcessArgs& args) override;
   void setPatchFileName(const std::string& newFileName);

private:
   inline void setup();

   void updateDisplays() override;

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

   void sendStart();
   void sendKill();

private:
   Svin::DisplayOLED::Controller displayController;
   Svin::Button restartButton;
   Svin::Button killButton;
   Svin::LED connectedLight;

   // file
   std::string fileName;
};

// widget

class MaxPatchWidget : public Svin::ModuleWidget
{
public:
   MaxPatchWidget(MaxPatch* module);

private:
   inline void setup();
};

#ifndef MaxPatchHPP
#include "MaxPatch.hpp"
#endif // NOT MaxPatchHPP

#endif // NOT MaxPatchH
