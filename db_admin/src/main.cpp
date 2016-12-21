#include "MainWindow.h"

#include <QApplication>
#include <windows.h>

int main(int argc, char* argv[])
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
