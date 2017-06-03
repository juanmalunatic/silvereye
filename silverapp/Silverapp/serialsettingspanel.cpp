/*
 *
Casos de revisar:

	Se inició el sistema
		Intentar el puerto por defecto. Si no se logra, quedarse ahí.

	Se quiere usar otro puerto
		Entrar y seleccionarlo

	Se reinició al maestro (mismo puerto)

		Detectar la desconexión (no sucede)
		Si estaba open cuando se reinicia, se jode.
			Como se arregla?
			Closed serial port.
			NOPEN: Serial port  "COM10"  couldn't be opened.
			QSerialPort::SerialPortError(DeviceNotFoundError)

		Temporal: cambiar a otro puerto
				  reiniciar dispofísico mientras en otro puerto
				  reseleccionarlo

				  y si no hay otro puerto?

	Se cambió de puerto al maestro

		Detectar la desconexión (no sucede)
			Actualizar el texto diciendo "Disconnected. Select port."
		Actualizar lista. Seleccionar nuevo puerto. Listo.
*/

#include "serialsettingspanel.h"
#include "ui_serialsettingspanel.h"

#include "qpanel.h"
#include "mainwindow.h"
#include "serialworker.h"

#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>



SerialSettingsPanel::SerialSettingsPanel(QWidget *parent) :

	QPanel(parent), mpUi(new Ui::SerialSettingsPanel)

{

	/// Setup

	mpUi->setupUi(this);
	this->updateAvailableSerialPorts();

	/// Get serialworker
	///
	MainWindow *pMainWindow = qobject_cast<MainWindow*>( this->parent() );
	mpRemoteSerialWorker    = pMainWindow->getSerialWorker();

	/// Check if there's an open port
	///
	bool initialPortOpened =  mpRemoteSerialWorker->mSerialPort.isOpen();
	if(! initialPortOpened )
	{
		mpUi->portStatusTextEdit->setText("Initial port opening failed. Select a port.");
	}

	/// Connections

	// Overloaded signals require additional syntax to disambiguate
	// https://wiki.qt.io/New_Signal_Slot_Syntax
	QObject::connect(

		mpUi->portSelectComboBox, static_cast<void (QComboBox::*)(const QString&)>
										   ( &QComboBox::activated ),
						   this,   &SerialSettingsPanel::formatComboBoxPortName
	);



	QObject::connect(

					   this, &SerialSettingsPanel::comboBoxPortNameChanged,
	   mpRemoteSerialWorker,        &SerialWorker::changeCurrentSerialPort

	);

	// Update ports, among others, on show

	QObject::connect(

		qobject_cast<QPanel*>(this) ,              &QPanel::panelOpened,
							  this  , &SerialSettingsPanel::updateAvailableSerialPorts

	);

	// Error handling

	QObject::connect(

				mpRemoteSerialWorker,        &SerialWorker::errorChanged,
								this, &SerialSettingsPanel::displaySerialWorkerError

	);


}

SerialSettingsPanel::~SerialSettingsPanel()
{
	delete mpUi;
}


void SerialSettingsPanel::updateAvailableSerialPorts()
{

	// Adding or removing items activates currentIndexChanged. Prevent.
	this->blockSignals(true);

	// remove all n items: when an item is removed its index is updated
	//                     ergo, remove item with index 0 n times

	while( mpUi->portSelectComboBox->count() != 0 )
	{
		mpUi->portSelectComboBox->removeItem(0);
	}


	QList<QSerialPortInfo> portList =  QSerialPortInfo::availablePorts();

	for (int iPortList = 0; iPortList < portList.size(); ++iPortList)
	{
		QSerialPortInfo portItem = portList.at( iPortList );

		QString portName        = portItem.portName();
		QString portDescription = portItem.description();

		QString portString = portName + QString(" - ") + portDescription;


		// A QComboBox allows each of its items to have a userData field (type QVariant)

		QVariant portNameToUserData( portName );

		mpUi->portSelectComboBox->addItem( portString, portNameToUserData );

	}

	this->blockSignals(false);

}

void SerialSettingsPanel::formatComboBoxPortName(const QString& itemText)
{

	// The item's text is a combination of portName and description (not useful)

	Q_UNUSED(itemText);

	// Each QComboBox' item can have a userData field.
	// currentData holds the userData of the currently selected item.

	QVariant currentItemUserData = mpUi->portSelectComboBox->currentData();

	QString  selectedPortName    = currentItemUserData.toString();

	QString  formattedPortName   = QString("\\\\.\\") + selectedPortName;

	emit comboBoxPortNameChanged(formattedPortName);

	// change the name of the port in status. if an error occurs it will be overwritten
	// by the error handling

	mpUi->portStatusTextEdit->setText( selectedPortName + QString(" is open.") );

}


void SerialSettingsPanel::on_portReloadPushButton_clicked()
{
	this->updateAvailableSerialPorts();
}

void SerialSettingsPanel::displaySerialWorkerError(QSerialPort::SerialPortError serialPortError)
{

	// Port emits NoError error on port change. Ignore

	if( serialPortError == QSerialPort::NoError )
	{
		return;
	}

	QString errorString = QString("unset");

	switch( serialPortError )
	{
		case QSerialPort::DeviceNotFoundError :
			errorString = "Master module was reset while port was open. Reboot the master device while it's disconnected or another port is selected and try again.";
		break;

		default:
			errorString = "An unknown error occurred. Try closing the application and rebooting the master device.";
		break;


	}

	qDebug() << serialPortError;

	mpUi->portStatusTextEdit->setText( errorString );

}
