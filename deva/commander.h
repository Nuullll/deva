#ifndef COMMANDER_H
#define COMMANDER_H

#include <QtCore>

class Commander : public QObject
{
	Q_OBJECT

public:
	explicit Commander(QObject *parent = 0);

	void getCurrentAltitude(int index);

signals:
	void readySend(QString stringReadySend);

public slots:
	void onReadySend(QString stringReadySend);

private:
	
};

#endif // !COMMANDER_H
