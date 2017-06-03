#ifndef SERIALSETTINGSPANEL_H
#define SERIALSETTINGSPANEL_H

#include <QWidget>
#include <QSerialPort>

#include "serialworker.h"
#include "qpanel.h"

namespace Ui {
	class SerialSettingsPanel;
}

class SerialSettingsPanel : public QPanel
{
	Q_OBJECT

public:
	explicit SerialSettingsPanel(QWidget *parent = 0);
	~SerialSettingsPanel();

private:

	Ui::SerialSettingsPanel *mpUi;

	SerialWorker *mpRemoteSerialWorker;

	void updateAvailableSerialPorts();

signals:

	void comboBoxPortNameChanged(const QString& portNameToSwitchTo);

private slots:

	void formatComboBoxPortName(const QString& itemText);

	void displaySerialWorkerError(QSerialPort::SerialPortError serialPortError);

	//reload port list
	void on_portReloadPushButton_clicked();





};

#endif // SERIALSETTINGSPANEL_H
