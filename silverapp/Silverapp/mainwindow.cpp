#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QThread>
#include <QTimer>
#include <QDebug>
#include <QtSerialPort/QSerialPort>

#include "serialthread.h"
#include "serialworker.h"
#include "recordrawpanel.h"
#include "serialsettingspanel.h"
#include "modelcalibrationpanel.h"
#include "sagittalanglespanel.h"

#include "ogre3d_userlib/qtogrewindow.h"
#include "humanmodelpanel.h"

#include "quaternion2euler.h"
#include "anglewrap.h"

#include <stdint.h>



// Eigen stuff

#ifndef EIGEN_PI
	#define EIGEN_PI 3.14159265358979323846
#endif

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

#define EIGEN_DONT_ALIGN_STATICALLY
#include <Eigen/Geometry>
#include <unsupported/Eigen/EulerAngles>


MainWindow::MainWindow(QWidget *parent) :

	QMainWindow(parent),
	mUi(new Ui::MainWindow),  // <--Initialization list
	mSerialThread(this)

{
	/// Constructor

	mUi->setupUi(this);                    // Config

	// Register types as metadata (to use them as arguments in signals/slots)
	qRegisterMetaType<ImuData>("ImuData");
	qRegisterMetaType<QSerialPort::SerialPortError>("QSerialPort::SerialPortError");
	qRegisterMetaType<Eigen::Quaterniond>("Eigen::Quaterniond");

	/// Main actions

	// Initialize complex variables

	this->initializeComplexVariables();

	// Set up a COM port controller on a separate thread and make it emit new data as a signal.

	this->serialThreadStart();

	// Panels are QWidgets that turn off their processing while hidden

	this->panelsInstantiate();

	// Quaternion algorithms setup

	this->quaternionCalcsConnect();

	// Use mainwindows as an observer to interconnect panels

	this->panelsInterconnect();



}

MainWindow::~MainWindow()
{

	delete mUi; // Delete UI.
	delete mpHumanModelPanel; // Else it won't be freed, somehow.

}


void MainWindow::closeEvent( QCloseEvent *evt )
{
	Q_UNUSED( evt );
	mpHumanModelPanel->close(); // needed to exit
	qDebug() << "Error en el puerto serial.";

}

/*---------------------------------------------------------------------
*                 Set up serial worker and threading
*----------------------------------------------------------------------
*
* mpSerialControl handles the COM port and runs in a non-GUI thread.
*
* Every new serial transaction emits sendSerialData(ByteArray)
*--------------------------------------------------------------------*/

void MainWindow::serialThreadStart()
{

	// Port settings are managed internally in SerialWorker

	mSerialRounds   = 0; // Count serial transactions and update the imuData array every time 7 have occured.

	mSerialWorker.moveToThread( &mSerialThread );           // Move the controller to the dataThread

	mSerialWorker.mSerialPort.moveToThread(&mSerialThread); // Also move the internal serial port object

	mSerialWorker.connectInternalSignals();       // Reconnect Worker to SerialPort after thread change
												  // Moving the attached serial port no longer needed

	//Assign signals&slots before thread start.

	QObject::connect
	(
		 &mSerialWorker, &SerialWorker::serialDataArrived,
				   this,   &MainWindow::processSerialData
	);

	mSerialThread.start(); // This starts the EventLoop on the thread.
						   // Until the thread is started, no event loop will take place.
						   // When started, internal connections of SerialWorker will start the signal updating

	// Destruction is handled automatically:
	//   SerialThread is killed on close (child of mainwindow on init list)
	//   SerialWorker is a member, also destroyed on window destruction (even if its in other thread)

}

/*---------------------------------------------------------------------
* SLOT processSerialData
*
* mpSerialControl, which lives in other thread, emits a signal con-
* taining new serial data. Qt's Signal&Slots mechanism ensures that,
* access to shared data is serialized (queued connections are used).
*
* Signal sendCurrentSensorData is emitted afer data for 7 sensors
* has been acquired (which takes around 10 ms at 100 Hz). This signal
* broadcasts the latest formatted data of the 7 sensors.
*
* mSerialRounds is used to ensure a full round of sensor's output
* was acquired.
* ---------------------------------------------------------------------*/

