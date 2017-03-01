#include "commander.h"

Commander::Commander(QObject *parent) :
	QObject(parent)
{
	connect(this, &Commander::readySend, this, &Commander::onReadySend);
}

void Commander::getCurrentAltitude(int index)
{
	QJsonObject json;

	json["commandType"] = "getCommand";
	json["command"] = __func__;
	json["index"] = QString::number(index);

	QString stringReadySend = QJsonDocument(json).toJson(QJsonDocument::Compact);

	emit readySend(stringReadySend);
}

void Commander::onReadySend(QString string)
{
	qDebug() << "String ready to send:" << string;
}