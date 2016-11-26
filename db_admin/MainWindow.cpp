#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "databaseConnectionParams.h"

#include <QMenu>

void popupMenu(const QPoint &pos, QWidget *viewport, const std::initializer_list<QAction *> &actList, QWidget *parent);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectToDb();
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

void MainWindow::connectToDb()
{
    db = QSqlDatabase::addDatabase(dbParam::driver);
    db.setHostName(dbParam::hostName);
    db.setDatabaseName(dbParam::dbName);
    db.setUserName(dbParam::userName);
    db.setPassword(dbParam::pass);
    db.setPort(dbParam::port);
    db.open();
}

void MainWindow::on_operNames_customContextMenuRequested(const QPoint &pos)
{
    popupMenu(pos, ui->operNames->viewport(), {ui->actNewOperation, ui->actEditOperation, ui->actDeleteOperation}, this);
}

void MainWindow::on_orderNames_customContextMenuRequested(const QPoint &pos)
{
    popupMenu(pos, ui->orderNames->viewport(), {ui->actNewOrder, ui->actEditOrder, ui->actDeleteOrder}, this);
}

void MainWindow::on_staffView_customContextMenuRequested(const QPoint &pos)
{
    popupMenu(pos, ui->staffView->viewport(), {ui->actNewStaffMember, ui->actEditStaffMember, ui->actDeleteStaffMember}, this);
}

void popupMenu(const QPoint& pos, QWidget* viewport, const std::initializer_list<QAction*>& actList, QWidget* parent = Q_NULLPTR)
{
    auto menu = new QMenu(parent);
    for (auto& i : actList)
        menu->addAction(i);
    menu->popup(viewport->mapToGlobal(pos));
}

void MainWindow::on_actNewOperation_triggered()
{

}

void MainWindow::on_actNewOrder_triggered()
{

}

void MainWindow::on_actNewStaffMember_triggered()
{

}

void MainWindow::on_operNames_doubleClicked(const QModelIndex &index)
{

}



void MainWindow::on_orderNames_doubleClicked(const QModelIndex &index)
{

}



void MainWindow::on_staffView_doubleClicked(const QModelIndex &index)
{

}


void MainWindow::on_actEditOperation_triggered()
{

}

void MainWindow::on_actEditOrder_triggered()
{

}

void MainWindow::on_actEditStaffMember_triggered()
{

}

void MainWindow::on_actDeleteOperation_triggered()
{

}

void MainWindow::on_actDeleteOrder_triggered()
{

}

void MainWindow::on_actDeleteStaffMember_triggered()
{

}