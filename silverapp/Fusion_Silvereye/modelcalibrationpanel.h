// Semantics: http://www.linguee.es/ingles-espanol/traduccion/mounting.html

#ifndef MODELCALIBRATIONPANEL_H
#define MODELCALIBRATIONPANEL_H

#include <QWidget>

#define EIGEN_DONT_ALIGN_STATICALLY
#include <Eigen/Geometry>
#include <array>


#include "qpanel.h"

namespace Ui
{
	class ModelCalibrationPanel;
}

class ModelCalibrationPanel : public QPanel
{
	Q_OBJECT

public:

	explicit ModelCalibrationPanel(QWidget *parent = 0);
	~ModelCalibrationPanel();

private:

	Ui::ModelCalibrationPanel *ui;

	bool mSaveVirtualOrientation = false;
	bool mSaveSensorMounting     = false;
	bool mSaveCompensation       = false;


	std::array<Eigen::Quaterniond,7> mQ_sensors_raw;                 // refreshed when either V or M is called
	std::array<Eigen::Quaterniond,7> mQ_sensors_ref;                 // updated by calculateMounting
	Eigen::Quaterniond mQ_virtual = Eigen::Quaterniond(1,0,0,0);     // updates by calculateVirtualOrientation

	void calculateMounting();
	void calculateVirtualOrientation();
	void saveCompensation();

public slots:

	void updateReferences(const std::array<Eigen::Quaterniond,7>& Q_sensors_raw);

	void on_saveFrontalButton_clicked();
	void on_saveMountingButton_clicked();
	void on_saveAllButton_clicked();
	void on_saveCompensationButton_clicked();
	void on_resetViewportButton_clicked();
	void on_sagittalViewportButton_clicked();

signals:

	void virtualOrientationChanged(
		const Eigen::Quaterniond &Q_virtual_new
	);

	void initialSensorOrientationsChanged   (
		const std::array<Eigen::Quaterniond,7> &Q_sensors_ref_new
	);

	void compensationChanged   (
		const std::array<Eigen::Quaterniond,7> &Q_compensate
	);

	void viewportResetClicked();
	void viewportSagittalClicked();


};

#endif // MODELCALIBRATIONPANEL_H
