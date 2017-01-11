#include "socketserver.h"
#include "QtWebSockets/QWebSocketServer"
#include "QtWebSockets/QWebSocket"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

SocketServer::SocketServer(quint16 port, QObject *parent) :
	QObject(parent),
	webSocketServer(Q_NULLPTR),
	clients() {

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

SocketServer::~SocketServer() {

	webSocketServer->close();
	qDeleteAll(clients.begin(), clients.end());
}

void SocketServer::onNewConnection() {

	QWebSocket *pSocket = webSocketServer->nextPendingConnection();

	qDebug() << "Client connected.";

	connect(pSocket, &QWebSocket::binaryMessageReceived, this, &SocketServer::processMessage);
	connect(pSocket, &QWebSocket::textMessageReceived, this, &SocketServer::processMessage);
	connect(pSocket, &QWebSocket::disconnected, this, &SocketServer::socketDisconnected);

	clients << pSocket;
}

void SocketServer::processMessage(QString message) {

	QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());

	qDebug() << "Message received:" << message;

	Q_FOREACH(QWebSocket *pClient, clients)
	{
		pClient->sendTextMessage(message);
		qDebug() << "Message sent back:" << message;
	}
}

void SocketServer::processBinaryMessage(QByteArray binaryMessage) {

	QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());

	qDebug() << "Binary message received:" << binaryMessage.data();

	Q_FOREACH(QWebSocket *pClient, clients)
	{
		pClient->sendBinaryMessage(binaryMessage);
		qDebug() << "Binary message sent back:" << binaryMessage.data();
	}
}

void SocketServer::socketDisconnected() {

	QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
	if (pClient)
	{
		clients.removeAll(pClient);
		pClient->deleteLater();
	}
}