void MainWindow::processSerialData(const QByteArray& newSensorData)
{

	/*-----------------------------------------------------------------
	* decodeFrame: convert binary data to ImuData object
	* constData(): pointer to the const char* data (of QByteArray)
	* payload size is always 30 at this point
	*
	* checking signature prevents reading garbage
	* -----------------------------------------------------------------*/

	ImuData formattedData; // Create a ImuData placeholder
	bool    validSignature = decodeFrame( newSensorData.constData(), 30 , &formattedData );

	if( !validSignature ) //
	{
		// TO-DO: Report this in serial config panel
		qDebug() << "Invalid signature. Check serial output.";
		return;
	}

	// Refers to sensor list where 0 = hip, 1 = rthigh, etc

	int iSensor = formattedData.id - 1; // Incoming IDs are 1-7

	mSensorDataUnsynced[ iSensor ] = formattedData;

	Eigen::Quaterniond currentQuat = Eigen::Quaterniond(

		formattedData.quaternion.w,
		formattedData.quaternion.x,
		formattedData.quaternion.y,
		formattedData.quaternion.z
	);

	// If the received data was invalid, use the previous correct reading
	if( ! formattedData.online )
	{
		currentQuat = mRawQuatsFallback[ iSensor ];
	}
	else // Also, if the data was valid, store it in the "fallback" buffer for further use
	{
		// Note that the fallback quats are not guaranteed to be from the last round
		mRawQuatsFallback[ iSensor ] = currentQuat;
	}


	mRawQuatsUnsynced[ iSensor ] = currentQuat;

	if( mSerialRounds != (MainWindow::TOTAL_SENSORS - 1) ) // Update sensorData when all 7 sensors have been read
	{
		++mSerialRounds;
	}
	else
	{

		// Although data from several sensors is now synced, naming
		// reminds not to use the members directly: use signal arguments instead.

		mQ_sensors_raw = mRawQuatsUnsynced; // Store the synced data in the member

		emit sensorDataChanged    ( mSensorDataUnsynced );
		emit quaternionDataChanged( mRawQuatsUnsynced   );

		mSerialRounds = 0;

	}

	// DEBUG

/*
	if( formattedData.id == 1)
	{
		qDebug() << "Id:" << formattedData.id;
		// Acc
		qDebug() << "AX: " << formattedData.accelerometer.x << " AY: " << formattedData.accelerometer.y << " AZ: " << formattedData.accelerometer.z ;
		// Mag
		qDebug() << "MX: " << formattedData.magnetometer.x << " MY: " << formattedData.magnetometer.y << " MZ: " << formattedData.magnetometer.z;
		// Gyr
		qDebug() << "GX: " << formattedData.gyroscope.x << " GY: " << formattedData.gyroscope.y << " GZ: " << formattedData.gyroscope.z;
		// Qua
		qDebug() << "qW: " << formattedData.quaternion.w << "qX: " << formattedData.quaternion.x << "qY: " << formattedData.quaternion.y << "qZ: " << formattedData.quaternion.z;
		// Calib
		qDebug() << "CALIBRATION: Sys=" << formattedData.callibration.system << " Gyro=" << formattedData.callibration.gyr << "Accel= " << formattedData.callibration.acc << "Mag= " << formattedData.callibration.mag;
		//Hex
		qDebug() << newSensorData.toHex();
	}
*/

}


SerialWorker* MainWindow::getSerialWorker()
{
	return &mSerialWorker;
}


// --------------------------------------------------------------------
///                       QPanel management
// --------------------------------------------------------------------

/* QPanel: QWidget that stores a connection internally and emits a signal
		when it has been closed.

MainWindow manages QPanel so that it's disconnected from a data source
(signal) while hidden and connected when visible with the following
methods.

Instantiation: panelsInstantiate
Set-up       : on_panelName_clicked()     (see SystemStatus below )

*/

