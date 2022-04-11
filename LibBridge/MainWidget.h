#ifndef MainWidgetH
#define MainWidgetH

#include <QWidget>

class MainWidget : public QWidget
{
   Q_OBJECT
public:
   MainWidget();

private:
   void closeEvent(QCloseEvent* ce) override;
};

#endif // NOT MainWidgetH
