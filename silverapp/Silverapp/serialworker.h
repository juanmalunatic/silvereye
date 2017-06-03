#ifndef SerialWorker_H
#define SerialWorker_H

#include <QCoreApplication>
#include <QObject>
#include <QTimer>
#include <QSerialPort>
#include <QElapsedTimer>

//#include "imudata.h"


class SerialWorker : public QObject  // Inherit all methods and member variables of QObject and make them public
{

Q_OBJECT

public:

	SerialWorker();
	~SerialWorker();

	void closeSerialPort(); // public to be called by destructor

	void connectInternalSignals();

	QSerialPort mSerialPort;

private:

	bool openSerialPort();

signals:

	void serialDataArrived(const QByteArray& newSerialData);

	void errorChanged(QSerialPort::SerialPortError error);

	// TO-DO emit a signal on error

private slots:

	void handleReadyRead();

	// Changes and errors

	void handleError(QSerialPort::SerialPortError serialPortError);


public slots:

	// Handle port change
	void changeCurrentSerialPort(const QString& portNameToChangeTo);

};

#endif // SerialWorker_H
