/*

This guy's a beast.
http://stackoverflow.com/questions/25224575/how-to-safely-destruct-a-qthread

*/

#include <QDebug>

#include "serialthread.h"


SerialThread::SerialThread(QObject *parent) : QThread(parent)
{

}

SerialThread::~SerialThread() {

	quit();

	#if QT_VERSION >= QT_VERSION_CHECK(5,2,0)
	requestInterruption();
	#endif

	wait();

	qDebug() << "SerialThread ends.";

}
