#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    ui->concat_orders_str->hide();

    connectDB();
    init();
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
    QSqlQuery query;
    QSqlQueryModel *queryModel = new QSqlQueryModel(this);
    ui->lst_orders->setModel(queryModel);
    queryModel->setQuery("SELECT Id, Title as Orders FROM ordertypes");
    ui->lst_orders->setColumnHidden(0,true);
}

void MainWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);
    ui->lst_orders->horizontalHeader()->setDefaultSectionSize(ui->lst_orders->width());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_order_clicked()
{
    QString selected_order = ui->lst_orders->model()->data(ui->lst_orders->currentIndex()).toString();
    int row = ui->lst_orders->currentIndex().row();
    QString selected_order_id = QString::number(ui->lst_orders->model()->index(row,0).data().toInt());
    QString orders_str = ui->concat_orders_str->text();
    if (orders_str == "") ui->concat_orders_str->setText(selected_order_id+":"+selected_order);else ui->concat_orders_str->setText(orders_str+","+selected_order_id+":"+selected_order);
    add_new_order();
}

void MainWindow::add_new_order(){
    QStringList lst_orders = ui->concat_orders_str->text().split(",");
    QStandardItemModel *model = new QStandardItemModel();
    int num_orders = lst_orders.count();
    for (int i=0; i < num_orders; i++){
        QString params = lst_orders.at(i);
        QStringList lst_orders_data = params.split(":");
        QStandardItem *item = new QStandardItem();
        item->setText(lst_orders_data.at(1));
        model->appendRow(item);
    }
    ui->lst_client_orders->setModel(model);
}

void MainWindow::on_delete_client_order_clicked()
{
    int index = ui->lst_client_orders->currentIndex().row();

    int count = ui->lst_client_orders->selectionModel()->selectedRows().count();
    for( int i = 0; i < count; i++){
        ui->lst_client_orders->model()->removeRow(ui->lst_client_orders->selectionModel()->selectedRows().at(i).row(), QModelIndex());
    }

    QStringList lst_orders = ui->concat_orders_str->text().split(",");
    lst_orders.removeAt(index);

    QString str="";
    int n = lst_orders.count();
    for (int j = 0; j< n; j++){
        if (j == 0) str = str+lst_orders.at(j);else str = str+","+lst_orders.at(j);
    }
    ui->concat_orders_str->setText(str);
}

void MainWindow::on_send_order_clicked()
{
    QSqlQuery query;
    QStringList lst_orders = ui->concat_orders_str->text().split(",");
    QString num_orders = QString::number(lst_orders.count());

    QSqlDatabase::database().transaction();
    query.exec("INSERT INTO ClientOrders(NumOrders) VALUES("+num_orders+")");
    query.exec("SELECT Id FROM ClientOrders WHERE Id=(SELECT MAX(Id) FROM ClientOrders)");
    query.next();
    QString client_id = QString::number(query.value(0).toInt());

    for(int i=0; i < num_orders.toInt(); i++){
        QString order_params = lst_orders.at(i);
        QStringList order_data = order_params.split(":");
        QString IdOrderType = order_data.at(0);

        query.exec("SELECT COUNT(*) FROM Algorithm WHERE id_ordertype="+IdOrderType);
        query.next();
        QString num_operations = QString::number(query.value(0).toInt());
        query.exec("INSERT INTO Orders(id_ordertype,id_client,numoperations) VALUES("+IdOrderType+","+client_id+","+num_operations+")");

        query.exec("SELECT Id FROM Orders WHERE Id=(SELECT MAX(Id) FROM Orders)");
        query.next();
        QString id_order = QString::number(query.value(0).toInt());

        query.exec("SELECT Id_operationType FROM Algorithm WHERE Id_OrderType = "+IdOrderType+" AND Id NOT IN (SELECT Id_dependent FROM AlgDependencies)");
        while(query.next()){
            QSqlQuery qr;
            QString id_operationtype = QString::number(query.value(0).toInt());
            qr.exec("INSERT INTO Operations(id_operationtype,id_order) VALUES("+id_operationtype+","+id_order+")");
        }
    }
    QSqlDatabase::database().commit();

    ui->lst_client_orders->setModel(0);
    ui->concat_orders_str->setText("");
}
