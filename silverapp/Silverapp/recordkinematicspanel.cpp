#include "recordkinematicspanel.h"
#include "ui_recordkinematicspanel.h"

#include <QFileDialog>
#include <QDebug>
#include <QTime>
#include <QDate>
#include <QDateTime>
#include <QTimer>

#include <QMessageBox>

#define EIGEN_DONT_ALIGN_STATICALLY
#include <Eigen/Geometry>

#include "mainwindow.h"


RecordKinematicsPanel::RecordKinematicsPanel(QWidget *parent) :
	QPanel(parent),
	mpUi(new Ui::RecordKinematicsPanel)
{
	mpUi->setupUi(this);

	mpFile = new QFile();
	mpFile->setParent(this);

	QObject::connect(

				this, &RecordKinematicsPanel::panelOpened,
				this, &RecordKinematicsPanel::fillFilenameWithCurrentTime
	);

	mpMainWindow = qobject_cast<MainWindow*>( this->parent() );


	elapsedTimer.setParent(this);
	connect( &elapsedTimer, SIGNAL(timeout()), this, SLOT(updateElapsed()) );


	elapsedTimer.start(1000);


}

RecordKinematicsPanel::~RecordKinematicsPanel()
{
	delete mpUi;
}


/// Filename functions


// Select folder

void RecordKinematicsPanel::on_FolderButton_clicked()
{

	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::Directory);
	dialog.setOption(QFileDialog::ShowDirsOnly, true);
	dialog.setDirectory("D:/");

	if( dialog.exec() )
	{
		 QString fileName = dialog.selectedFiles().at(0);
		 mpUi->FolderLineEdit->setText( fileName );
	}

}



// Join dir and filename fields

QString RecordKinematicsPanel::getPathToFile()
{
	QString chosenFolder = mpUi->FolderLineEdit->text();
	QString fileToCheck  = mpUi->FileLineEdit->text();

	QString pathToFile = chosenFolder + fileToCheck;

	return pathToFile;

}

// Check if filename exists in filesystem.

bool RecordKinematicsPanel::currentFilenameExists()
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

void RecordKinematicsPanel::updateFileStatusText()
{
	if( this->currentFilenameExists() )
	{
		mpUi->FileStatus->setText("Warning: File already exists!");
	}
	else
	{
		mpUi->FileStatus->setText("");
	}
}


// Auto generate a filename based on date+time

void RecordKinematicsPanel::fillFilenameWithCurrentTime()
{
	// Use date and time to suggest a filename

	QDate currentDate = QDate::currentDate();
	QString currDateStr = currentDate.toString("yyyyMMdd");

	QTime currentTime = QTime::currentTime();
	QString currTimeStr = currentTime.toString("hhmmss");

	QString fileLineEditStr = currDateStr + "-" + currTimeStr + ".kimu";

	mpUi->FileLineEdit->setText( fileLineEditStr );

	this->updateFileStatusText();

}


// Generate a filename manually

void RecordKinematicsPanel::on_FileButton_clicked()
{
	this->fillFilenameWithCurrentTime();
}


// Each time the user types check whether file already exists.

void RecordKinematicsPanel::on_FileLineEdit_textChanged(const QString &arg1)
{
	Q_UNUSED(arg1);
	this->updateFileStatusText();
}


/// Main recording actions

void RecordKinematicsPanel::on_RecordButton_clicked()
{

	// mRecording is a flag to be cleared only when all the file
	// operations are done. It is set false in the fx that
	// handles the incoming data (as explained in the next paragraph).

	// mFinalizeRecording is read by the loop that prints the incoming
	// sensor data to a file. It signals that the protocol to finish
	// reading a file must be executed: Closes the file, clears the
	// buffer, sets mRecording = false and disconnects the signals
	// and slots that send new data.

	if( !mRecording )
	{
		mRecording = true;

		this->setupRecording();
		mFinalizeRecording = false;

	}
	else
	{
		mFinalizeRecording = true;
	}
}


