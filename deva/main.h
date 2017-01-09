#ifndef MAIN_H
#define MAIN_H

#include <QtCore>

static quint16 HOST_PORT = 12580;
static quint16 DEVICE_PORT = 10086;

bool startAdb(QString adbPath, quint16 hostPort = HOST_PORT, quint16 devicePort = DEVICE_PORT);
bool execute(QString exePath, QStringList arguments);

#endif //MAIN_H