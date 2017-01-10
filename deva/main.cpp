#include "deva.h"
#include <QtWidgets/QApplication>
#include <QProcess>
#include "socketserver.h"
#include "main.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    deva w;
    w.show();

	SocketServer server(HOST_PORT);
	startAdb("C:\\adb\\adb.exe", HOST_PORT, DEVICE_PORT);

    return a.exec();
}

bool startAdb(QString adbPath, quint16 hostPort, quint16 devicePort) {

	QStringList arguments;

	// execute: adb shell am broadcast -a NotifyServiceStop
	arguments << "shell" << "am" << "broadcast" << "-a" << "NotifyServiceStop";
	if (!execute(adbPath, arguments)) {
		return false;
	}

	// execute: adb forward tcp:[hostPort] tcp:[devicePort]
	QString tcpPort = "tcp:%1";
	arguments.clear();
	arguments << "forward" << tcpPort.arg(hostPort) << tcpPort.arg(devicePort);
	if (!execute(adbPath, arguments)) {
		return false;
	}

	// execute: adb shell am broadcast -a NotifyServiceStart
	arguments.clear();
	arguments << "shell" << "am" << "broadcast" << "-a" << "NotifyServiceStart";
	if (!execute(adbPath, arguments)) {
		return false;
	}

	return true;
}

bool execute(QString exePath, QStringList arguments) {

	QProcess *process = new QProcess;

	// execute: [exePath] [arguments]
	process->start(exePath, arguments);

	// wait for started
	if (!process->waitForStarted()) {
		qDebug() << exePath << "failed to start.";
		qDebug() << "Arguments:" << arguments;
		return false;
	}

	// wait for finished
	while (!process->waitForFinished()) {
		qDebug() << exePath << "failed to finish.";
		qDebug() << "Arguments:" << arguments;
		return false;
	}

	if (process->exitStatus() != QProcess::NormalExit) {
		qDebug() << exePath << "Error occured.";
		qDebug() << "Arguments:" << arguments;
		qDebug() << process->readAllStandardError().data();
		return false;
	}
	else {
		qDebug() << process->readAll().data();
		return true;
	}
	
}