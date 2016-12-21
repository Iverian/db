#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->description->setReadOnly(true);
    connectDB();

	QFile file(QDir::currentPath() + "/data.txt");
    if (file.open(QIODevice::ReadOnly)) staff_id = QString(file.readLine());

    if (hasRunningOp()) {
        QSqlQuery query;
        query.exec("SELECT Id FROM Operations WHERE Id_staff="+staff_id);
        query.next();
        operation_id = query.value(0).toString();
        query.exec("SELECT Title, Description FROM OperationTypes AS A, Operations AS B WHERE A.Id = B.Id_OperationType and B.Id = "+operation_id);
        query.next();
        ui->title->setText(query.value(0).toString());
        ui->description->setText(query.value(1).toString());
        ui->get_operation->setEnabled(false);
    }else {
        ui->title->setText("Get new operation");
        ui->operation_done->setEnabled(false);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("195.19.32.74");
    db.setDatabaseName("ASU_FN1131");
    db.setUserName("ASU_fn11");
    db.setPassword("fn11");
    db.setPort(5432);
    db.open();
}

bool MainWindow::hasRunningOp(){
    QSqlQuery query;
    query.exec("SELECT COUNT(*) FROM Operations WHERE Id_staff="+staff_id+" and Status='running'");
    query.next();
    if (query.value(0).toInt() != 0) return true;else return false;
}

void MainWindow::on_get_operation_clicked()
{
    QSqlQuery query;
    QSqlDatabase::database().transaction();
    query.exec("SELECT Id FROM Operations WHERE Id_operationType in (SELECT Id FROM OperationTypes WHERE Id in (SELECT Id_OperationType FROM Skills WHERE Id_Staff = "+staff_id+")) and Id_staff = 0 and Status = 'available'");
    query.next();

    QString op_id = query.value(0).toString();
    if (op_id != ""){
        query.exec("SELECT Title, Description FROM OperationTypes AS A, Operations AS B WHERE A.Id = B.Id_OperationType and B.Id = "+op_id);
        query.next();

        ui->title->setText(query.value(0).toString());
        ui->description->setText(query.value(1).toString());
        ui->get_operation->setEnabled(false);
        ui->operation_done->setEnabled(true);

        query.exec("Update Operations SET Id_Staff = "+staff_id+", Status = 'running' WHERE Id = "+op_id);
        operation_id = op_id;
    } else ui->title->setText("There are no tasks for you");
    QSqlDatabase::database().commit();

}

void MainWindow::on_operation_done_clicked()
{
    QSqlQuery query;
    query.exec("UPDATE Operations SET Status='completed' WHERE Id="+operation_id);

    query.exec("SELECT Id, id_alg FROM Operations WHERE id_order = (SELECT Id_order FROM Operations WHERE Id = "+operation_id+") and Status <> 'completed'");
    while(query.next()){
        QString id_alg = query.value(1).toString();
        QSqlQuery qr;
        qr.exec("SELECT id_parent FROM algdependences WHERE id_dependent = "+id_alg);
        int s = 0; // счетчик, который инкрементируется в случае если parent операции ещё не готов
        while(qr.next()){
            QString id_parent = qr.value(0).toString();
            QSqlQuery q;
            q.exec("SELECT Id FROM Operations WHERE id_alg = "+id_parent+" and Status <> 'completed'");
            q.next();
            QString a = q.value(0).toString();
            if (a != "") s++;
        }
        if (s == 0){
            QString id_operation = query.value(0).toString();
            qr.exec("UPDATE Operations SET Status = 'available' WHERE Id = "+id_operation);
        }
    }
    operation_id="";
    ui->description->setText("");
    ui->title->setText("Get new operation");
    ui->get_operation->setEnabled(true);
    ui->operation_done->setEnabled(false);
}