void RecordKinematicsPanel::setupRecording()
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
	mpUi->RecordButton->setText("Stop");

	mSecondsElapsed = 0;


	/// Write the references for compensation (.cimu)

	QString tempString = this->getPathToFile();

	tempString.chop(4); // remove extension
	tempString.append( QString("cimu") );

	mpFile->setFileName( tempString );


	if ( mpFile->open( QIODevice::WriteOnly | QIODevice::Truncate ) )
	{
		qDebug() << "Compensation file opened.";

		QTextStream streamout(mpFile);

		// title

		QString title("References for initial calibration - ");
		title.append( QDateTime::currentDateTime().toString() );
		title.append("\r\n");

		streamout << title;

		// headers

		streamout <<
									   "ID\t" <<
					  "                QuaW\t" <<
					  "                QuaX\t" <<
					  "                QuaY\t" <<
					  "                QuaZ"   <<
					  "\r\n";

		// data

		//virtual

		Eigen::Quaterniond VirtualQuat = mpMainWindow->getVirtualQuat();

		streamout << " 0\t";

		// Numeric settings
		streamout.setRealNumberNotation( QTextStream::FixedNotation );
		streamout.setPadChar(' ');

		int quaDataWidth     = 20;
		int quaDecimalPlaces = 17;

		streamout.setRealNumberPrecision(quaDecimalPlaces);

		//QuaW
		streamout.setFieldWidth(quaDataWidth);
		streamout << VirtualQuat.w();

		streamout.setFieldWidth(0); //space
		streamout << '\t';

		//QuaX
		streamout.setFieldWidth(quaDataWidth);
		streamout << VirtualQuat.x();

		streamout.setFieldWidth(0); //space
		streamout << '\t';

		//QuaY
		streamout.setFieldWidth(quaDataWidth);
		streamout << VirtualQuat.y();

		streamout.setFieldWidth(0); //space
		streamout << '\t';

		//QuaZ

		streamout.setFieldWidth(quaDataWidth);
		streamout << VirtualQuat.z();

		streamout.setFieldWidth(0);
		streamout << "\r\n";

		// references

		std::array< Eigen::Quaterniond, 7 > ReferenceQuats;
		ReferenceQuats = mpMainWindow->getReferenceQuats();

		for( int iQuat = 0 ; iQuat <= 6 ; ++iQuat )
		{

			streamout.setFieldWidth(2);
			streamout << QString::number(iQuat+1);

			streamout.setFieldWidth(0);
			streamout << "\t";

			//QuaW
			streamout.setFieldWidth(quaDataWidth);
			streamout << ReferenceQuats.at(iQuat).w();

			streamout.setFieldWidth(0); //space
			streamout << '\t';

			//QuaX
			streamout.setFieldWidth(quaDataWidth);
			streamout << ReferenceQuats.at(iQuat).x();

			streamout.setFieldWidth(0); //space
			streamout << '\t';

			//QuaY
			streamout.setFieldWidth(quaDataWidth);
			streamout << ReferenceQuats.at(iQuat).y();

			streamout.setFieldWidth(0); //space
			streamout << '\t';

			//QuaZ

			streamout.setFieldWidth(quaDataWidth);
			streamout << ReferenceQuats.at(iQuat).z();

			streamout.setFieldWidth(0);
			streamout << "\r\n";

		}


		streamout.flush(); // close the first file
		mpFile->close();

		qDebug() << "Compensation file closed.";

	}

	/// Stream for the kinematic data (.kimu)

	tempString.chop(4); // remove extension
	tempString.append( QString("kimu") );


	mpFile->setFileName( tempString );

	if ( mpFile->open( QIODevice::WriteOnly | QIODevice::Truncate ) )
	{

		qDebug() << "Kinematics file opened.";

		QTextStream streamout(mpFile);

		// title

		QString title("Live kinematic data - ");
		title.append( QDateTime::currentDateTime().toString() );
		title.append("\r\n");

		// header

		streamout <<
					"   Milli\t"<<
					"ID\t"<<
					"      Angle";

		mPrintRaw = false;
		mPrintSeg = false;
		mPrintJoi = false;

		if( mpUi->jointCheckBox->isChecked() )
		{

			mPrintJoi = true;

			streamout <<

					 "\t             JoiQuaW\t"<<
					 "             JoiQuaX\t"<<
					 "             JoiQuaY\t"<<
					 "             JoiQuaZ";

		}

		if( mpUi->segmentCheckBox->isChecked() )
		{

			mPrintSeg = true;

			streamout <<

					 "\t             SegQuaW\t"<<
					 "             SegQuaX\t"<<
					 "             SegQuaY\t"<<
					 "             SegQuaZ";
		}

		if ( mpUi->rawCheckBox->isChecked() )
		{

			mPrintRaw = true;

			streamout <<

					 "\t             RawQuaW\t"<<
					 "             RawQuaX\t"<<
					 "             RawQuaY\t"<<
					 "             RawQuaZ";
		}

		streamout << "\r\n";

		//-------------------------------------------
		// Connect incoming data
		//-------------------------------------------


		mConnectNewDataToFile = QObject::connect
		(
			mpMainWindow,            &MainWindow::kinematicsChanged,
					this, &RecordKinematicsPanel::writeSignalsToOpenFile
		);


		//------------------------------------------
		// Start timer
		//------------------------------------------

		mTimestamper.start();

	}

}


// Once connected by the record button, execute every time new data arrives

