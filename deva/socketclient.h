#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include <QTcpSocket>
#include "commander.h"

class SocketClient : public QObject
{
	Q_OBJECT

public:
	explicit SocketClient(QObject *parent = 0);

	void doConnect(QString address, quint16 port);

public slots:
	void onStateChanged(QAbstractSocket::SocketState state);
	void sendMessage(QString message);

private:
	QTcpSocket *socket;
	Commander *commander;
};

#endif // SOCKETCLIENT_H