void MainWindow::panelsInstantiate()
{
	// "this" sets MainWindow as parent: auto memory cleanup on close

	mpSystemStatusPanel     = new SystemStatusPanel(this);
	mpSerialSettingsPanel   = new SerialSettingsPanel(this);
	mpModelCalibrationPanel = new ModelCalibrationPanel(this);
	mpRecordRawPanel        = new RecordRawPanel(this);
	mpHumanModelPanel       = new HumanModelPanel(this);
    mpSagittalAnglesPanel   = new SagittalAnglesPanel(this);
	mpRecordKinematicsPanel = new RecordKinematicsPanel(this);

	//DBG
    // mpHumanModelPanel->show();
	// mpSagittalAnglesPanel->show();


	// Default positions

                     this->move(0,0);
        mpHumanModelPanel->setPosition(210,35);
    mpSagittalAnglesPanel->move(620,0);
    mpModelCalibrationPanel->move(520,100);


}

// Generic handling functions

// SLOT: Disconnect a panel from its data feed and hide it.
void MainWindow::disconnectPanel(QPanel * pPanel)
{
	QObject::disconnect( pPanel->getConnectionToMainWindow() );
	pPanel->hide();
	pPanel->setVisible(false);
}

void MainWindow::panelSetupDisconnectionAndShow(QPanel* pPanel, QMetaObject::Connection newConnection)
{
	// Store connection to have it auto disconnected by PanelDisconnect
	pPanel->setConnectionToMainWindow( newConnection );
	pPanel->show();
	pPanel->setVisible(true);

	// Disconnect signal when panel gets closed
	QObject::connect
	(
		pPanel,     &QPanel::panelClosed,
		  this, &MainWindow::disconnectPanel
	);
}

// --------------------------------------------------------------------
///          GUI button events + QPanel connection setup
// --------------------------------------------------------------------

/* --------------------------------------------------------------------
* Events for the MainWindow elements. Each method corresponds to a
* button (which in turn corresponds to one panel).
*-------------------------------------------------------------------*/


void MainWindow::on_systemStatusButton_clicked()
{
	if( mpSystemStatusPanel->isVisible() ) return;

	QMetaObject::Connection MainWindowToSystemStatus = QObject::connect(

					  this,        &MainWindow::sensorDataChanged,
	   mpSystemStatusPanel, &SystemStatusPanel::refreshWithNewSensorData

	);

	panelSetupDisconnectionAndShow( mpSystemStatusPanel , MainWindowToSystemStatus );

}

// Doesn't use QPanel!!
void MainWindow::on_recordRawButton_clicked()
{
	mpRecordRawPanel->show();
	mpRecordRawPanel->fillFilenameWithCurrentTime();
}

// Doesn't have a data feed
void MainWindow::on_serialSettingsButton_clicked()
{
	mpSerialSettingsPanel->show();
}

void MainWindow::on_modelCalibrationButton_clicked()
{


	if( mpModelCalibrationPanel->isVisible() ) return;

	QMetaObject::Connection MainWindowToCalibrationPanel = QObject::connect(

					  this,                &MainWindow::quaternionDataChanged,
	   mpModelCalibrationPanel, &ModelCalibrationPanel::updateReferences

	);

	panelSetupDisconnectionAndShow( mpModelCalibrationPanel , MainWindowToCalibrationPanel );


}

void MainWindow::on_humanModelButton_clicked()
{

	if( mpHumanModelPanel->isVisible() ) return;

	QMetaObject::Connection MainWindowToHumanModelPanel = QObject::connect(

					 this,      &MainWindow::segmentsAndJointsChanged,
		mpHumanModelPanel, &HumanModelPanel::updateModel
	);

	mpHumanModelPanel->setConnectionToMainWindow( MainWindowToHumanModelPanel );

	// MÉTODOS DEBUG
	/*
	QObject::connect(

					 this,      &MainWindow::debugCalibration,
		mpHumanModelPanel, &HumanModelPanel::debugCalibration
	);
	*/

	mpHumanModelPanel->show();

}

