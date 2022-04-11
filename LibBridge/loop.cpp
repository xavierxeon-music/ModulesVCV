#include <QApplication>

#define INIT_FUNCTION void init(int argc, char **argv)
#define LOOP_FUNCTION void loop(int value)
#define TERMINATE_FUNCTION void terminate()

#include "MainWidget.h"

static QApplication *app = nullptr;

extern "C"
{
   INIT_FUNCTION
   {
      app = new QApplication(argc, argv);

      MainWidget *mainWidget = new MainWidget();
      mainWidget->show();
   }

   LOOP_FUNCTION
   {
      Q_UNUSED(value)
      app->processEvents();
   }

   TERMINATE_FUNCTION
   {
      delete app;
      app = nullptr;
   }
}
