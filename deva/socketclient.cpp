#include "socketclient.h"

SocketClient::SocketClient(QObject *parent) : 
	QObject(parent)
{
}

void SocketClient::doConnect(QString address, quint16 port)
{
	socket = new QTcpSocket(this);
	commander = new Commander(this);

	connect(commander, &Commander::readySend, this, &SocketClient::sendMessage);

	socket->connectToHost(address, port);

	if (socket->waitForConnected(5000))
	{
		qDebug() << "Connected to" << address << ":" << port;
		connect(socket, &QTcpSocket::stateChanged, this, &SocketClient::onStateChanged);

		// send command
		commander->getCurrentAltitude(2);

		// read response
		qDebug() << "Reading:" << socket->bytesAvailable();
		qDebug() << socket->readAll();
	}
	else
	{
		qDebug() << "Not connected.";
	}
}

void SocketClient::onStateChanged(QAbstractSocket::SocketState state)
{
	qDebug() << state;
}

void SocketClient::sendMessage(QString cmdStringReadySend)
{
	qDebug() << "Command ready to send:" << cmdStringReadySend;
	cmdStringReadySend += "\n";
	socket->write(cmdStringReadySend.toUtf8());
	socket->waitForBytesWritten(1000);
	socket->waitForReadyRead(1000);
}