void MainWindow::on_sagittalAnglesButton_clicked()
{

	if( mpSagittalAnglesPanel->isVisible() ) return;

	QMetaObject::Connection MainWindowToSagittalAnglesPanel = QObject::connect(

						 this,          &MainWindow::anglesChanged,
		mpSagittalAnglesPanel, &SagittalAnglesPanel::updatePlots

	);


	mpSagittalAnglesPanel->setConnectionToMainWindow( MainWindowToSagittalAnglesPanel );

	mpSagittalAnglesPanel->show();

}

void MainWindow::on_recordKinematicsButton_clicked()
{

	if( mpRecordKinematicsPanel->isVisible() ) return;

	// Connect from the children when the button is pressed

	/*
	QMetaObject::Connection MainWindowToRecordKinematicsPanel = QObject::connect(

						   this,            &MainWindow::kinematicsChanged,
		mpRecordKinematicsPanel, &RecordKinematicsPanel::writeSignalsToDisk

	);

	mpRecordKinematicsPanel->setConnectionToMainWindow( MainWindowToRecordKinematicsPanel );
	*/

	mpRecordKinematicsPanel->show();

}


//--------------------------------------------------------------------
/// Interconections between panels
//--------------------------------------------------------------------

/* --------------------------------------------------------------------
* Note that most of the connections are from MainWindow to a panel (han
* deled previously). There might be some interconnections in the panels
* themselves.
*--------------------------------------------------------------------*/

void MainWindow::panelsInterconnect()
{

	QObject::connect
	(
		mpModelCalibrationPanel, &ModelCalibrationPanel::viewportResetClicked,
			  mpHumanModelPanel, &HumanModelPanel::resetViewport
	);


	QObject::connect
	(
		mpModelCalibrationPanel, &ModelCalibrationPanel::viewportSagittalClicked,
			  mpHumanModelPanel, &HumanModelPanel::sagittalViewport
	);


}




// --------------------------------------------------------------------
///          Quaternions: underlying calculations
// --------------------------------------------------------------------



void MainWindow::quaternionCalcsConnect()
{
	// Init to default values

	Eigen::Quaterniond idenQuat = Eigen::Quaterniond(1,0,0,0);

	// Init all involved quats with the identity

	for(int iQuat = 0 ; iQuat <= (MainWindow::TOTAL_SENSORS-1) ; ++iQuat )
	{
		mQ_sensors_raw[iQuat] = idenQuat;
		mQ_segments   [iQuat] = idenQuat;
		mQ_sensors_ref[iQuat] = idenQuat;
		mQ_compensate [iQuat] = idenQuat;

		if( iQuat <= (MainWindow::TOTAL_JOINTS-1) )
		{
			mQ_joints[iQuat] = idenQuat;
		}

	}

	this->updateSegmentsAndJoints();

	// Although permanently connected, the panel will only
	// emit the signals while (a) it's open (b) there's incoming data
	// (c) the user clicks the corresponding buttons


	QObject::connect(

		mpModelCalibrationPanel, &ModelCalibrationPanel::compensationChanged,
						   this,		    &MainWindow::updateCompensation
	);

	QObject::connect(

		mpModelCalibrationPanel, &ModelCalibrationPanel::virtualOrientationChanged,
						   this,		    &MainWindow::updateVirtualOrientation
	);

	QObject::connect(

		mpModelCalibrationPanel, &ModelCalibrationPanel::initialSensorOrientationsChanged,
						   this,		    &MainWindow::updateInitialSensorOrientations
	);

	QObject::connect(
		this, &MainWindow::quaternionDataChanged,
		this, &MainWindow::updateSegmentsAndJoints
	);



	/*
	QObject::connect(
						 this,          &MainWindow::anglesChanged,
		mpSagittalAnglesPanel, &SagittalAnglesPanel::updatePlots
	);
	*/

}

void MainWindow::updateVirtualOrientation ( const Eigen::Quaterniond &Q_virtual_new )
{

	mQ_virtual = Q_virtual_new;

	this->updateLeftAndRightQuats();

	qDebug() << "Received: New virtual reference orientation.";
}

