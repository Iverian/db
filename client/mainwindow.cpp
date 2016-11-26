#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    connectDB();
    QSqlQuery query;
    query.exec("Create table test(Id integer, Name varchar(20))");
    //query.exec("INSERT INTO order_type VALUES(1,'hhh','alg')");
    //query.exec("SELECT count(*) FROM sqlite_master WHERE type='table' AND name='test'");
    //query.next();
    //qDebug()<< query.value(0).toString();
    //query.exec("Drop table test");
    ui->setupUi(this);
}


void MainWindow::connectDB(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("195.19.32.74");
    db.setDatabaseName("ASU_FN1131");
    db.setUserName("ASU_fn11");
    db.setPassword("fn11");
    db.setPort(5432);
    db.open();
}

void MainWindow::init(){

}

MainWindow::~MainWindow()
{
    delete ui;
}
