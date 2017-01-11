#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>

class SocketClient : public QObject
{
	Q_OBJECT
public:
	explicit SocketClient(const QUrl &url, bool debug = false, QObject *parent = Q_NULLPTR);

Q_SIGNALS:
	void closed();

private Q_SLOTS:
	void onConnected();
	void onTextMessageReceived(QString message);
	void onStateChanged(QAbstractSocket::SocketState state);

private:
	QWebSocket m_webSocket;
	QUrl m_url;
	bool m_debug;
};

#endif // SOCKETCLIENT_H