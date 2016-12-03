#include "MainWindow.h"
#include "databaseConnectionParams.h"
#include "ui_MainWindow.h"

#include <QMenu>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include <QDebug>

#define refreshTableHelper(_table_view_, _query_)                                                           \
    [this]() {                                                                                              \
        QModelIndex __retval;                                                                               \
        auto __queryModel = new QSqlQueryModel;                                                             \
        auto __sel = (_table_view_)->currentIndex();                                                        \
        __queryModel->setQuery(_query_, db);                                                                \
        auto __found = -1;                                                                                  \
        if (__sel.row() != -1) {                                                                            \
            auto __q = __queryModel->query();                                                               \
            auto __cur = (_table_view_)->model()->index(__sel.row(), 0).data().toInt();                     \
            for (auto __i = 0; __q.next(); ++__i)                                                           \
                if (__q.value(0).toInt() == __cur) {                                                        \
                    __found = __i;                                                                          \
                    break;                                                                                  \
                }                                                                                           \
        }                                                                                                   \
        if (__found != -1)                                                                                  \
            __retval = (_table_view_)->model()->index(__found, __sel.column());                             \
        (_table_view_)->setModel(__queryModel);                                                             \
        return __retval;                                                                                    \
	}()

void popupMenu(
    const QPoint& pos, QWidget* viewport, const std::initializer_list<QAction*>& actList, QWidget* parent);

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
    auto found = refreshTableHelper(ui->operNames, "select Id, Title, Description from OperationTypes");

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
    auto found = refreshTableHelper(ui->orderNames, "select Id, Title, Description from OrderTypes");

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
	auto found = refreshTableHelper(ui->staffView, "select Id, Name from Staff");
	if (found.isValid())
		ui->staffView->setCurrentIndex(found);
}

void MainWindow::refreshAlgoTree(const QModelIndex& cur) {}

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

void MainWindow::on_actNewOperation_triggered() {}

void MainWindow::on_actNewOrder_triggered() {}

void MainWindow::on_actNewStaffMember_triggered() {}

void MainWindow::on_operNames_doubleClicked(const QModelIndex& index) {}

void MainWindow::on_orderNames_doubleClicked(const QModelIndex& index) {}

void MainWindow::on_staffView_doubleClicked(const QModelIndex& index) {}

void MainWindow::on_actEditOperation_triggered() {}

void MainWindow::on_actEditOrder_triggered() {}

void MainWindow::on_actEditStaffMember_triggered() {}

void MainWindow::on_actDeleteOperation_triggered()
{
    auto id = ui->operNames->model()->index(ui->operNames->currentIndex().row(), 0).data().toString();

    auto q
        = db.exec("SELECT COUNT(*) FROM Operations WHERE Status = true AND Id_operationType = " + id + ";");
	q.next();
    if (q.value(0).toInt())
        QMessageBox::critical(
            this, "Action forbidden!", "Unable to delete active operation", QMessageBox::Ok);
    else {
        auto confirm = QMessageBox::critical(
            this, "Confirm action", "This action cannot be undone", QMessageBox::Ok, QMessageBox::Cancel);
        if (confirm == QMessageBox::Ok) {
            db.transaction();
            q = QSqlQuery(db);

            q.exec("DELETE FROM OrderTypes WHERE Id IN"
                   "(SELECT Id_orderType FROM Algorithm WHERE Id_operationType = "
                + id + ");");
            q.exec("WITH AlgoOper AS (SELECT Id FROM Algorithm WHERE Id_operationType = " + id
                + ")"
                  "DELETE FROM AlgDependencies WHERE (Id_parent IN AlgoOper) OR (Id_dependent IN "
                  "AlgoOper);");
            q.exec("DELETE FROM Algorithm WHERE Id_operationType = " + id + ";");
            q.exec("DELETE FROM Skills WHERE Id_operationType = " + id + ";");
            q.exec("DELETE FROM OperationTypes WHERE Id = " + id + ";");
            db.commit();
        }
	}
    refreshOperView();
    refreshOrderView();
    refreshStaffView();
}

void MainWindow::on_actDeleteOrder_triggered() {}

void MainWindow::on_actDeleteStaffMember_triggered() {}

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
	ui->operNames->horizontalHeader()->setDefaultSectionSize(ui->operNames->width());
	ui->orderNames->horizontalHeader()->setDefaultSectionSize(ui->orderNames->width());
}
