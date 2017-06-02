/*

<< DESCRIPTION >>

SerialWorker is a wrapper to instantiate a QSerialPort object
	(SerialWorkerInstance.mSerialPort).

This wrapper is necessary to move the processing of the serial input to
a non-GUI thread. Additionally, this wrapper helps manage the serial
port object (QSerialPort mSerialPort) from the MainWindow.

<< STRUCTURE >>

SerialWorker (constructor)

	[serial_config   ]

	[conn_ComPort_2_SerialWorker]


handleReadyRead

	[emit_SerialWorker_2_MainWindow]  (emits sendSerialData)

prepareToShutdown  (UNUSED)
	[serial_close]


<< TO-DO >>

Implement a method to change the port name.
	Current port name as private member variable
		Setter for port name
Implement a clean shutdown.
Implement error handling.

<< REFERENCES >>

[1] C++ Threading Pattern for Qt serial port
	http://stackoverflow.com/questions/25679153/c-threading-pattern-for-qt-serial-port/25679409#25679409

[2] How To Really, Truly Use QThreads; The Full Explanation
	https://mayaposch.wordpress.com/2011/11/01/how-to-really-truly-use-qthreads-the-full-explanation/

[3] Sharing data across Qt threads
	http://stackoverflow.com/questions/12372301/sharing-data-across-qt-threads/12374274#12374274

[4] Copied or Not Copied: Arguments in Signal-Slot Connections?
	http://www.embeddeduse.com/2013/06/29/copied-or-not-copied-arguments-signals-slots/

*/

#include "SerialWorker.h"
//#include "imudata.h"

#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QSerialPort>

SerialWorker::SerialWorker()

{

	/*-----------------------------------------------------------------
	* Configures the serial port according to the application needs.
	*----------------------------------------------------------------*/

	qDebug() << "A SerialWorker instance starts."; // Report initialization

	mSerialPort.setBreakEnabled(false);
	mSerialPort.setFlowControl(QSerialPort::NoFlowControl);


    mSerialPort.setPortName("\\\\.\\COM6");    // Port name

	qint32 customBaudRate = 38400;             // Baud rate (see /datasheets/rs232)
	mSerialPort.setBaudRate( customBaudRate ); // Apply baud rate

	this->openSerialPort();


	// Call this->connectInternalSignals() if not using threads

}


SerialWorker::~SerialWorker()
{

	this->closeSerialPort();
	qDebug() << "SerialWorker instance ends.";
}

// Enables to reconnect Worker and SerialPort if they change thread affinity
void SerialWorker::connectInternalSignals()
{

	/*-----------------------------------------------------------------
	* The QSerialPort object (mSerialPort) emits a ReadyRead signal
	* automatically when new data arrives to the port. SerialWorker
	* detects this event and handles the new data via handleReadyRead.
	*----------------------------------------------------------------*/

	QObject::connect
	(
		&mSerialPort,  &QSerialPort::readyRead,
				this, &SerialWorker::handleReadyRead
	);

	QObject::connect(
		&mSerialPort, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>
						  (&QSerialPort::error),
				this,     &SerialWorker::handleError
	);


}


/*------------------------------------------------------------------------
* Slot handleReadyRead is called when there's new data in mSerialPort
* (a QSerialPort connected to a specific COM Port). handleReadyRead
* emits this new (binary) data as a signal (it's formatted in MainWindow)
-------------------------------------------------------------------------*/

void SerialWorker::handleReadyRead()
{

	/* // [debug]
	qDebug() << mSerialPort.read(30);
	qDebug() << "-------------------------------"; */

	// The physical system transmits 30 bytes with each serial transaction.
	// read() is used instead of readLine() in case the data  forms an unintended line brake


	// qDebug() << "Data on selected port";

	QByteArray readByteArray = mSerialPort.read(30);

	if( readByteArray.size() == 30 )
	{
		emit serialDataArrived(readByteArray);
	}

	/*-----------------------------------------------------------------------
	* SerialWorker and MainWindow run in separate threads and communicate via
	* signals&slots. Qt uses queuedConnections for them, which requires copy-
	* ing arguments [3]. Therefore, using small arguments for cross-thread
	* signals helps improve performance [4].
	----------------------------------------------------------------------*/


	/* // [debug]
		QByteArray tempo = mSerialPort.read(30);
		qDebug() << tempo.toHex();
		qDebug() << "----------------";
		emit newDataToMainWindow( tempo ); */


}


bool SerialWorker::openSerialPort()

{

	bool portOpened = mSerialPort.open( QIODevice::ReadOnly );

	if( !portOpened )
	{
		qDebug() << "NOPEN: Serial port " << mSerialPort.portName() <<  " couldn't be opened.";
		return false;
	}

	qDebug() << "OPEN: Serial port " << mSerialPort.portName() << " opened.";
	qDebug() << "Baud rate: "        << mSerialPort.baudRate();


	mSerialPort.setDataTerminalReady(true); // Android needs me
	return true;

}

void SerialWorker::closeSerialPort()
{
	mSerialPort.setDataTerminalReady(false);

	// Use this deprecated function to free the port completely on exit (black magic)
	mSerialPort.setSettingsRestoredOnClose(false);

	// Close the serial port
	mSerialPort.close();

	qDebug() << "Closed serial port.";
}

void SerialWorker::changeCurrentSerialPort(const QString& portNameToChangeTo)
{

	if( mSerialPort.isOpen() )
	{
		this->closeSerialPort();
	}

	mSerialPort.setPortName(portNameToChangeTo);

	this->openSerialPort();

}



void SerialWorker::handleError(QSerialPort::SerialPortError serialPortError)
{

	// On portNameChange, port reports an error: there was no error. Ignore.

	if( serialPortError == QSerialPort::NoError )
	{
		return;
	}


	emit errorChanged( serialPortError );

}
