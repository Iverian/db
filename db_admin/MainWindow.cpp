#include "MainWindow.h"
#include "OperationEdit.h"
#include "databaseConnectionParams.h"
#include "ui_MainWindow.h"
#include "utility.h"

#include <QMenu>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include <QDebug>

void popupMenu(
    const QPoint& pos, QWidget* viewport, const std::initializer_list<QAction*>& actList, QWidget* parent);

QModelIndex refreshTableHelper(QTableView* tableView, const QString& query, QSqlDatabase& db);

MainWindow::MainWindow(QWidget* parent)
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

void MainWindow::resizeEvent(QResizeEvent* event)
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
    auto found = refreshTableHelper(ui->operNames, "SELECT Id, Title, Description FROM OperationTypes", db);

	ui->operNames->setColumnHidden(0, true);
	ui->operNames->setColumnHidden(2, true);

	ui->operDesc->clear();

    connect(ui->operNames->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
		SLOT(operNames_selectionChanged()));

	if (found.isValid())
		ui->operNames->setCurrentIndex(found);
}

void MainWindow::refreshOrderView()
{
    auto found = refreshTableHelper(ui->orderNames, "SELECT Id, Title, Description FROM OrderTypes", db);

	ui->orderNames->setColumnHidden(0, true);
	ui->orderNames->setColumnHidden(2, true);

	ui->orderDesc->clear();
	ui->orderAlgo->setModel(Q_NULLPTR);

    connect(ui->orderNames->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
		SLOT(orderNames_selectionChanged()));

	if (found.isValid())
		ui->orderNames->setCurrentIndex(found);
}

void MainWindow::refreshStaffView()
{
    auto found = refreshTableHelper(ui->staffView, "SELECT Id, Name FROM Staff", db);
	if (found.isValid())
		ui->staffView->setCurrentIndex(found);
}

void MainWindow::refreshAlgoTree() {}

void MainWindow::on_operNames_customContextMenuRequested(const QPoint& pos)
{
	popupMenu(pos, ui->operNames->viewport(),
		{ ui->actNewOperation, ui->actEditOperation, ui->actDeleteOperation }, this);
}

void MainWindow::on_orderNames_customContextMenuRequested(const QPoint& pos)
{
    popupMenu(
        pos, ui->orderNames->viewport(), { ui->actNewOrder, ui->actEditOrder, ui->actDeleteOrder }, this);
}

void MainWindow::on_staffView_customContextMenuRequested(const QPoint& pos)
{
    popupMenu(pos, ui->staffView->viewport(),
        { ui->actNewStaffMember, ui->actEditStaffMember, ui->actDeleteStaffMember }, this);
}

void popupMenu(const QPoint& pos, QWidget* viewport, const std::initializer_list<QAction*>& actList,
    QWidget* parent = Q_NULLPTR)
{
	auto menu = new QMenu(parent);
	for (auto& i : actList)
		menu->addAction(i);
	menu->popup(viewport->mapToGlobal(pos));
}

void MainWindow::on_actNewOperation_triggered()
{
    OperationEdit::add(this, db);
    refreshOperView();
}

void MainWindow::on_actNewOrder_triggered() {}

void MainWindow::on_actNewStaffMember_triggered() {}

void MainWindow::on_operNames_doubleClicked(const QModelIndex&) { on_actEditOperation_triggered(); }

void MainWindow::on_orderNames_doubleClicked(const QModelIndex& index) {}

void MainWindow::on_staffView_doubleClicked(const QModelIndex& index) {}

void MainWindow::on_actEditOperation_triggered()
{
    OperationEdit::edit(
        this, db, ui->operNames->model()->index(ui->operNames->currentIndex().row(), 0).data().toInt());
    refreshOperView();
}

void MainWindow::on_actEditOrder_triggered() {}

void MainWindow::on_actEditStaffMember_triggered() {}

