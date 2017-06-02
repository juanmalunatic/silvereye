#include "modelcalibrationpanel.h"
#include "ui_modelcalibrationpanel.h"

#define EIGEN_DONT_ALIGN_STATICALLY
#include <Eigen/Core>
#include <Eigen/Geometry>

#include <QDebug>

#include "qpanel.h"

ModelCalibrationPanel::ModelCalibrationPanel(QWidget *parent) :
	QPanel(parent),
	ui(new Ui::ModelCalibrationPanel)
{
	ui->setupUi(this);
}

ModelCalibrationPanel::~ModelCalibrationPanel()
{
	delete ui;
}

// Flag activation via UI

void ModelCalibrationPanel::on_saveFrontalButton_clicked()
{
	mSaveVirtualOrientation = true;
}

void ModelCalibrationPanel::on_saveMountingButton_clicked()
{
	mSaveSensorMounting = true;
}


void ModelCalibrationPanel::on_saveAllButton_clicked()
{
	mSaveVirtualOrientation = true;
	mSaveSensorMounting   = true;

}

void ModelCalibrationPanel::on_saveCompensationButton_clicked()
{

	mSaveCompensation = true;

}



void ModelCalibrationPanel::updateReferences(const std::array<Eigen::Quaterniond,7>& Q_sensors_raw)
{

	mQ_sensors_raw = Q_sensors_raw;

	if( mSaveVirtualOrientation )
	{
		this->calculateVirtualOrientation();
		mSaveVirtualOrientation = false;
	}

	if( mSaveSensorMounting )
	{
		this->calculateMounting();
		mSaveSensorMounting = false;
	}

	if(mSaveCompensation)
	{
		this->saveCompensation();
		mSaveCompensation = false;

	}

}

void ModelCalibrationPanel::calculateVirtualOrientation()
{

	using namespace Eigen;

	//Virtual axis

	Quaterniond Q_virtual_creator = mQ_sensors_raw[0];

	Vector3d world_X(1,0,0);
	Vector3d world_Z(0,0,1);

	Vector3d vc_Z         = Q_virtual_creator * world_Z;            // Apply rotation to Z axis of the sensor
	Vector3d vc_Z_proy_XY = vc_Z - ( vc_Z.dot(world_Z) * world_Z ); // Projection: rotated Y axis on the XY plane
	Vector3d forward_line = vc_Z_proy_XY.normalized();              // Normalize projection to create a "forward line"

	double dotx = world_X.dot( forward_line );
	double detx = world_Z.dot( world_X.cross(forward_line) );
	double angle = std::atan2(detx,dotx);							// Determine angle between w_X and the forward line

	AngleAxisd xToForward( angle, world_Z );
	Quaterniond Qvirtual( xToForward );								// Construct a quat with the needed rotation

	mQ_virtual = Qvirtual.normalized();


	qDebug() << "Executed: Virtual orientation update.";

	emit virtualOrientationChanged( mQ_virtual );

}

void ModelCalibrationPanel::calculateMounting()
{

	mQ_sensors_ref = mQ_sensors_raw;

	for( int iSen = 0; iSen <= 6 ; ++iSen)
	{
		mQ_sensors_ref.at(iSen).normalize();
	}

	qDebug() << "Executed: Sensor mounting";

	emit initialSensorOrientationsChanged( mQ_sensors_ref );

}


void ModelCalibrationPanel::saveCompensation()
{

	std::array<Eigen::Quaterniond,7>  Q_compensate;


	for( int iC = 0 ; iC <= 6 ; ++iC )
	{
		Q_compensate[iC] = mQ_sensors_raw.at(0) * mQ_sensors_raw.at(iC).conjugate();
		Q_compensate.at(iC).normalize();

		//Q_compensate[iC] = Eigen::Quaterniond(1,0,0,0);

	}

	emit compensationChanged( Q_compensate );

}

void ModelCalibrationPanel::on_resetViewportButton_clicked(){

	emit viewportResetClicked();

}

void ModelCalibrationPanel::on_sagittalViewportButton_clicked()
{
	emit viewportSagittalClicked();

}
