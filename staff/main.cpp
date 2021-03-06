#include "mainwindow.h"
#include <QApplication>

QString get_staff_id()
{
    QFile file(QDir::currentPath() + "/data.txt");
	if (file.open(QIODevice::ReadOnly))
		return QString(file.readLine());
}

bool user_exist()
{
    QSqlQuery query,qr;
	QString staff_id = get_staff_id();
    qr.exec("SELECT COUNT(*) FROM staff WHERE Id = "+staff_id);
    qr.next();
	query.exec("SELECT COUNT(*) FROM staff WHERE Id = " + staff_id + " and Status='logged_in'");
	query.next();
    if (qr.value(0).toInt() == 0) return true; else
	if (query.value(0).toInt() != 0)
		return true;
	else
		query.exec("UPDATE staff SET Status = 'logged_in' WHERE Id='" + staff_id + "'");
	return false;
}

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

    if (user_exist()) w.close();

	return a.exec();
}
