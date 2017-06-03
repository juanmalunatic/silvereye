#ifndef SYSTEMSTATUSPANEL_H
#define SYSTEMSTATUSPANEL_H

#include <QWidget>
#include <QLabel>
#include <QElapsedTimer>
#include <array>

#include "qpanel.h"
#include "imudata.h"

// Namespace

namespace Ui
{
	class SystemStatusPanel;
}


// Structs

struct DataRow
{
	QLabel* id;
	QLabel* status;
	QLabel* battery;
	QLabel* calibS;
	QLabel* calibG;
	QLabel* calibA;
	QLabel* calibM;

};

// Class

class SystemStatusPanel : public QPanel
{

	Q_OBJECT

public:

	explicit SystemStatusPanel(QWidget *parent = 0);
	~SystemStatusPanel();

	// Window control
	bool mVisible = false;
	//void closeEvent(QCloseEvent *event);


private:

	Ui::SystemStatusPanel *mUi;

	// GUI elements

	// Structs with pointers to the GUI items
	// (each SX is a row, and has 7 child QLabel)

	//Array with 7 elements
	// how to use MainWindow::totalSensors?
	std::array<DataRow, 7> mRowPointers;

	// Frequency calculation
	QElapsedTimer mMsTimer;
	double mFreqAvg = 10;

signals:

	// Closing notification is implemented in QPanel


public slots:

	void refreshWithNewSensorData(const std::array<ImuData,7>& newData);



};

#endif // SYSTEMSTATUSPANEL_H
