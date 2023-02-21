#ifndef HubClientH
#define HubClientH

#include <QObject>

#include <QTcpSocket>

class MainWidget;

namespace Hub
{
   class Client : public QObject
   {
      Q_OBJECT
   public:
      Client(MainWidget* mainWidget, const QString& appName);

   protected:
      void sendDocument(const QJsonObject& object) const;
      virtual void processDocument(const QJsonObject& object) = 0;

   private slots:
      void slotStateChanged(QAbstractSocket::SocketState socketState);
      void slotReadyRead();

   private:
      QTcpSocket* socket;
      const QString appName;
   };
} // namespace Hub

#endif // NOT HubClientH
