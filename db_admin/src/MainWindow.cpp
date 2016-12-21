#include "MainWindow.h"
#include "OperationEdit.h"
#include "OrderEdit.h"
#include "StaffMemberEdit.h"
#include "databaseConnectionParams.h"
#include "ui_MainWindow.h"
#include "utility.h"

#include <QMessageBox>
#include <QSqlError>
#include <QSqlQueryModel>

QModelIndex refreshTableHelper(
	QTableView* tableView, const QString& query, QSqlDatabase& db);

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
	auto found = refreshTableHelper(ui->operNames,
		"SELECT Id,Title,Description%1 FROM OperationTypes%2"_q
			.arg(!displayInactive() ? "" : ",IsActive")
			.arg(!displayInactive() ? " WHERE IsActive = true;" : ";"),
		db);
	ui->operNames->setColumnHidden(0, true);
	ui->operNames->setColumnHidden(2, true);
	ui->operDesc->clear();
	if (displayInactive()) {
		auto q = reinterpret_cast<QSqlQueryModel*>(ui->operNames->model())->query();
		q.next();
		for (auto i = 0; q.isValid(); q.next(), ++i)
			if (!q.value(3).toBool())
				ui->operNames->model()->setData(ui->operNames->model()->index(i, 3),
					QBrush(Qt::lightGray), Qt::ForegroundRole);
	}
	connect(ui->operNames->selectionModel(),
		SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
		SLOT(operNames_selectionChanged()));

	if (found.isValid())
		ui->operNames->setCurrentIndex(found);
}

void MainWindow::refreshOrderView()
{
	auto found = refreshTableHelper(ui->orderNames,
		"SELECT Id, Title, Description FROM OrderTypes%1"_q.arg(
			!displayInactive() ? " WHERE IsActive = true;" : ";"),
		db);

	ui->orderNames->setColumnHidden(0, true);
	ui->orderNames->setColumnHidden(2, true);

	ui->orderDesc->clear();
	ui->orderAlgo->setModel(Q_NULLPTR);

	connect(ui->orderNames->selectionModel(),
		SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
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
		{ui->actNewOperation, ui->actEditOperation, ui->actDeleteOperation}, this);
}

void MainWindow::on_orderNames_customContextMenuRequested(const QPoint& pos)
{
	popupMenu(pos, ui->orderNames->viewport(),
		{ui->actNewOrder, ui->actEditOrder, ui->actDeleteOrder}, this);
}

