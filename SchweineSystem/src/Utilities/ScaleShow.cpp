#include "ScaleShow.h"

ScaleShow::ScaleShow()
   : Svin::Module()
   , noteList(this)
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
}

void ScaleShow::process(const ProcessArgs& args)
{
}

// widget

ScaleShowWidget::ScaleShowWidget(ScaleShow* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelScaleShow = Svin::Origin::the()->addModule<ScaleShow, ScaleShowWidget>("ScaleShow");