void MainWindow::on_actDeleteOperation_triggered()
{
    auto id = ui->operNames->model()->index(ui->operNames->currentIndex().row(), 0).data().toString();

    db.transaction();
    auto activeOrderCount = getFirstIntQueryVal(
        "WITH DependentOrders AS (SELECT Id_orderType FROM Algorithm WHERE Id_operationType = " + id
            + ")"
              "SELECT COUNT (*) FROM Orders WHERE Id_orderType IN DependentOrders AND NumOperations <> 0;",
        db);
    if (activeOrderCount != 0)
        QMessageBox::critical(
            this, "Action forbidden!", "Unable to deactivate used operation", QMessageBox::Ok);
    else {
        auto confirm = QMessageBox::warning(this, "Confirm action",
            "All dependant Orders will be deactivated too", QMessageBox::Ok, QMessageBox::Cancel);
        if (confirm == QMessageBox::Ok)
            db.exec("UPDATE OperationTypes IsActive = false WHERE Id = " + id
                + ";"
                  "WITH DependentOrders AS (SELECT Id_orderType FROM Algorithm WHERE Id_operationType = "
                + id + ")"
                       "UPDATE OrderTypes IsActive = false WHERE Id IN DependentOrders;");
    }
    db.commit();

    refreshOperView();
    refreshOrderView();
    refreshAlgoTree();
}

void MainWindow::on_actDeleteOrder_triggered()
{
    auto id = ui->orderNames->model()->index(ui->orderNames->currentIndex().row(), 0).data().toString();

    db.transaction();
    auto activeOrderCount = getFirstIntQueryVal(
        "SELECT COUNT (*) FROM Orders WHERE Id_orderType = " + id + " AND NumOperations <> 0;", db);
    if (activeOrderCount != 0)
        QMessageBox::critical(
            this, "Action forbidden!", "Unable to deactivate running order", QMessageBox::Ok);
    else {
        auto confirm = QMessageBox::warning(this, "Confirm action", "Order will become inactive for clients",
            QMessageBox::Ok, QMessageBox::Cancel);
        if (confirm == QMessageBox::Ok)
            db.exec("UPDATE OrderTypes IsActive = false WHERE Id = " + id + ";");
    }
    db.commit();

    refreshOrderView();
    refreshAlgoTree();
}

void MainWindow::on_actDeleteStaffMember_triggered()
{
    auto id = ui->staffView->model()->index(ui->staffView->currentIndex().row(), 0).data().toString();

    db.transaction();
    auto activeOperCount = getFirstIntQueryVal(
        "SELECT COUNT (*) FROM Operations WHERE Id_staff = " + id + " AND Status = 'running';", db);
    auto staffStatus = getFirstIntQueryVal("SELECT Status FROM Staff WHERE Id = " + id + ";");
    // TODO: проверить как ведет себя Qt с ENUM типами PSQL
    if (activeOperCount != 0 || staffStatus == 2)
        QMessageBox::critical(
            this, "Action forbidden!", "Unable to deactivate working staff member", QMessageBox::Ok);
    else {
        auto confirm = QMessageBox::warning(this, "Confirm action", "Staff member will be unable to work",
            QMessageBox::Ok, QMessageBox::Cancel);
        if (confirm == QMessageBox::Ok)
            db.exec("UPDATE Staff StaffStatus = 'deactivated' WHERE Id = " + id + ";");
    }
    db.commit();

    refreshStaffView();
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
    refreshAlgoTree();
}

void MainWindow::resizeTableHeader()
{
	ui->operNames->horizontalHeader()->setDefaultSectionSize(ui->operNames->width());
	ui->orderNames->horizontalHeader()->setDefaultSectionSize(ui->orderNames->width());
}

QModelIndex refreshTableHelper(QTableView* tableView, const QString& query, QSqlDatabase& db)
{
    QModelIndex retval;
    auto queryModel = new QSqlQueryModel;
    auto sel = tableView->currentIndex();
    queryModel->setQuery(query, db);
    auto found = -1;
    if (sel.row() != -1) {
        auto q = queryModel->query();
        auto cur = tableView->model()->index(sel.row(), 0).data().toInt();
        for (auto i = 0; q.next(); ++i)
            if (q.value(0).toInt() == cur) {
                found = i;
                break;
            }
    }
    if (found != -1)
        retval = tableView->model()->index(found, sel.column());
    tableView->setModel(queryModel);
    return retval;
}
