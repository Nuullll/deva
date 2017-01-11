#include "socketclient.h"
#include <QtCore/QDebug>
#include <iostream>

QT_USE_NAMESPACE

SocketClient::SocketClient(const QUrl &url, bool debug, QObject *parent) :
	QObject(parent),
	m_url(url),
	m_debug(debug)
{
	if (m_debug)
		qDebug() << "WebSocket server:" << url;
	connect(&m_webSocket, &QWebSocket::connected, this, &SocketClient::onConnected);
	connect(&m_webSocket, &QWebSocket::disconnected, this, &SocketClient::closed);
	connect(&m_webSocket, static_cast<void(QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error),
		[=](QAbstractSocket::SocketError error) { 
		qDebug() << "Error:" << error;
	});
	connect(&m_webSocket, &QWebSocket::stateChanged, this, &SocketClient::onStateChanged);
	m_webSocket.open(QUrl(url));
}

void SocketClient::onConnected()
{
	if (m_debug)
		qDebug() << "WebSocket connected";
	std::cout << "Websocket connected." << std::endl;
	
	connect(&m_webSocket, &QWebSocket::textMessageReceived,
		this, &SocketClient::onTextMessageReceived);
	m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));
}

void SocketClient::onTextMessageReceived(QString message)
{
	if (m_debug)
		qDebug() << "Message received:" << message;
	m_webSocket.close();
}

void SocketClient::onStateChanged(QAbstractSocket::SocketState state) {

	qDebug() << state;
}