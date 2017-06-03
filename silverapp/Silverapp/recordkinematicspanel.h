#ifndef RECORDKINEMATICSPANEL_H
#define RECORDKINEMATICSPANEL_H

#include <QWidget>

#include <array>
#include <QWidget>
#include <QFileDialog>
#include <QTextStream>
#include <QElapsedTimer>
#include <QTimer>

#define EIGEN_DONT_ALIGN_STATICALLY
#include <Eigen/Geometry>

#include "qpanel.h"

class MainWindow; // instead of include to avoid circular references
				  //http://stackoverflow.com/questions/10462065/error-c2143-syntax-error-missing-before-when-declaring-pointer

namespace Ui {
class RecordKinematicsPanel;
}

class RecordKinematicsPanel : public QPanel
{
	Q_OBJECT

public:

	explicit RecordKinematicsPanel(QWidget *parent = 0);
	~RecordKinematicsPanel();

	void fillFilenameWithCurrentTime();
	bool currentFilenameExists();
	void updateFileStatusText();


private:

	Ui::RecordKinematicsPanel *mpUi;

	QFile * mpFile;
	QElapsedTimer mTimestamper;

	MainWindow* mpMainWindow;

	bool mRecording = false;
	bool mFinalizeRecording = false;

	QString getPathToFile();
	void setupRecording();

	QMetaObject::Connection mConnectNewDataToFile;

	bool mPrintRaw = false;
	bool mPrintSeg = false;
	bool mPrintJoi = false;

	QTimer elapsedTimer;

	int mSecondsElapsed = 0;


public slots:

	void writeSignalsToOpenFile
	(
		const QVector<double>& sagittal_angles,
		const std::array< Eigen::Quaterniond,7> &quats_raw,
		const std::array< Eigen::Quaterniond,7> &quats_segments,
		const std::array< Eigen::Quaterniond,6> &quats_joints
	);

private slots:

	void on_FolderButton_clicked();
	void on_FileButton_clicked();
	void on_FileLineEdit_textChanged(const QString &arg1);

	void on_RecordButton_clicked();

	void updateElapsed();

};

#endif // RECORDKINEMATICSPANEL_H
