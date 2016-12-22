#include <MainWindow.h>
#include <OperationEdit.h>
#include <OperationListModel.h>
#include <OrderEdit.h>
#include <OrderListModel.h>
#include <StaffMemberEdit.h>
#include <StaffMemberModel.h>
#include <databaseConnectionParams.h>
#include <ui_MainWindow.h>
#include <utility.h>

#include <QMessageBox>
#include <QSqlQueryModel>
#include <QStringListModel>

using namespace std;

const BasicItem& curListItem(QListView* view);

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connectToDb();
    refreshOperView();
    refreshOrderView();
    refreshStaffView();
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

void MainWindow::refreshListView(QListView* targetView, ModelSelector x, int flags)
{
    auto newModel = createFromDb(x, flags, this);
    auto newIndex = -1;
    if (targetView->model()) {
        auto curIndex = targetView->currentIndex().row();
        auto curId = reinterpret_cast<BasicListModel*>(targetView->model())->at(curIndex).id;
        newIndex
            = static_cast<int>(find_if(newModel->cont().cbegin(), newModel->cont().cend(),
                                   [&curId](const BasicListModel::dataType::const_iterator& iter) {
                                       return (*iter)->get_id() == curId;
                                   })
                - newModel->cont().cbegin());
        delete targetView->model();
    }
    targetView->setModel(newModel);
    if (newIndex >= 0 && newIndex < newModel->cont().size())
        targetView->setCurrentIndex(newModel->index(newIndex, 0));
}

void MainWindow::refreshOperView()
{
    refreshListView(ui->operNames, OperationModel,
        OperationListModel::LoadDescription | displayInactive() ? OperationListModel::LoadInactive
                                                                : 0);
    refreshOperInfo();
}

void MainWindow::refreshOrderView()
{
    refreshListView(ui->orderNames, OrderModel,
        OrderListModel::LoadDescription | OrderListModel::LoadAlgorithm | displayInactive()
            ? OrderListModel::LoadInactive
            : 0);
    refreshOrderInfo();
}

void MainWindow::refreshStaffView()
{
    refreshListView(ui->staffNames, StaffModel, StaffMemberModel::LoadSkills);
    refreshSkillView();
}

void MainWindow::refreshSkillView()
{
    ui->staffSkills->setModel(
        new QStringListModel(reinterpret_cast<StaffMember&>(curListItem(ui->staffNames)).skills));
}

void MainWindow::refreshOperInfo()
{
    ui->operDesc->setPlainText(reinterpret_cast<Operation&>(curListItem(ui->operNames)).desc);
}

void MainWindow::refreshOrderInfo()
{
    ui->orderDesc->setPlainText(reinterpret_cast<Order&>(curListItem(ui->orderNames)).desc);
}

void MainWindow::on_operNames_customContextMenuRequested(const QPoint& pos)
{
    popupMenu(pos, ui->operNames->viewport(),
        {ui->actNewOperation, ui->actEditOperation, ui->actDeleteOperation}, this);
}

void MainWindow::on_orderNames_customContextMenuRequested(const QPoint& pos)
{
    popupMenu(pos, ui->orderNames->viewport(),
        {ui->actNewOrder, ui->actEditOrder, ui->actDeleteOrder}, this);
}

void MainWindow::on_staffNames_customContextMenuRequested(const QPoint& pos)
{
    popupMenu(pos, ui->staffNames->viewport(),
        {ui->actNewStaffMember, ui->actEditStaffMember, ui->actDeleteStaffMember}, this);
}

void MainWindow::on_actNewOperation_triggered()
{
    OperationEdit::add(this, db);
    refreshOperView();
}

void MainWindow::on_actNewOrder_triggered()
{
    OrderEdit::add(this, db);
    refreshOrderView();
}

void MainWindow::on_actNewStaffMember_triggered()
{
    StaffMemberEdit::add(this, db);
    refreshStaffView();
}

void MainWindow::on_operNames_doubleClicked(const QModelIndex&)
{
    on_actEditOperation_triggered();
}

void MainWindow::on_orderNames_doubleClicked(const QModelIndex&)
{
    on_actEditOrder_triggered();
}

void MainWindow::on_staffNames_doubleClicked(const QModelIndex&)
{
    on_actEditStaffMember_triggered();
}

void MainWindow::on_actEditOperation_triggered()
{
    OperationEdit::edit(this, db, curListItem(ui->operNames).id);
    refreshOperView();
}

