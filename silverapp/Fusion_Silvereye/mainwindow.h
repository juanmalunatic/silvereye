#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QElapsedTimer>

/*
Unaligned bug (when passing Eigen object as reference)
I didn't want vectorization anyway :/

http://stackoverflow.com/questions/28413100/pass-fixed-size-eigen-types-as-parameters-in-qt-signals-and-slots-function
http://eigen.tuxfamily.org/dox/group__TopicUnalignedArrayAssert.html

Change to std::vector and use the provided solution
if vectorization becomes crucial.
*/

#define EIGEN_DONT_ALIGN_STATICALLY
#include <Eigen/Geometry>

#include "qpanel.h"
#include "imudata.h"
#include "serialthread.h"
#include "serialworker.h"

#include "systemstatuspanel.h"
#include "recordrawpanel.h"
#include "serialsettingspanel.h"
#include "modelcalibrationpanel.h"
#include "humanmodelpanel.h"
#include "sagittalanglespanel.h"
#include "recordkinematicspanel.h"

namespace Ui {

	class MainWindow;

}

class MainWindow : public QMainWindow
{

	Q_OBJECT // QMetaObject system

public:

	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();



	// Public functions
	std::array<ImuData,7> getSensorData();

	// Constant (read only)
	// TO-DO change it
	static const qint32 TOTAL_SENSORS = 7;
	static const qint32 TOTAL_JOINTS  = 6;

	void panelStoreConnectionAndShow(QPanel* pPanel, QMetaObject::Connection newConnection);

	// Caution: SerialWorker lives in a different thread, so this function will
	//   only work after serialThreadStart() has executed (mSerialThreadStarted = true)

	// SerialWorker* getSerialWorkerPointer();

	SerialWorker * getSerialWorker();

	Eigen::Quaterniond getVirtualQuat();
	std::array< Eigen::Quaterniond, 7 > getReferenceQuats();



private:

	// Main window

	Ui::MainWindow *mUi;

	// Secondary windows

	SystemStatusPanel     *mpSystemStatusPanel;   // System status panel
	SerialSettingsPanel   *mpSerialSettingsPanel;
	RecordRawPanel        *mpRecordRawPanel; // Recording panel
	ModelCalibrationPanel *mpModelCalibrationPanel;
	HumanModelPanel       *mpHumanModelPanel;
    SagittalAnglesPanel   *mpSagittalAnglesPanel;
	RecordKinematicsPanel *mpRecordKinematicsPanel;


	// Serial thread controls
	// Located first than panels so they get destroyed first

	SerialWorker  mSerialWorker;  // Serial controller
	SerialThread  mSerialThread;     // Thread to manage the serial readings
	qint32        mSerialRounds = 0;


	// Data

	// Warning: Updates constantly: item 6 can be from a previous sampling, while item 1 from a new one.
	// Serialworker sends 30 bytes -> mainWindow formats them and
	// stores them in mSensorData

	std::array<ImuData,7>            mSensorDataUnsynced = std::array<ImuData,7>();
	std::array<Eigen::Quaterniond,7> mRawQuatsUnsynced   = std::array<Eigen::Quaterniond,7>();

	// Quaternion algorithms

	Eigen::Quaterniond mQ_virtual = Eigen::Quaterniond(1,0,0,0);

	std::array< Eigen::Quaterniond, 7 > mQ_sensors_raw;     // Proper init in setup method (quaternionCalcsConnect)
	std::array< Eigen::Quaterniond, 7 > mQ_sensors_ref;

	Eigen::Quaterniond mQ_left  = Eigen::Quaterniond(1,0,0,0);
	Eigen::Quaterniond mQ_right = Eigen::Quaterniond(1,0,0,0);

	std::array< Eigen::Quaterniond, 7 > mQ_segments;
	std::array< Eigen::Quaterniond, 6 > mQ_joints;

	std::array< Eigen::Quaterniond, 7 > mQ_compensate;
	void compensateRawQuats(std::array<Eigen::Quaterniond, 7> &inputQuats);

    // Track angle changes to unwrap

    QVector<double> mLastJumpyAnglesRadZ = QVector<double>(6, 0.0);
    int mEulerZMode = 2; // useful modes are 0 and 1


	// Setup functions

    void interfaceDecorate();

	void serialThreadStart();

	void panelsInstantiate();
	void panelSetupDisconnectionAndShow(QPanel* pPanel, QMetaObject::Connection newConnection);
	void panelsInterconnect();

	void quaternionCalcsConnect();
	void updateLeftAndRightQuats();




protected:

	void virtual closeEvent( QCloseEvent *evt ); // needed to close the 3d panel on quit


signals:

	// We have a const T& and a Qt::DirectConnection
	// pass the private var as a ref! (allowed)

	void sensorDataChanged(const std::array<ImuData,7>& currSensorData);
	void quaternionDataChanged( const std::array<Eigen::Quaterniond,7>& Q_sensors_raw);

	void segmentsAndJointsChanged
	(
		const std::array<Eigen::Quaterniond,7>& Q_segments_new,
		const std::array<Eigen::Quaterniond,6>& Q_joints_new

	);

	void anglesChanged
	(
		const QVector<double>& angles_new
	);

	// Use to debug

	void debugCalibration
	(
		const Eigen::Quaterniond                &Q_virtual,
		const std::array< Eigen::Quaterniond,7> &Q_sensors_raw,
		const std::array< Eigen::Quaterniond,7> &Q_sensors_ref
	);


	void kinematicsChanged
	(
		const QVector<double>& sagittal_angles,
		const std::array< Eigen::Quaterniond,7> &quats_raw,
		const std::array< Eigen::Quaterniond,7> &quats_segments,
		const std::array< Eigen::Quaterniond,6> &quats_joints
	);



private slots:

	//Generic panel management
	void disconnectPanel(QPanel* Panel); // was a public slot

	// For incoming serial data
	void processSerialData(const QByteArray &newSensorData);

	void on_systemStatusButton_clicked();
	void on_recordRawButton_clicked();
	void on_serialSettingsButton_clicked();
	void on_modelCalibrationButton_clicked();
	void on_humanModelButton_clicked();
    void on_sagittalAnglesButton_clicked();
	void on_recordKinematicsButton_clicked();

	void updateSegmentsAndJoints();

public slots:

	// Quaternion algorithms

	void updateVirtualOrientation(
		const Eigen::Quaterniond &Q_virtual_new
	);

	void updateInitialSensorOrientations(
		const std::array<Eigen::Quaterniond,7> &Q_sensors_ref_new
	);

	void updateCompensation(
		const std::array<Eigen::Quaterniond,7> &Q_compensate
	);


};

#endif // MAINWINDOW_H
