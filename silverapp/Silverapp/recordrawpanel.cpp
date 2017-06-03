/*

// TO-DO(?) rewrite connection and disconnection from MainWindow (Not a priority)

Recording panel doesn't use the QPanel schema:
Its connection to the data source is triggered by a button on its own GUI.

Connection to data source       RecordingPanel::setupRecording()
Disconnection from data source  RecordingPanel::writeNewSensorDataToFile()

*/

#include "recordrawpanel.h"
#include "ui_recordrawpanel.h"

#include "mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include <QTime>
#include <QDate>

#include <QMessageBox>

RecordRawPanel::RecordRawPanel(QWidget *parent) :
	QWidget(parent, Qt::Window),
	mUi(new Ui::RecordRawPanel)
{
	mUi->setupUi(this);

	mpFile = new QFile();
	mpFile->setParent(this);


	// Window shown with a GUI press in MainWindow
	// Filename filled with current time on show


}

RecordRawPanel::~RecordRawPanel()
{
	delete mUi;

	qDebug() << "RecordRawPanel destructor.";
}


//----------------------------------------------------
// GUI init
//----------------------------------------------------


// Select folder

void RecordRawPanel::on_FolderButton_clicked()
{

	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::Directory);
	dialog.setOption(QFileDialog::ShowDirsOnly, true);
	dialog.setDirectory("D:/");

	if( dialog.exec() )
	{
		 QString fileName = dialog.selectedFiles().at(0);
		 mUi->FolderLineEdit->setText( fileName );
	}

}

// Auto generate a filename based on date+time

void RecordRawPanel::fillFilenameWithCurrentTime()
{
	// Use date and time to suggest a filename

	QDate currentDate = QDate::currentDate();
	QString currDateStr = currentDate.toString("yyyyMMdd");

	QTime currentTime = QTime::currentTime();
	QString currTimeStr = currentTime.toString("hhmmss");

	QString fileLineEditStr = currDateStr + "-" + currTimeStr + ".gimu";

	mUi->FileLineEdit->setText( fileLineEditStr );

	this->updateFileStatusText();
}

// Join dir and filename fields

QString RecordRawPanel::getPathToFile()
{
	QString chosenFolder = mUi->FolderLineEdit->text();
	QString fileToCheck  = mUi->FileLineEdit->text();

	QString pathToFile = chosenFolder+fileToCheck;

	return pathToFile;

}

// Check if filename exists in filesystem.

bool RecordRawPanel::currentFilenameExists()
{

	QFile fileTmp( this->getPathToFile() );

	// Show a warning if file exists

	if( fileTmp.exists() )
	{
		return true;

	}
	else
	{
		return false;

	}
}

// Warn the user about existing file

void RecordRawPanel::updateFileStatusText()
{
	if( this->currentFilenameExists() )
	{
		mUi->FileStatus->setText("Warning: File already exists!");
	}
	else
	{
		mUi->FileStatus->setText("");
	}
}

// Generate a filename manually

void RecordRawPanel::on_FileButton_clicked()
{
	this->fillFilenameWithCurrentTime();
}

// Each time the user types check whether file already exists.

void RecordRawPanel::on_FileLineEdit_textChanged(const QString &arg1)
{
	Q_UNUSED(arg1);
	this->updateFileStatusText();
}


//-----------------------------------------------
// Main recording actions
//-----------------------------------------------

void RecordRawPanel::on_RecordButton_clicked()
{

	// mRecording is a flag to be cleared only when all the file
	// operations are done. It is set false in the fx that
	// handles the incoming data (as explained in the next paragraph).

	// mFinalizeRecording is read by the loop that prints the incoming
	// sensor data to a file (writeNewSensorDataToFile). It signals that
	// the protocol to finish reading a file must be executed:
	// Closes the file, clears the buffer, sets mRecording = false
	// and disconnects the signals and slots that send new data.

	if( !mRecording )
	{
		mRecording = true;

		this->setUpRecording();
		mFinalizeRecording = false;
	}
	else
	{
		mFinalizeRecording = true;
	}
}


void RecordRawPanel::setUpRecording()
{
	// First, check whether the filename is valid
	// If the file already exists, send a last warning

	if( this->currentFilenameExists() )
	{
		QMessageBox::StandardButton reply;

		reply = QMessageBox::question(
			this,
			"Warning!",
			"The specified file already exists. Overwrite it?",
			QMessageBox::Yes | QMessageBox::No
		);

		if (reply == QMessageBox::No)
		{
			mRecording = false;

			// Exit
			return;

		}

	}

	// If we continue, it means we're either overwriting
	// or creating the file.

	// Change the button text
	mUi->RecordButton->setText("Stop");

	//-------------------------------------------
	// Set up file handlers
	//-------------------------------------------

	mpFile->setFileName( this->getPathToFile() );

	// Open the file

	if ( mpFile->open( QIODevice::WriteOnly | QIODevice::Truncate ) )
	{

		qDebug() << "File opened by RecordRawPanel";
		qDebug() << mpFile;

		//-------------------------------------------
		// Create column formatting
		//-------------------------------------------

		QTextStream streamout(mpFile);

		// Enable whitespace display to see the underlying structure

		streamout <<

			"  Milli\t" <<
			"ID\t"     <<

			"   AccX\t" <<
			"   AccY\t" <<
			"   AccZ\t" <<

			"      MagX\t" <<
			"      MagY\t" <<
			"      MagZ\t" <<

			"               GyrX\t" <<
			"               GyrY\t" <<
			"               GyrZ\t" <<

			"             QuaW\t" <<
			"             QuaX\t" <<
			"             QuaY\t" <<
			"             QuaZ\r\n";

		//-------------------------------------------
		// Connect incoming data
		//-------------------------------------------

		// Connect signal from MainWindow to slot
		// Parent MUST always be MainWindow!
		// Also if I could write good C++ I'd use static_cast or dynamic_cast :^)

		mConnectNewDataToFile = QObject::connect
		(
			(const MainWindow*) this->parent(),     &MainWindow::sensorDataChanged,
										  this, &RecordRawPanel::streamDataToOpenFile
		);

		// In this case an event in the children widget triggers the connection
		// in SystemStatus the trigger is, in contrast, a MainWindow button.


		//------------------------------------------
		// Start timer
		//------------------------------------------

		mTimestamper.start();

	}


}

