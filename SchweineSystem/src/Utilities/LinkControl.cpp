#include "LinkControl.h"

#include <Music/Note.h>

#include <SvinOrigin.h>

LinkControl::LinkControl()
   : Svin::Module()
   , noteList(this)
   , connectedLight(this, Panel::RGB_Connected)
{
   setup();

   noteList.append({Panel::RGB_NoteC, Panel::RGB_NoteCs,
                    Panel::RGB_NoteD, Panel::RGB_NoteDs,
                    Panel::RGB_NoteE,
                    Panel::RGB_NoteF, Panel::RGB_NoteFs,
                    Panel::RGB_NoteG, Panel::RGB_NoteGs,
                    Panel::RGB_NoteA, Panel::RGB_NoteAs,
                    Panel::RGB_NoteB});

   for (uint8_t index = 0; index < noteList.size(); index++)
   {
      const Note::Value noteValue = static_cast<Note::Value>(index);
      noteList[index]->setDefaultColor(Note::colorMap.at(noteValue));
      noteList[index]->setOn();
   }

   connectedLight.setDefaultColor(Color::Predefined::Green);

}

void LinkControl::process(const ProcessArgs& args)
{
   connectedLight.setActive(LinkControled());
}

// widget

LinkControlWidget::LinkControlWidget(LinkControl* module)
: Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelLinkControl = Svin::Origin::the()->addModule<LinkControl, LinkControlWidget>("LinkControl");

