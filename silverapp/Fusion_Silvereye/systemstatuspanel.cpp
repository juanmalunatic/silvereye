#include "systemstatuspanel.h"
#include "ui_systemstatuspanel.h"


#include "cmath"

#include "imudata.h"
#include "mainwindow.h"
#include "qpanel.h"



#include <QDebug>

SystemStatusPanel::SystemStatusPanel(QWidget *parent) :

	QPanel(parent), // Qt::Window in QPanel
	mUi(new Ui::SystemStatusPanel)

{

	// Defaultui setup

	mUi->setupUi(this);

	//qDebug() << this;

	// Assign the QLabels to pointers with a loop
	for( int i = 0 ; i <= (MainWindow::TOTAL_SENSORS-1) ; i++ )
	{

		//  std::array<DataRow, MainWindow::TOTAL_SENSORS> RowPointers;
		/*
			QLabel* id;
			QLabel* status;
			QLabel* battery;
			QLabel* calibS;
			QLabel* calibG;
			QLabel* calibA;
			QLabel* calibM;
		*/

		// Format a string with the loop variable as prefix: S1, S2, etc.
		// %1 should be seen as a command line argument: "explorer.exe %1 %2"

		QString prefix = QString("S%1").arg(i+1);

		// Find the pointers based on prefix and suffix and store in array
		// S1 + calibA, S1 + calibM, etc.

		mRowPointers[i].id      = this->findChild<QLabel*>( prefix + QString("id"    ) );

		mRowPointers[i].status  = this->findChild<QLabel*>( prefix + QString("status") );
		mRowPointers[i].battery = this->findChild<QLabel*>( prefix + QString("bat"   ) );

		mRowPointers[i].calibS  = this->findChild<QLabel*>( prefix + QString("calibS") );
		mRowPointers[i].calibG  = this->findChild<QLabel*>( prefix + QString("calibG") );
		mRowPointers[i].calibA  = this->findChild<QLabel*>( prefix + QString("calibA") );
		mRowPointers[i].calibM  = this->findChild<QLabel*>( prefix + QString("calibM") );


	}


}

SystemStatusPanel::~SystemStatusPanel()
{

	// delete this object
	delete mUi;

	qDebug() << "SystemStatusPanel destructor";
}


void SystemStatusPanel::refreshWithNewSensorData(const std::array<ImuData,7>& newData)
{
	// We reach this point when MainWindow tells us theres new data for the 7 sensors
	//real


	// When the gui is locked (action performed like drag a window), events are queued
	// (so there's no data loss). In these cases this timer is fired in succession
	// giving an elapsed time of 0.

	qint64 elapsedMsSinceLastUpdate = mMsTimer.elapsed();


	if( elapsedMsSinceLastUpdate == 0 )
	{
		elapsedMsSinceLastUpdate = mFreqAvg; // Use previous values
	}

	double frequency = 1000.0 / elapsedMsSinceLastUpdate; // we time the reading block (7 sensors)
														  // 7*1.4 = ~10ms
														  // 1000 ms/10ms = 100 Hz
	//debug
	//double frequency = mMsTimer.elapsed();


	// Nice moving average
	// http://stackoverflow.com/questions/12636613/how-to-calculate-moving-average-without-keeping-the-count-and-data-total

	qint64 N = 100; // number of elements to average

	mFreqAvg -= mFreqAvg/N;
	mFreqAvg += frequency/N;

	/*if( std::isnan(mFreqAvg) )
	{
		//debug
	}*/


	if( mMsTimer.isValid() ) // If it has been started before
	{
		mUi->FrameRateValue->setText( QString("%1 Hz").arg(mFreqAvg) );
	}

	mMsTimer.start(); // Time next round

	//Initial version
	/*for( int i = 0 ; i <= (MainWindow::TOTAL_SENSORS-1) ; i++ )
	{

		QString prefix = QString("S%1").arg(i+1); // Format S1, S2, etc
		// Monster syntax lel
		// TO-DO Improve: store ptrs somewhere and just loop them

		this->findChild<QLabel*>(prefix+QString("calibA"))->setText(

			QString::number( (int) newSensorDataArray[i].callibration.acc )

		);


	}*/

	// Loop through all the stored pointers
	// and set text to the updated data

	QString status_on  = "On";
	QString status_off = "Off";

	for( int i=0 ; i <= (MainWindow::TOTAL_SENSORS-1) ; i++ )
	{

		// Status

		if( (int)newData[i].online )
		{
			mRowPointers[i].status  -> setText( status_on );
			mRowPointers[i].status  -> setStyleSheet("QLabel { color : green; }");

		}
		else
		{
			mRowPointers[i].status  -> setText( status_off );
			mRowPointers[i].status  -> setStyleSheet("QLabel { color : red; }");
		}

		// Battery


		// Batt %  |  0*  14  29  43  57  71  86 100
		// Mapping | 000 001 010 011 100 101 110 111
		//             0   1   2   3   4   5   6   7
		//
		// y = 14.28571 x +0

		double bat_level = 14.28571 * (int)newData[i].battery;

		mRowPointers[i].battery -> setText( QString::number( bat_level, 'f', 0  ) );


		// Other fields

		mRowPointers[i].id      -> setText( QString::number( (int)newData[i].id      ) );

		mRowPointers[i].calibS  -> setText( QString::number( (int)newData[i].callibration.system ) );
		mRowPointers[i].calibG  -> setText( QString::number( (int)newData[i].callibration.gyr    ) );
		mRowPointers[i].calibA  -> setText( QString::number( (int)newData[i].callibration.acc    ) );
		mRowPointers[i].calibM  -> setText( QString::number( (int)newData[i].callibration.mag    ) );


	}


}
