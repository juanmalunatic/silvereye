/*


<< TO-DO >>

Here comes an overview of the app.


<< CONVENTIONS >>

names of private variables
http://stackoverflow.com/questions/1228161/why-use-prefixes-on-member-variables-in-c-classes/1229360#1229360
Jason Williams post


	m for members
	c for constants/readonlys
	p for pointer (and pp for pointer to pointer)
	v for volatile
	s for static
	i for indexes and iterators
	e for events

	mp for member + pointer

Where I wish to make the type clear, I use standard suffixes (e.g. List, ComboBox, etc).

Parameters formatting:
	http://stackoverflow.com/questions/5816719/difference-between-function-arguments-declared-with-and-in-c

*/

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{

	QApplication a(argc, argv);

	// Execute the main window
	MainWindow w;
	w.show();

	return a.exec();
}
