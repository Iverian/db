#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();
private:
    Ui::MainWindow* ui;
};
