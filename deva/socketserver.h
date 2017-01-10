#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class SocketServer : public QObject
{
	Q_OBJECT
public:
	explicit SocketServer(quint16 port, QObject *parent = Q_NULLPTR);
	virtual ~SocketServer();

	private Q_SLOTS:
	void onNewConnection();
	void processMessage(QString message);
	void processBinaryMessage(QByteArray binaryMessage);
	void socketDisconnected();

private:
	QWebSocketServer *webSocketServer;
	QList<QWebSocket *> clients;
};

#endif //SOCKETSERVER_H