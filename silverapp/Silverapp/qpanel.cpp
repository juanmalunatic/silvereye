/*
*
* A QPanel is a class derived from QWidget to manage sub-windows'
* visibility and connections to MainWindow from MainWindow itself.
*
* Signals sent from MainWindow (providing data updates) can be
* disconnected while a sub-window is hidden to save resources
* and re-connected when the sub-window is reopened.
*
* GUI button is clicked
*	Connect data source to panel
*	Show panel window
*
* Panel is closed
*	QPanel emits closenotifier
*	  Disconnect data source
*	  Hide panel window
*
* Usage steps on qpanel.h
* Based on http://stackoverflow.com/questions/32124715/is-it-possible-to-disconnect-all-of-a-qobjects-connections-without-deleting-it
*
*/

#include "qpanel.h"

QPanel::QPanel(QWidget *parent) :	QWidget(parent, Qt::Window) // Derive from base class QWidget and make a standalone window.
{

}

QPanel::~QPanel()
{

}


/*Every time the QPanelInstance is connected to a data source in MainWindow,
this connection can be saved with setConnectionToMainWindow.*/

void QPanel::setConnectionToMainWindow(const QMetaObject::Connection &newConnection)
{
	this->mConnectionToMainWindow = newConnection;
}

QMetaObject::Connection QPanel::getConnectionToMainWindow()
{
	return this->mConnectionToMainWindow;
}


/* When the QPanel is closed, a signal is emitted, which can be used to trigger
a slot in MainWindow. */

void QPanel::closeEvent(QCloseEvent *event)
{
	Q_UNUSED( event )

	/* The QPanel instance will report when it has been closed. The emitted
	signal, panelNotifyClose, points to the closed panel (object is not
	destroyed on close, window is just hidden).

	As the signal carries a pointer to the QPanel that was just closed,
	its saved connection can be nullified with QObject::disconnect.
	This implementation occurs in MainWindow  */

	emit panelClosed(this);

	qDebug() << "CloseEvent on QPanel " << this->objectName();

}

void QPanel::showEvent( QShowEvent *event ) {

	//QWidget::showEvent( event ); //<-suggested online no idea

	Q_UNUSED( event );

	qDebug() << "ShowEvent on QPanel " << this->objectName();

	emit panelOpened(this);


}


