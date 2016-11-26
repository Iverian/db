#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "databaseConnectionParams.h"

#include <QMenu>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include <QDebug>

void popupMenu(const QPoint &pos, QWidget *viewport, const std::initializer_list<QAction *> &actList, QWidget *parent);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectToDb();
    refreshOperView();
    refreshOrderView();
    resizeTableHeader();
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    resizeTableHeader();
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

void MainWindow::refreshOperView()
{
    auto queryModel = new QSqlQueryModel;
    auto rowSelected = ui->operNames->selectionModel() ? ui->operNames->selectionModel()->currentIndex().row() : -1;
    queryModel->setQuery("select Id, Title, Description from OperationTypes", db);

    auto found = -1;
    if (rowSelected != -1) {
        auto query = queryModel->query();
        auto curItem = ui->operNames->model()->index(rowSelected, 0).data().toInt();
        for (auto index = 0; query.next(); ++index) {
            if (query.value(0).toInt() == curItem) {
                found = index;
                break;
            }
        }
    }

    ui->operNames->setModel(queryModel);
    ui->operDesc->clear();
    connect(ui->operNames->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this,
            SLOT(operNames_selectionChanged()));

    if (found != -1)
        ui->operNames->setCurrentIndex(ui->operNames->model()->index(rowSelected, 1));
    ui->operNames->setColumnHidden(0, true);
    ui->operNames->setColumnHidden(2, true);

}

void MainWindow::refreshOrderView()
{
    auto queryModel = new QSqlQueryModel;
    auto rowSelected = ui->orderNames->currentIndex().row();
    queryModel->setQuery("select Id, Title, Description from OrderTypes", db);

    auto found = -1;
    if (rowSelected != -1) {
        auto query = queryModel->query();
        auto curItem = ui->orderNames->model()->index(rowSelected, 0).data().toInt();
        for (auto index = 0; query.next(); ++index)
            if (query.value(0).toInt() == curItem) {
                found = index;
                break;
            }
    }

    ui->orderNames->setModel(queryModel);
    ui->orderDesc->clear();
    ui->orderAlgo->setModel(Q_NULLPTR);
    connect(ui->orderNames->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this,
            SLOT(orderNames_selectionChanged()));

    if (found != -1)
         ui->orderNames->setCurrentIndex(ui->orderNames->model()->index(found, 1));
    ui->orderNames->setColumnHidden(0, true);
    ui->orderNames->setColumnHidden(2, true);
}

void MainWindow::refreshStaffView()
{
    auto queryModel = new QSqlQueryModel;
    queryModel->setQuery("select Id, Name from Staff", db);
    auto selected = ui->staffView->currentIndex();

    auto found = -1;
    if (selected.row() != -1) {
        auto query = queryModel->query();
        auto curItem = ui->staffView->model()->index(selected.row(), 0).data().toInt();
        for (auto index = 0; query.next(); ++index)
            if (query.value(0).toInt() == curItem) {
                found = index;
                break;
            }
    }

    ui->staffView->setModel(queryModel);
    if (found != -1)
        ui->staffView->setCurrentIndex(ui->staffView->model()->index(found, selected.column()));
}

void MainWindow::refreshAlgoTree(const QModelIndex &cur)
{
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

void MainWindow::operNames_selectionChanged()
{
    auto curRow = ui->operNames->currentIndex().row();
    auto query = qobject_cast<QSqlQueryModel*>(ui->operNames->model())->query();
    if (query.seek(curRow)) {
        ui->operDesc->clear();
        ui->operDesc->insertPlainText(query.value(2).toString());
    }
}

void MainWindow::orderNames_selectionChanged()
{
    auto cur = ui->orderNames->currentIndex();
    auto query = qobject_cast<QSqlQueryModel*>(ui->orderNames->model())->query();
    if (query.seek(cur.row())) {
        ui->orderDesc->clear();
        ui->orderDesc->insertPlainText(query.value(2).toString());
    }
    refreshAlgoTree(cur);
}

void MainWindow::resizeTableHeader()
{
    ui->operNames->horizontalHeader()->setDefaultSectionSize(ui->operNames->geometry().width());
    ui->orderNames->horizontalHeader()->setDefaultSectionSize(ui->orderNames->geometry().width());
}
