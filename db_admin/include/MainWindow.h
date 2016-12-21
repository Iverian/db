#pragma once

#include <QMainWindow>
#include <QSqlDatabase>
#include <QModelIndex>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();
protected:
	void resizeEvent(QResizeEvent *event) override;
private slots:
	void on_actNewOperation_triggered();
	void on_actNewOrder_triggered();
	void on_actNewStaffMember_triggered();

	void on_operNames_customContextMenuRequested(const QPoint &pos);
	void on_orderNames_customContextMenuRequested(const QPoint &pos);
	void on_staffView_customContextMenuRequested(const QPoint &pos);

	void on_operNames_doubleClicked(const QModelIndex &);
	void on_orderNames_doubleClicked(const QModelIndex &);
	void on_staffView_doubleClicked(const QModelIndex &);
	void on_actEditOperation_triggered();
	void on_actEditOrder_triggered();
	void on_actEditStaffMember_triggered();

	void on_actDeleteOperation_triggered();
	void on_actDeleteOrder_triggered();
	void on_actDeleteStaffMember_triggered();

	void operNames_selectionChanged();
	void orderNames_selectionChanged();

	void on_actDisplayInactive_changed();

private:
	bool displayInactive();
	void resizeTableHeader();
	void connectToDb();
	void refreshOperView();
	void refreshOrderView();
	void refreshStaffView();

	void refreshAlgoTree();

	void editOper(const QModelIndex &index);
	void editOrder(const QModelIndex &index);
	void editStaff(const QModelIndex &index);

	QSqlDatabase db;
	Ui::MainWindow *ui;
};
