#include "filesGenerator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	filesGenerator w;
	w.show();
	return a.exec();
}