void MainWindow::updateInitialSensorOrientations ( const std::array<Eigen::Quaterniond,7> &Q_sensors_ref_new )
{

	// Values already normalized in modelCalibrationPanel.

	mQ_sensors_ref = Q_sensors_ref_new;

	// this->compensateRawQuats(mQ_sensors_ref);
	this->updateLeftAndRightQuats();

	qDebug() << "Received: New sensor mountings.";
}

void MainWindow::updateCompensation(const std::array<Eigen::Quaterniond, 7> &Q_compensate)
{

	mQ_compensate = Q_compensate;

	qDebug() << "Received: Compensation.";
}


void MainWindow::compensateRawQuats(std::array<Eigen::Quaterniond, 7> &inputQuats) //notice no const!
{

	// Compensation for initial unalignment

	for( int iC = 0 ; iC <= 6 ; ++iC )
	{
		Eigen::Quaterniond tempQ = mQ_compensate[iC] * inputQuats.at(iC);
		tempQ.normalize();

		inputQuats[iC] = tempQ;
	}

}
/*
-----------------------------------------------------------------------------------------------

Full equation for this sensor set (BNO055) and the chosen ISB coordinate frames is:

Q*_isb x ((Q*_virtual x ((Q_sensors_raw[i] x Q*_sensors_ref[i]) x Q_virtual)) x Q_isb)

(parens indicate "logical" application order).

Quaternions are non-commutative but associative: (A x B) x C = A x (B x C)
as only Q_sensors_raw is updated very frequently, we define Q_right and Q_left for efficiency

Q_left  = Q*_isb x Q*_virtual;
Q_right = Q_virtual x Q_isb

TO-DO: If performance becomes an issue, consider making Q_right an array that includes
Q*_sensors_ref in the calculation.

-----------------------------------------------------------------------------------------------
 */

void MainWindow::updateLeftAndRightQuats()
{
	Eigen::AngleAxisd  AngleAxis_isb ( 90 * M_PI/180 , Eigen::Vector3d::UnitX() );
	Eigen::Quaterniond Q_isb ( AngleAxis_isb );
	Q_isb.normalize();

	mQ_left  = Q_isb.conjugate() * mQ_virtual.conjugate();
	mQ_left.normalize();

	mQ_right = mQ_virtual * Q_isb;
	mQ_right.normalize();

}


