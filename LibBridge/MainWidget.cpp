#include "MainWidget.h"

#include <QAction>
#include <QMenu>
#include <QMenuBar>

MainWidget::MainWidget()
   : QWidget(nullptr)
{
   setWindowTitle("VCV Rack 2 - Loader");

   QMenuBar* menuBar = new QMenuBar(this);

   QMenu* fileMenu = menuBar->addMenu("File");
   fileMenu->addAction("Load Library");
}

