#include <QApplication>

#include "Interface.h"

#include "MainWidget.h"

static QApplication* app = nullptr;

extern "C"
{
   CREATE_FUNCTION
   {
      static int argc = 1;
      static const char* argv = "VCV Rack2 Bridge Loader";
      app = new QApplication(argc, const_cast<char**>(&argv));

      MainWidget* mainWidget = new MainWidget();
      mainWidget->show();
   }

   INIT_FUNCTION
   {
      qDebug() << __FUNCTION__ << sampleRate;
   }

   PROCESS_FUNCTION
   {
      for (uint8_t index = 0; index < 8; index++)
      {
         output[index] = input[index];
      }
      app->processEvents();
   }

   TERMINATE_FUNCTION
   {
      delete app;
      app = nullptr;
   }
}