void MainWindow::updateSegmentsAndJoints()
{

	//this->compensateRawQuats(mQ_sensors_raw);

	Eigen::Quaterniond refLiveDifference, operateLeft;

	// Store segments (ISB)

	for(int iSensor = 0 ; iSensor <= (MainWindow::TOTAL_SENSORS-1) ; ++iSensor )
	{

		// Raw quats were not normalized. Ref quats were (in ModelCalibrationPanel).

		refLiveDifference = mQ_sensors_raw.at(iSensor).normalized() * mQ_sensors_ref.at(iSensor).conjugate();
		refLiveDifference.normalize();

		operateLeft = mQ_left * refLiveDifference;
		operateLeft.normalize();

		mQ_segments[iSensor] =	operateLeft * mQ_right;
		mQ_segments.at(iSensor).normalize();

	}

	// Store joints (ISB)

	Eigen::Quaterniond Q_proximal, Q_distal;

	for(int iJoint = 0 ; iJoint <= (MainWindow::TOTAL_JOINTS-1) ; ++iJoint )
	{

		Q_proximal = mQ_segments[iJoint  ];
		Q_distal   = mQ_segments[iJoint+1];

		// 0 and 1 : right hip   [0]
		// 1 and 2 : right knee  [1]
		// 2 and 3 : right ankle [2]
		// 0 and 4 : left hip    [3]  <--- 0 and 4!

		if( iJoint == 3 )
		{
			Q_proximal = mQ_segments[0];
		}

		// 4 and 5 : left knee   [4]
		// 5 and 6 : left ankle  [5]

		mQ_joints[iJoint] = Q_proximal.conjugate() * Q_distal;
		mQ_joints.at(iJoint).normalize();

	}

	emit segmentsAndJointsChanged(mQ_segments, mQ_joints);


	/// Quaternion to euler angles conversion.

	//  Only to be emitted while the corresponding panels are visible.
	if( mpSagittalAnglesPanel->isVisible() || mpRecordKinematicsPanel->isVisible() )
	{

        QVector<double> eulerAnglesZ(6, 0.0); // 6 sagittal angles, init them with 0.0

		for(int iAngle = 0 ; iAngle <= (eulerAnglesZ.size()-1) ; ++iAngle )
		{

            // Using Eigen/unsupported
            /*
            Eigen::Matrix<double, 3, 3>  tempRotMatrix  = mQ_joints.at(iAngle).toRotationMatrix();
            Eigen::EulerAnglesZXYd       eulerAnglesZXY = Eigen::EulerAngles<double, Eigen::EulerSystemZXY>::EulerAngles(tempRotMatrix, true, true, true);
            eulerAnglesZ[ iAngle ] = (eulerAnglesZXY.alpha() * 180)/EIGEN_PI;
            */

			// Using plain Eigen
            /*
            Eigen::Matrix3d  tempRotMatrix = mQ_joints.at(iAngle).toRotationMatrix();
            Eigen::Vector3d eulerAnglesZXY = tempRotMatrix.eulerAngles(2,0,1);
            eulerAnglesZ[ iAngle ] = ( eulerAnglesZXY[0] * 180)/EIGEN_PI;
            */


			// Using another library, Eigen gave wrong results.
            double res[3];
			quaternion2euler( mQ_joints.at(iAngle), res , yxz ); // rotation sequence conventions are backwards

			// Change the angle signs according to clinical conventions

			int sign = 1;

			// change signs for right and left knees
			if( iAngle == 1 || iAngle == 4 )
			{
				sign = -1;
			}

            // LE QUITO EL SIGNO POR AHORA

            eulerAnglesZ[iAngle] = sign * res[0] * 180/EIGEN_PI; // otherlib


            // Solucion toche que no sirvio
            /*
            double jumpyAngleRad     = eulerAnglesZXY.alpha();
            double lastJumpyAngleRad = mLastJumpyAnglesRadZ.at(iAngle);
            mLastJumpyAnglesRadZ[iAngle] = jumpyAngleRad; // save current as next
            double tempAngleRad = angleUnwrap( lastJumpyAngleRad, jumpyAngleRad );
            eulerAnglesZ[ iAngle ] =  tempAngleRad*180/EIGEN_PI; // fixed angle
            mEulerZMode = updateAngleMode(mEulerZMode, lastJumpyAngleRad, jumpyAngleRad);
            if( mEulerZMode == 0 )
            {
                jumpyAngleRad = jumpyAngleRad - EIGEN_PI;
            }
            */


            /*
            if( iAngle == 1 )
            {
                qDebug() << eulerAnglesZXY.alpha()*180/EIGEN_PI << " " << eulerAnglesZXY.beta()*180/EIGEN_PI << " " << eulerAnglesZXY.gamma()*180/EIGEN_PI;
            }
            */


		}

		emit anglesChanged( eulerAnglesZ );

		if( mpRecordKinematicsPanel->isVisible() )
		{
			emit kinematicsChanged( eulerAnglesZ , mQ_sensors_raw, mQ_segments, mQ_joints );
		}

	}

	///DEBUG METHODS
	//emit debugCalibration( mQ_virtual, mQ_sensors_raw, mQ_sensors_ref );


}


// --------------------------------------------------------------------
///         Getters and setters for recording
// --------------------------------------------------------------------

Eigen::Quaterniond MainWindow::getVirtualQuat(){

	return mQ_virtual;

}


std::array< Eigen::Quaterniond, 7 > MainWindow::getReferenceQuats(){

	return mQ_sensors_ref;

}


// --------------------------------------------------------------------
///         GUI eyecandy
// --------------------------------------------------------------------



void MainWindow::initializeComplexVariables()
{
	// Older methods to decorate the App's window
    /*
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsView* view  = mUi->logoGraphicsView;
    */

	// Safety net: this variable _might_ be used without having been updated.

	mRawQuatsFallback.fill( Eigen::Quaterniond(1,0,0,0) );
}
