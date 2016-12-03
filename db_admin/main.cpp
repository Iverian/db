#include "MainWindow.h"
#include "OperationEdit.h"
#include "OrderEdit.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    OrderEdit w;
    w.show();
    return a.exec();
}
