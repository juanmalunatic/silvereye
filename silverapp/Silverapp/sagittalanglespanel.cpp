/*
Useful docs on how to use QCP (QCustomPanel):

Layout system:
    http://www.qcustomplot.com/documentation/thelayoutsystem.html


Realtime data:
	 http://www.qcustomplot.com/index.php/support/forum/31


*/
#include "sagittalanglespanel.h"
#include "ui_sagittalanglespanel.h"
#include "qcustomplot.h"

#include <QDebug>


SagittalAnglesPanel::SagittalAnglesPanel(QWidget *parent) :
    QPanel(parent),
    ui(new Ui::SagittalAnglesPanel)
{


    ui->setupUi(this);


	/// Data init
	// 100 Hz, and 3 seconds runtime = 300 datapoints per graph

	int const datapoints = 300;
	int const plots = 6;

	mDataIndex = 0;

	//mX doesn't change, set it from 0 to 299
	//mX can be used for every plot

	mX.resize(datapoints);
	for( int iX = 0 ; iX <= (datapoints-1); ++iX )
	{
		mX[iX] = iX/100.0; // so that 300 samples gives 3 secs.
	};

	// mY contains data for 6 plots
	// mY will change each iteration

	mY.resize(plots);

	for(int iPlot = 0 ; iPlot <= (plots-1); ++iPlot)
	{
		mY[iPlot].reserve(datapoints);
		mY[iPlot].resize(datapoints);
		mY[iPlot].fill(0);
	}

	//mYBuffer holds new points until
	// resizing and replotting takes place

	mYBuffer.resize(plots);
	for(int iYBuffer = 0; iYBuffer <= (plots-1); ++iYBuffer)
	{
		mYBuffer[iYBuffer].resize(mBufferSize);
		mYBuffer[iYBuffer].fill(0);
	}


	/// Ranges setup

	// Hips

	qint32  hip_low       = -30;
	QString hip_low_label = "Extens.";

	qint32  hip_high       = +120;
	QString hip_high_label = "Flexion";

	// Knees

	qint32  knee_low       = -40; //realmente es -10 o menos pero pa display
	QString knee_low_label = "Hyperext.";

	qint32  knee_high       = +150;
	QString knee_high_label = "Flexion";

	// Ankles

	qint32  ankle_low       = -50;
	QString ankle_low_label = "Plantarflex.";

	qint32  ankle_high       = +20;
	QString ankle_high_label = "Dorsiflex.";


	// Pointers. Storing them is cheaper than finding them each iteration.

	mpAnglePlots     = QVector<QCustomPlot*>(6); // Easy iteration
	mpLiveAngleBoxes = QVector<QCPItemText*>(6); // Live angles

	// Setup the plots in an order that matches the incoming angles
	// This writes the internal pointers in order. Elegant and robust, I know.

	mSetupCounter = 0; // increases each time setupPlot() is called

	setupPlot( ui->rightHipPlot  , "Right hip"  , hip_low_label  , hip_low  , hip_high_label  , hip_high);
	setupPlot( ui->rightKneePlot , "Right knee" , knee_low_label , knee_low , knee_high_label , knee_high);
	setupPlot( ui->rightAnklePlot, "Right ankle", ankle_low_label, ankle_low, ankle_high_label, ankle_high);

	setupPlot( ui->leftHipPlot   , "Left hip"   , hip_low_label  , hip_low  , hip_high_label  , hip_high);
	setupPlot( ui->leftKneePlot  , "Left knee"  , knee_low_label , knee_low , knee_high_label , knee_high);
	setupPlot( ui->leftAnklePlot , "Left ankle" , ankle_low_label, ankle_low, ankle_high_label, ankle_high);



}
SagittalAnglesPanel::~SagittalAnglesPanel()
{
    delete ui;
}

// Generic plot set-up for all the plots