// Once connected by the record button, execute each time new data arrives

void RecordRawPanel::streamDataToOpenFile(const std::array<ImuData, 7> &newData)
{

	// Executes as long as the user doesn't push STOP

	QTextStream streamout(mpFile);

	// Use some variables

	int accDataWidth     =  7;
	int accDecimalPlaces =  2;

	int magDataWidth     = 10;
	int magDecimalPlaces =  4;

	int gyrDataWidth     = 19;
	int gyrDecimalPlaces = 15;

	int quaDataWidth     = 17;
	int quaDecimalPlaces = 14;

	// Loop through the 7 sensors

	for( int iSensor = 0; iSensor <= 6 ; iSensor++ )
	{

		//----------------------------------
		// Print
		//----------------------------------


		// Timestamp

		streamout.setFieldWidth(7);
		streamout.setPadChar('0');
		streamout << mTimestamper.elapsed(); // consider nanoseconds

		streamout.setFieldWidth(0); //space
		streamout << '\t';

		// ID
		streamout.setFieldWidth(2);
		streamout << newData[iSensor].id;

		streamout.setFieldWidth(0); //space
		streamout << '\t';

		// Numeric settings

		streamout.setRealNumberNotation( QTextStream::FixedNotation );
		streamout.setPadChar(' ');

		//-------------------------
		// ACC
		//-------------------------

		streamout.setRealNumberPrecision(accDecimalPlaces);

		// AccX
		streamout.setFieldWidth(accDataWidth);
		streamout << newData[iSensor].accelerometer.x;

		streamout.setFieldWidth(0); //space
		streamout << '\t';

		// AccY
		streamout.setFieldWidth(accDataWidth);
		streamout << newData[iSensor].accelerometer.y;

		streamout.setFieldWidth(0); //space
		streamout << '\t';

		// AccZ
		streamout.setFieldWidth(accDataWidth);
		streamout << newData[iSensor].accelerometer.z;

		streamout.setFieldWidth(0); //space
		streamout << '\t';

		//-------------------------
		// MAG
		//-------------------------

		streamout.setRealNumberPrecision(magDecimalPlaces);

		//MagX
		streamout.setFieldWidth(magDataWidth);
		streamout << newData[iSensor].magnetometer.x;

		streamout.setFieldWidth(0); //space
		streamout << '\t';

		//MagY
		streamout.setFieldWidth(magDataWidth);
		streamout << newData[iSensor].magnetometer.y;

		streamout.setFieldWidth(0); //space
		streamout << '\t';

		//MagZ
		streamout.setFieldWidth(magDataWidth);
		streamout << newData[iSensor].magnetometer.z;

		streamout.setFieldWidth(0); //space
		streamout << '\t';

		//-------------------------
		// GYR
		//-------------------------

		streamout.setRealNumberPrecision(gyrDecimalPlaces);

		//GyrX
		streamout.setFieldWidth(gyrDataWidth);
		streamout << newData[iSensor].gyroscope.x;

		streamout.setFieldWidth(0); //space
		streamout << '\t';

		//GyrY
		streamout.setFieldWidth(gyrDataWidth);
		streamout << newData[iSensor].gyroscope.y;

		streamout.setFieldWidth(0); //space
		streamout << '\t';

		//GyrZ
		streamout.setFieldWidth(gyrDataWidth);
		streamout << newData[iSensor].gyroscope.z;

		streamout.setFieldWidth(0); //space
		streamout << '\t';


		//-------------------------------
		// Quat
		//-------------------------------

		streamout.setRealNumberPrecision(quaDecimalPlaces);

		//QuaW
		streamout.setFieldWidth(quaDataWidth);
		streamout << newData[iSensor].quaternion.w;

		streamout.setFieldWidth(0); //space
		streamout << '\t';

		//QuaX
		streamout.setFieldWidth(quaDataWidth);
		streamout << newData[iSensor].quaternion.x;

		streamout.setFieldWidth(0); //space
		streamout << '\t';

		//QuaY
		streamout.setFieldWidth(quaDataWidth);
		streamout << newData[iSensor].quaternion.y;

		streamout.setFieldWidth(0); //space
		streamout << '\t';

		//QuaZ

		streamout.setFieldWidth(quaDataWidth);
		streamout << newData[iSensor].quaternion.z;

		streamout << "\r\n";

	} // end loop

	// When the button is pushed again
	// finalize the recording

	if( mFinalizeRecording == true )
	{

		// streamout << "bye nenitas" << endl;

		streamout.flush(); // flush the buffer!

		QObject::disconnect( mConnectNewDataToFile );
		mpFile->close();

		mUi->RecordButton->setText("Record");
		mRecording = false;

	}

}