void RecordKinematicsPanel::writeSignalsToOpenFile
(
	const QVector<double>& sagittal_angles,
	const std::array< Eigen::Quaterniond,7> &quats_raw,
	const std::array< Eigen::Quaterniond,7> &quats_segments,
	const std::array< Eigen::Quaterniond,6> &quats_joints
)
{

	// Executes as long as the user doesn't push STOP
	QTextStream streamout(mpFile);

	int quaDataWidth     = 20;
	int quaDecimalPlaces = 17;

	int angleDataWidth     = 10;
	int angleDecimalPlaces = 5;

	int totalLoops = 7;


	// Skip final round if not printing raw/segments
	if( (!mPrintRaw) && (!mPrintSeg) )
	{
		--totalLoops;
	};


	for(int iLoop = 0 ; iLoop <= (totalLoops-1) ; ++iLoop )
	{
		// Timestamp

		streamout.setFieldWidth(8);
		streamout.setPadChar('0');
		streamout << mTimestamper.elapsed(); // consider nanoseconds

		streamout.setFieldWidth(0); //space
		streamout << '\t';

		// ID
		streamout.setFieldWidth(2);
		streamout << (iLoop + 1);

		streamout.setFieldWidth(0); //space
		streamout << '\t';

		// Numeric settings
		streamout.setRealNumberNotation( QTextStream::FixedNotation );
		streamout.setPadChar(' ');


		if( iLoop != 6 )
		{

			// Angle
			double angle  = sagittal_angles.at(iLoop);

			streamout.setFieldWidth(angleDataWidth);
			streamout.setRealNumberPrecision(angleDecimalPlaces);
			streamout << angle;

			// Joint
			if( mPrintJoi )
			{
				Eigen::Quaterniond JoiQuat = quats_joints.at(iLoop);
				streamout.setRealNumberPrecision(quaDecimalPlaces);

				streamout.setFieldWidth(0); //space
				streamout << '\t';

				//QuaW
				streamout.setFieldWidth(quaDataWidth);
				streamout << JoiQuat.w();

				streamout.setFieldWidth(0); //space
				streamout << '\t';

				//QuaX
				streamout.setFieldWidth(quaDataWidth);
				streamout << JoiQuat.x();

				streamout.setFieldWidth(0); //space
				streamout << '\t';

				//QuaY
				streamout.setFieldWidth(quaDataWidth);
				streamout << JoiQuat.y();

				streamout.setFieldWidth(0); //space
				streamout << '\t';

				//QuaZ

				streamout.setFieldWidth(quaDataWidth);
				streamout << JoiQuat.z();
			}

		}
		else // print nulls if on the 6th round to not mess up formatting
		{

			streamout.setFieldWidth(angleDataWidth);
			streamout << "----------";

			// Joint
			if( mPrintJoi )
			{
				for( int iJoi = 0 ; iJoi <= 3 ; ++iJoi)
				{
					streamout.setFieldWidth(0); //space
					streamout << '\t';

					streamout.setFieldWidth(quaDataWidth);
					streamout << "------------------";

					// TO-DO mirar las combinaciones si salen bien con todos los sensores prendidos

				}

			}

		}


		if( mPrintSeg )
		{

			Eigen::Quaterniond SegQuat = quats_segments.at(iLoop);
			streamout.setRealNumberPrecision(quaDecimalPlaces);

			streamout.setFieldWidth(0); //space
			streamout << '\t';

			//QuaW
			streamout.setFieldWidth(quaDataWidth);
			streamout << SegQuat.w();

			streamout.setFieldWidth(0); //space
			streamout << '\t';

			//QuaX
			streamout.setFieldWidth(quaDataWidth);
			streamout << SegQuat.x();

			streamout.setFieldWidth(0); //space
			streamout << '\t';

			//QuaY
			streamout.setFieldWidth(quaDataWidth);
			streamout << SegQuat.y();

			streamout.setFieldWidth(0); //space
			streamout << '\t';

			//QuaZ

			streamout.setFieldWidth(quaDataWidth);
			streamout << SegQuat.z();


		}

		if( mPrintRaw )
		{

			Eigen::Quaterniond RawQuat = quats_raw.at(iLoop);
			streamout.setRealNumberPrecision(quaDecimalPlaces);

			streamout.setFieldWidth(0); //space
			streamout << '\t';

			//QuaW
			streamout.setFieldWidth(quaDataWidth);
			streamout << RawQuat.w();

			streamout.setFieldWidth(0); //space
			streamout << '\t';

			//QuaX
			streamout.setFieldWidth(quaDataWidth);
			streamout << RawQuat.x();

			streamout.setFieldWidth(0); //space
			streamout << '\t';

			//QuaY
			streamout.setFieldWidth(quaDataWidth);
			streamout << RawQuat.y();

			streamout.setFieldWidth(0); //space
			streamout << '\t';

			//QuaZ

			streamout.setFieldWidth(quaDataWidth);
			streamout << RawQuat.z();

		}

		streamout.setFieldWidth(0); //space
		streamout << "\r\n";

	}

	if( mFinalizeRecording == true )
	{

		streamout.flush(); // flush the buffer!

		QObject::disconnect( mConnectNewDataToFile );
		mpFile->close();

		qDebug() << "Kinematics file closed.";

		mpUi->RecordButton->setText("Record");
		mpUi->ElapsedTimeLabel->setText( QString::number(0) );

		mRecording = false;

	}


}


void RecordKinematicsPanel::updateElapsed()
{

	if( mRecording )
	{
		++mSecondsElapsed;
		mpUi->ElapsedTimeLabel->setText( QString::number(mSecondsElapsed) );
	}


}