void MainWindow::on_actEditOrder_triggered()
{
    OrderEdit::edit(this, db, curListItem(ui->orderNames).id);
    refreshOrderView();
    refreshOrderInfo();
}

void MainWindow::on_actEditStaffMember_triggered()
{
    StaffMemberEdit::edit(this, curListItem(ui->staffNames).id, db);
    refreshStaffView();
}

void MainWindow::on_actDeleteOperation_triggered()
{
    auto id = curListItem(ui->operNames).id;
    db.transaction();
    auto activeOrderCount = getFirstQueryVal<int>(
        "WITH DependentOrders AS (SELECT Id_orderType FROM "
        "Algorithm WHERE Id_operationType = %1) "
        "SELECT COUNT(*) FROM Orders WHERE Id_orderType IN"
        "(SELECT Id_orderType FROM DependentOrders) AND NumOperations <> 0;"_q.arg(id),
        db);
    if (activeOrderCount != 0)
        QMessageBox::critical(
            this, "Action forbidden!", "Unable to deactivate used operation", QMessageBox::Ok);
    else {
        auto confirm = QMessageBox::warning(this, "Confirm action",
            "All dependent Orders will be deactivated too", QMessageBox::Ok, QMessageBox::Cancel);
        if (confirm == QMessageBox::Ok) {
            db.exec("UPDATE OperationTypes SET IsActive = false WHERE Id = %1;"_q.arg(id));
            db.exec(
                "UPDATE OrderTypes SET IsActive = false WHERE Id"
                " IN (SELECT Id_orderType FROM Algorithm WHERE Id_operationType = %1);"_q.arg(id));
        }
    }
    db.commit();
    refreshOperView();
    refreshOrderView();
}

void MainWindow::on_actDeleteOrder_triggered()
{
    auto id = curListItem(ui->orderNames).id;
    db.transaction();
    auto activeOrderCount = getFirstQueryVal<int>(
        "SELECT COUNT(*) FROM Orders WHERE Id_orderType = %1 AND NumOperations <> 0;"_q.arg(id),
        db);
    if (activeOrderCount != 0)
        QMessageBox::critical(
            this, "Action forbidden!", "Unable to deactivate running order", QMessageBox::Ok);
    else {
        auto confirm = QMessageBox::warning(this, "Confirm action",
            "Order will become inactive for clients", QMessageBox::Ok, QMessageBox::Cancel);
        if (confirm == QMessageBox::Ok)
            db.exec("UPDATE OrderTypes SET IsActive = false WHERE Id = %1;"_q.arg(id));
    }
    db.commit();
    refreshOrderView();
}

void MainWindow::on_actDeleteStaffMember_triggered()
{
    auto id = curListItem(ui->staffNames).id;
    db.transaction();
    auto activeOperCount = getFirstQueryVal<int>(
        "SELECT COUNT (*) FROM Operations WHERE Id_staff = %1 AND Status = 'running';"_q.arg(id),
        db);
    auto staffStatus = getFirstQueryVal<int>("SELECT Status FROM Staff WHERE Id = %1;"_q.arg(id));
    if (activeOperCount != 0 || staffStatus == StaffMember::LoggedIn)
        QMessageBox::critical(this, "Action forbidden!",
            "Unable to deactivate working staff member", QMessageBox::Ok);
    else {
        auto confirm = QMessageBox::warning(this, "Confirm action",
            "Staff member will be unable to work", QMessageBox::Ok, QMessageBox::Cancel);
        if (confirm == QMessageBox::Ok)
            db.exec("UPDATE Staff SET Status = 'deactivated' WHERE Id = %1;"_q.arg(id));
    }
    db.commit();
    refreshStaffView();
}

bool MainWindow::displayInactive()
{
    return ui->actDisplayInactive->isChecked();
}

void MainWindow::on_actDisplayInactive_changed()
{
    refreshOrderView();
    refreshOperView();
    refreshStaffView();
}

void MainWindow::on_staffNames_clicked(const QModelIndex&)
{
    refreshSkillView();
}

void MainWindow::on_orderNames_clicked(const QModelIndex&)
{
    refreshOrderInfo();
}

void MainWindow::on_operNames_clicked(const QModelIndex&)
{
    refreshOperView();
}

const BasicItem& curListItem(QListView* view)
{
    return toBasic(view->model())->at(view->currentIndex().row());
}