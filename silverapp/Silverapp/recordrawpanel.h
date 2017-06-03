#ifndef RECORDRAWPANEL_H
#define RECORDRAWPANEL_H

#include <array>
#include <QWidget>
#include <QFileDialog>
#include <QTextStream>
#include <QElapsedTimer>

#include "imudata.h"

namespace Ui {
	class RecordRawPanel;
}

class RecordRawPanel : public QWidget
{
	Q_OBJECT

public:
	explicit RecordRawPanel(QWidget *parent = 0);
	~RecordRawPanel();

	void fillFilenameWithCurrentTime();
	bool currentFilenameExists();
	void updateFileStatusText();

private:

	Ui::RecordRawPanel *mUi;

	bool mRecording = false;
	bool mFinalizeRecording = false;


	QElapsedTimer mTimestamper;

	// Pointer to QFile: ok
	QFile* mpFile;

	QMetaObject::Connection mConnectNewDataToFile;

	//fxs
	void setUpRecording();
	void finishRecording(QTextStream& textStream);
	QString getPathToFile();

private slots:

	void on_FolderButton_clicked();
	void on_FileButton_clicked();
	void on_FileLineEdit_textChanged(const QString &arg1);
	void on_RecordButton_clicked();

	void streamDataToOpenFile(const std::array<ImuData,7>& newData);


};

#endif // RECORDRAWPANEL_H
