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
    queryModel->setQuery("SELECT Title as Orders FROM order_type");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_order_clicked()
{
    QString selected_order = ui->lst_orders->model()->data(ui->lst_orders->currentIndex()).toString();
    QString orders_str = ui->concat_orders_str->text();
    if (orders_str == "") ui->concat_orders_str->setText(selected_order);else ui->concat_orders_str->setText(orders_str+","+selected_order);
    add_new_order();
}

void MainWindow::add_new_order(){
    QStringList lst_orders = ui->concat_orders_str->text().split(",");
    QStandardItemModel *model = new QStandardItemModel();
    int num_orders = lst_orders.count();
    for (int i=0; i < num_orders; i++){
        QStandardItem *item = new QStandardItem();
        item->setText(lst_orders.at(i));
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
}
