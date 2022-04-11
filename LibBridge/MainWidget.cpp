#include "MainWidget.h"

#include <QAction>
#include <QCloseEvent>
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

void MainWidget::closeEvent(QCloseEvent* ce)
{
   ce->ignore();
}