void SagittalAnglesPanel::setupPlot
(
	QCustomPlot* pPlot,
	QString      plot_title,

	QString      low_title,
	qint32       range_low,

	QString      high_title,
	qint32       range_high
)
{
    QCustomPlot * customPlot = pPlot;


	// Define interactivity
	 customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom );

	 customPlot->axisRect()->setRangeZoomAxes(0, customPlot->yAxis );
	 customPlot->axisRect()->setRangeDragAxes(0, customPlot->yAxis );

	 customPlot->setNoAntialiasingOnDrag(true);

	/// Data

	QVector<double> iniY( 300 , 0.5 );

	// create graph and assign data to it:
	customPlot->addGraph();
	customPlot->graph(0)->setData( mX, iniY );

	/// Padding and styling

	// pad to show extremes
	// padding is relative to limits to make it look consistent

	qint32 calc_padding = (range_high - range_low)/10; // low is always negative

	qint32 range_padding =  calc_padding*0.8;
	qint32 label_padding =  calc_padding;

	qint32 range_low_p  = range_low  - range_padding;
	qint32 range_high_p = range_high + range_padding;

    // give the axes some labels:
	customPlot->xAxis->setLabel("Time [s]");
	customPlot->yAxis->setLabel("Angle [deg]");

	QFont axis_font = QFont("Arial", 6, QFont::Medium );
	axis_font.setStyleStrategy(QFont::PreferAntialias);

	customPlot->xAxis->setLabelFont( axis_font );
	customPlot->yAxis->setLabelFont( axis_font );

    // set axes ranges, so we see all data:

	customPlot->yAxis->setRange(range_low_p, range_high_p );
	customPlot->xAxis->setRange( 0, mSecondsToPlot);

	// set extra axes to indicate the kind of movement

	//QCPAxisRect * axisRect = customPlot->axisRect();
	//axisRect->addAxis(QCPAxis::atRight);

	//QCPAxis * innerAxis = axisRect->axis(QCPAxis::atLeft, 0);
	//QCPAxis * outerAxis = axisRect->axis(QCPAxis::atRight, 0);

	QCPAxis * outerAxis = customPlot->yAxis2;
	outerAxis->setVisible(true);
	outerAxis->setTickLabelSide(QCPAxis::lsInside);
	outerAxis->setTickLabelPadding(0);
	outerAxis->setTickLength(0,0);

	//innerAxis->setTickLabelColor(QColor("#6050F8"));

	QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);

	textTicker->addTick(range_low  + label_padding , low_title );
	textTicker->addTick(range_high - label_padding , high_title);


	//textTicker->addTick( (range_high+range_low)/2 , "Angle [deg]");


	// Creating a color to use while drawing the axis
	// http://www.qcustomplot.com/index.php/support/forum/119

	QColor axis_color(255, 255, 255);   // QColor(RED, GREEN, BLUE, ALPHA);
	QPen axis_pen;                      // Creating a pen to use for drawing the axis
	axis_pen.setColor(axis_color);      // Assigning the desired color to the pen
	outerAxis->setBasePen(axis_pen);	// Assigning the previously created pen to the axis you want to draw
	outerAxis->setTickPen(axis_pen);

	outerAxis->setRange( range_low_p, range_high_p );
	outerAxis->setTicker(textTicker);
	//outerAxis->setLabel("Angle [deg]");

	// Title on top
	QCPTextElement *title = new QCPTextElement(customPlot);
	title->setText( "         "+plot_title ); // 1337 h4x0r adds spaces for alignment
	QFont title_font = QFont("Arial", 10, QFont::Medium );
	title->setFont(title_font);
	title->setAutoMargins(QCP::msBottom|QCP::msTop);
	title->setMargins( QMargins(0,-1,0,-1) );

	//qDebug() << title->margins();

	// then we add it to the main plot layout:
	customPlot->plotLayout()->insertRow(0); // insert an empty row above the axis rect
	customPlot->plotLayout()->addElement(0, 0, title); // place the title in the empty cell we've just created

	customPlot->axisRect()->setAutoMargins(QCP::msLeft|QCP::msBottom);
	customPlot->axisRect()->setMargins(QMargins(-1, 0, 20, -1));

	QColor zero_color(136, 220, 232);
	QPen zero_pen;
	zero_pen.setColor(zero_color);

	customPlot->yAxis->grid()->setZeroLinePen(zero_pen);

	// Live angle marker

	QCPItemText *liveAngle = new QCPItemText(customPlot);

	//liveAngle->position->setType(QCPItemPosition::ptViewportRatio ); // todo el espacio, incluso afuera
	liveAngle->position->setType(QCPItemPosition::ptAxisRectRatio ); // todo el espacio
	liveAngle->setClipToAxisRect(false);// free me
	//liveAngle->position->setCoords(0.3,0.3); //ori

	liveAngle->position->setCoords( 0.03 , 0.95 );

	liveAngle->setPositionAlignment(Qt::AlignBottom|Qt::AlignLeft);
	liveAngle->setText( QString("%1").arg(range_low) );
	liveAngle->setFont(  QFont("Arial",9, QFont::Bold) );
	liveAngle->setColor( QColor(45,141,168) );

	liveAngle->setPen(QPen(Qt::black)); // show black border around text
	liveAngle->setPadding( QMargins(2,2,2,2) );

	// Fill in the pointers and advance the counter

	mpAnglePlots    [ mSetupCounter ] = pPlot;
	mpLiveAngleBoxes[ mSetupCounter ] = liveAngle;
	++mSetupCounter;

	customPlot->replot();

}

void SagittalAnglesPanel::updatePlots (const QVector<double>& angles_new)
{

	// TO-DO: Almacenamos todos los datos entrantes pero solo repintamos
	//        de acuerdo a un frameskip interno.


	int const plots = angles_new.size();

	// Store mBufferSize (10) samples

	if( mBufferCounter <= (mBufferSize-1))
	{
		// Iterate every plot to add data to buffer
		for(int iPlot = 0 ; iPlot <= (plots-1) ; ++iPlot)
		{

			mYBuffer[iPlot][mBufferCounter] = angles_new.at(iPlot);
		}

		++mBufferCounter;
	}
	else
	{
		mBufferCounter = 0;

		// When the buffer is full, we update the plot (as it's expensive)

		for(int iPlot = 0 ; iPlot <= (plots-1) ; ++iPlot)
		{

			// Remove mBufferSize samples to make space for the new data

			for(int iClean = 0; iClean <= (mBufferSize-1); ++iClean)
			{
				mY[iPlot].removeFirst();
			}

			// Add buffer points at the end

			mY[iPlot].append( mYBuffer.at(iPlot) );


			// Data
			mpAnglePlots.at(iPlot)->graph(0)->setData( mX, mY.at(iPlot) );

			// Label

			QString newLabel = QString::number( angles_new.at(iPlot) , 'g', 2);

			mpLiveAngleBoxes.at(iPlot)->setText( newLabel );


			mpAnglePlots.at(iPlot)->replot();

		}

		// Update graphs

	}

	/*for(int iPlot = 0 ; iPlot <= (plots-1) ; ++iPlot)
	{

	}


	for(int iPlot = 0 ; iPlot <= (plots-1) ; ++iPlot)
	{

		//

		//mpAnglePlots.at(iPlot)->graph(0)->addData();

		//qDebug() << angles_new.at(iPlot);

		//mpAnglePlots.at(iPlot)->repaint();

	}
	*/

}





