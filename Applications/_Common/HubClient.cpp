#include "HubClient.h"

#include <AppSettings.h>
#include <JSONTools.h>

static const quint16 port = 2357;

Hub::Client::Client(QObject* parent, const QString& appName)
   : QObject(parent)
   , socket(nullptr)
   , appName(appName)
{
   socket = new QTcpSocket(this);

   connect(socket, &QTcpSocket::readyRead, this, &Client::slotReadyRead);
   connect(socket, &QTcpSocket::stateChanged, this, &Client::slotStateChanged);

   AppSettings settings;
   settings.write("host", QString("127.0.0.1"), true);

   const QString hostName = settings.string("host");
   socket->connectToHost(hostName, port);
}

void Hub::Client::sendDocument(const QJsonObject& object) const
{
   const QByteArray content = JSONTools::Helper::convert(object);
   socket->write(content);
}

void Hub::Client::slotStateChanged(QAbstractSocket::SocketState socketState)
{
   if (QAbstractSocket::ConnectedState == socketState)
      socket->write(appName.toUtf8());
}

void Hub::Client::slotReadyRead()
{
   const QByteArray content = socket->readAll();

   const QJsonObject object = JSONTools::Helper::convert(content);
   if (appName != object["_Application"].toString())
      return;

   processDocument(object);
}
