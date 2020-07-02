#include "slides.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Slides w;
	w.show();
	return a.exec();
}
