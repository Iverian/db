#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();
private slots:
    void on_actNewOperation_triggered();
    void on_actNewOrder_triggered();
    void on_actNewStaffMember_triggered();

    void on_operNames_customContextMenuRequested(const QPoint &pos);
    void on_orderNames_customContextMenuRequested(const QPoint &pos);
    void on_staffView_customContextMenuRequested(const QPoint &pos);

    void on_operNames_doubleClicked(const QModelIndex &index);
    void on_orderNames_doubleClicked(const QModelIndex &index);
    void on_staffView_doubleClicked(const QModelIndex &index);
    void on_actEditOperation_triggered();
    void on_actEditOrder_triggered();
    void on_actEditStaffMember_triggered();

    void on_actDeleteOperation_triggered();
    void on_actDeleteOrder_triggered();
    void on_actDeleteStaffMember_triggered();

private:
    void connectToDb();
    void refreshOperView();
    void refreshOrderView();
    void refreshStaffView();

    void editOper(const QModelIndex& index);
    void editOrder(const QModelIndex& index);
    void editStaff(const QModelIndex& index);

    QSqlDatabase db;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
