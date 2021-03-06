#pragma once

#include <QMainWindow>
#include <QModelIndex>
#include <QSqlDatabase>
#include <BasicListModel.h>
#include <QListView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = Q_NULLPTR);
	~MainWindow();

private slots:
	void on_actNewOperation_triggered();
	void on_actNewOrder_triggered();
	void on_actNewStaffMember_triggered();

	void on_operNames_customContextMenuRequested(const QPoint& pos);
	void on_orderNames_customContextMenuRequested(const QPoint& pos);
	void on_staffNames_customContextMenuRequested(const QPoint& pos);

	void on_operNames_doubleClicked(const QModelIndex&);
	void on_orderNames_doubleClicked(const QModelIndex&);
	void on_staffNames_doubleClicked(const QModelIndex&);

	void on_actEditOperation_triggered();
	void on_actEditOrder_triggered();
	void on_actEditStaffMember_triggered();

	void on_actDeleteOperation_triggered();
	void on_actDeleteOrder_triggered();
	void on_actDeleteStaffMember_triggered();

	void on_actDisplayInactive_changed();

	void on_staffNames_clicked(const QModelIndex&);
	void on_orderNames_clicked(const QModelIndex &);
	void on_operNames_clicked(const QModelIndex &);

private:
	bool displayInactive();
	void connectToDb();
	void refreshListView(QListView* targetView, ModelSelector x, int flags);
	void refreshOperView();
	void refreshOperInfo();
	void refreshOrderView();
	void refreshStaffView();
	void refreshSkillView();
	void refreshOrderInfo();

	QSqlDatabase db;
	Ui::MainWindow* ui;
};