void MainWindow::on_staffView_customContextMenuRequested(const QPoint& pos)
{
	popupMenu(pos, ui->staffView->viewport(),
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
	refreshAlgoTree();
}

void MainWindow::on_actNewStaffMember_triggered() { StaffMemberEdit::add(db, this); }

void MainWindow::on_operNames_doubleClicked(const QModelIndex&)
{
	on_actEditOperation_triggered();
}

void MainWindow::on_orderNames_doubleClicked(const QModelIndex&)
{
	on_actEditOrder_triggered();
}

void MainWindow::on_staffView_doubleClicked(const QModelIndex&)
{
	on_actEditStaffMember_triggered();
}

void MainWindow::on_actEditOperation_triggered()
{
	OperationEdit::edit(this, db, ui->operNames->model()
									  ->index(ui->operNames->currentIndex().row(), 0)
									  .data()
									  .toInt());
	refreshOperView();
}

void MainWindow::on_actEditOrder_triggered()
{
	OrderEdit::edit(this, db, ui->orderNames->model()
								  ->index(ui->orderNames->currentIndex().row(), 0)
								  .data()
								  .toInt());
	refreshOrderView();
	refreshAlgoTree();
}

void MainWindow::on_actEditStaffMember_triggered()
{
	StaffMemberEdit::edit(ui->staffView->model()
							  ->index(ui->staffView->currentIndex().row(), 0)
							  .data()
							  .toInt(),
		db, this);
	refreshStaffView();
}

void MainWindow::on_actDeleteOperation_triggered()
{
	auto id = ui->operNames->model()
				  ->index(ui->operNames->currentIndex().row(), 0)
				  .data()
				  .toInt();
	db.transaction();
	auto activeOrderCount = getFirstQueryVal<int>(
		"WITH DependentOrders AS (SELECT Id_orderType FROM "
		"Algorithm WHERE Id_operationType = %1) "
		"SELECT COUNT(*) FROM Orders WHERE Id_orderType IN"
		"(SELECT Id_orderType FROM DependentOrders) AND NumOperations <> 0;"_q.arg(id),
		db);
	if (activeOrderCount != 0)
		QMessageBox::critical(this, "Action forbidden!",
			"Unable to deactivate used operation", QMessageBox::Ok);
	else {
		auto confirm = QMessageBox::warning(this, "Confirm action",
			"All dependent Orders will be deactivated too", QMessageBox::Ok,
			QMessageBox::Cancel);
		if (confirm == QMessageBox::Ok) {
			db.exec(echo << "UPDATE OperationTypes SET IsActive = false WHERE Id = %1;"_q
								.arg(id));
			db.exec(
				"UPDATE OrderTypes SET IsActive = false WHERE Id"
				" IN (SELECT Id_orderType FROM Algorithm WHERE Id_operationType = %1);"_q
					.arg(id));
		}
	}
	db.commit();
	refreshOperView();
	refreshOrderView();
	refreshAlgoTree();
}

void MainWindow::on_actDeleteOrder_triggered()
{
	auto id = ui->orderNames->model()
				  ->index(ui->orderNames->currentIndex().row(), 0)
				  .data()
				  .toInt();
	db.transaction();
	auto activeOrderCount = getFirstQueryVal<int>(
		"SELECT COUNT(*) FROM Orders WHERE Id_orderType = %1 AND NumOperations <> 0;"_q
			.arg(id),
		db);
	if (activeOrderCount != 0)
		QMessageBox::critical(this, "Action forbidden!",
			"Unable to deactivate running order", QMessageBox::Ok);
	else {
		auto confirm = QMessageBox::warning(this, "Confirm action",
			"Order will become inactive for clients", QMessageBox::Ok,
			QMessageBox::Cancel);
		if (confirm == QMessageBox::Ok)
			db.exec("UPDATE OrderTypes SET IsActive = false WHERE Id = %1;"_q.arg(id));
	}
	db.commit();

	refreshOrderView();
	refreshAlgoTree();
}

void MainWindow::on_actDeleteStaffMember_triggered()
{
	auto id = ui->staffView->model()
				  ->index(ui->staffView->currentIndex().row(), 0)
				  .data()
				  .toString();

	db.transaction();
	auto activeOperCount = getFirstQueryVal<int>(
		"SELECT COUNT (*) FROM Operations WHERE Id_staff = %1 AND Status = 'running';"_q
			.arg(id),
		db);
	auto staffStatus
		= getFirstQueryVal<int>("SELECT Status FROM Staff WHERE Id = %1;"_q.arg(id));
	// TODO: check how Qt handles PSQL ENUMS
	if (activeOperCount != 0 || staffStatus == 2)
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

void MainWindow::operNames_selectionChanged()
{
	auto curRow = ui->operNames->currentIndex().row();
	auto query = reinterpret_cast<QSqlQueryModel*>(ui->operNames->model())->query();
	if (query.seek(curRow)) {
		ui->operDesc->clear();
		ui->operDesc->insertPlainText(query.value(2).toString());
	}
}

void MainWindow::orderNames_selectionChanged()
{
	auto cur = ui->orderNames->currentIndex();
	auto query = reinterpret_cast<QSqlQueryModel*>(ui->orderNames->model())->query();
	if (query.seek(cur.row())) {
		ui->orderDesc->clear();
		ui->orderDesc->insertPlainText(query.value(2).toString());
	}
	refreshAlgoTree();
}

bool MainWindow::displayInactive() { return ui->actDisplayInactive->isChecked(); }

void MainWindow::resizeTableHeader()
{
	ui->operNames->horizontalHeader()->setDefaultSectionSize(ui->operNames->width());
	ui->orderNames->horizontalHeader()->setDefaultSectionSize(ui->orderNames->width());
}

QModelIndex refreshTableHelper(
	QTableView* tableView, const QString& query, QSqlDatabase& db)
{
	QModelIndex retval;
	auto queryModel = new QSqlQueryModel;
	auto sel = tableView->currentIndex();
	queryModel->setQuery(query, db);
	outQuery_(query, db);
	auto found = -1;
	if (sel.row() != -1) {
		auto q = queryModel->query();
		auto cur = tableView->model()->index(sel.row(), 0).data().toInt();
		for (auto i = 0; q.next(); ++i)
			if (q.value(0) == cur) {
				found = i;
				break;
			}
	}
	if (found != -1)
		retval = tableView->model()->index(found, sel.column());
	tableView->setModel(queryModel);
	return retval;
}

void MainWindow::on_actDisplayInactive_changed()
{
	refreshOrderView();
	refreshAlgoTree();
	refreshOperView();
}
