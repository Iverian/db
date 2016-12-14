#include "MainWindow.h"

#include <QApplication>
#include <windows.h>
#include <utility.h>
#include <QDebug>

int main(int argc, char* argv[])
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	qDebug() << "%1, %2"_q.arg(1).arg(2);
	return a.exec();
}
