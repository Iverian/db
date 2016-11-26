#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>
#include <windows.h>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:


    void on_add_order_clicked();

    void on_delete_client_order_clicked();

    void on_send_order_clicked();

private:
    Ui::MainWindow *ui;
    void connectDB();
    void init();
    void add_new_order();
};

#endif // MAINWINDOW_H
