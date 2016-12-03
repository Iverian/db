#ifndef ORDEREDIT_H
#define ORDEREDIT_H

#include <QWizard>

namespace Ui {
class OrderEdit;
}

class OrderEdit : public QWizard
{
    Q_OBJECT

public:
    explicit OrderEdit(QWidget *parent = 0);
    ~OrderEdit();

private:
    Ui::OrderEdit *ui;
};

#endif // ORDEREDIT_H
