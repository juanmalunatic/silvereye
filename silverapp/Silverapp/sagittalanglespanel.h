#ifndef SAGITTALANGLESPANEL_H
#define SAGITTALANGLESPANEL_H

#include <QWidget>
#include "qpanel.h"
#include "qcustomplot.h"



namespace Ui {
    class SagittalAnglesPanel;
}

class SagittalAnglesPanel : public QPanel
{
    Q_OBJECT

public:
    explicit SagittalAnglesPanel(QWidget *parent = 0);
    ~SagittalAnglesPanel();

private:

	void setupPlot(

		QCustomPlot* pPlot,
		QString      plot_title,

		QString      low_title,
		qint32       range_low,

		QString      high_title,
		qint32       range_high

	);

	qint32 mSecondsToPlot = 3; // seconds, not milliseconds, m indicates member

	// Non-elegant way of keeping track of plot elements

	// Update a plot index every time a plot is created


	// Store pointers for the updatable elements
	int mSetupCounter = 0;

	QVector<QCustomPlot*> mpAnglePlots;
	QVector<QCPItemText*> mpLiveAngleBoxes;

    Ui::SagittalAnglesPanel *ui;


	// Data points

	QVector<double> mX;
	QVector< QVector<double> >mY;
	int mDataIndex;


	int mBufferCounter = 0;
	int mBufferSize    = 7;
	QVector< QVector<double> > mYBuffer;


public slots:

	void updatePlots (const QVector<double>& angles_new);

};

#endif // SAGITTALANGLESPANEL_H
