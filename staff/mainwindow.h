#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_get_operation_clicked();

    void on_operation_done_clicked();

private:
    Ui::MainWindow *ui;
    QString staff_id;
    QString operation_id;
    void connectDB();
    bool user_exist();
    QString get_staff_id();
    bool hasRunningOp();
};

#endif // MAINWINDOW_H
