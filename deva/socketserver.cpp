#include "socketserver.h"
#include "QtWebSockets/QWebSocketServer"
#include "QtWebSockets/QWebSocket"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

SocketServer::SocketServer(quint16 port, QObject *parent) :
	QObject(parent),
	webSocketServer(Q_NULLPTR),
	clients()
{
	webSocketServer = new QWebSocketServer(QStringLiteral("Chat Server"),
		QWebSocketServer::NonSecureMode,
		this);
	if (webSocketServer->listen(QHostAddress::Any, port))
	{
		qDebug() << "Socket Server listening on port" << port;
		connect(webSocketServer, &QWebSocketServer::newConnection,
			this, &SocketServer::onNewConnection);
	}
}

SocketServer::~SocketServer()
{
	webSocketServer->close();
	qDeleteAll(clients.begin(), clients.end());
}

void SocketServer::onNewConnection()
{
	QWebSocket *pSocket = webSocketServer->nextPendingConnection();

	connect(pSocket, &QWebSocket::textMessageReceived, this, &SocketServer::processMessage);
	connect(pSocket, &QWebSocket::disconnected, this, &SocketServer::socketDisconnected);

	clients << pSocket;
}

void SocketServer::processMessage(QString message)
{
	QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
	Q_FOREACH(QWebSocket *pClient, clients)
	{
		if (pClient != pSender) //don't echo message back to sender
		{
			pClient->sendTextMessage(message);
		}
	}
}

void SocketServer::socketDisconnected()
{
	QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
	if (pClient)
	{
		clients.removeAll(pClient);
		pClient->deleteLater();
	}
}