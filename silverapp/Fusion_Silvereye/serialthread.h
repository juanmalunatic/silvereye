/*


  http://stackoverflow.com/questions/25224575/how-to-safely-destruct-a-qthread

*/

#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QObject>
#include <QThread>

class SerialThread : public QThread
{

	Q_OBJECT

	using QThread::run;

public:
	SerialThread(QObject * parent = 0);
	~SerialThread();

};

#endif // SERIALTHREAD_H
