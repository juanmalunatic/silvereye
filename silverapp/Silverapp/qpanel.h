/*
 * --------------------------------------------------------------------
* A QPanel is a class derived from QWidget to manage sub-windows'
* visibility and connections to MainWindow:
*
* Hidden  window : data source disconnected, no processing.
* Visible window : data source connected, data processing.
*
* The QPanel itself only differs from a QWidget in that:
*
* - It emits a signal when closed
* - Has a getter and setter method to store and retrieve the
*   connection to the data source.
*
* Actual QPanel handling is done in
*      MainWindow.cpp-> QPanel management
*
* 0. Pre-setup:
*
* - Create a class derived from QPanel and instance it in MainWindow.
* - Create a GUI button in MainWindow to activate the QPanel.
* - Create a data source SIGNAL to update the QPanel's content.
*
* 1. Connection
*
* Create a method based on an event of the created GUI button.
* In this method:
*
*  - Return if panel is already visible ( isVisible() method )
*
*  - Connect the SIGNAL data source to a SLOT of your derived class
*	 storing the connection as a temp var (type QMetaObject::Connection)
*
*  - Use panelSetupDisconnectionAndShow(pPanel, tempConn) to store
*    the connection in the object's instance and show the window.
*
* 2. Disconnection
*
* A QPanel instance will emit panelNotifyClose when it has been closed.
* This signal will be auto-connected to MainWindow::panelDisconnect with
* the above method, handling disconnection onWindowClose on its own :)
*
*/

#ifndef QPANEL_H
#define QPANEL_H

#include <QWidget>
#include <QDebug>

class QPanel : public QWidget
{

	Q_OBJECT

public:

	explicit QPanel(QWidget *parent = 0) ;
	~QPanel();

	void                    setConnectionToMainWindow(const QMetaObject::Connection &newConnection);
	//void                    setConnectionToMainWindow(QString Hola);
	QMetaObject::Connection getConnectionToMainWindow();

	void closeEvent(QCloseEvent *event);

	void showEvent(QShowEvent *event);


private:

	QMetaObject::Connection mConnectionToMainWindow;

signals:

	void panelClosed(QPanel* Panel);
	void panelOpened(QPanel* Panel);

public slots:

	//

};

#endif // QPANEL_H
