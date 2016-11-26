#ifndef ADDNEWSTAFFMEMBER_H
#define ADDNEWSTAFFMEMBER_H

#include <QDialog>

namespace Ui {
class AddNewStaffMember;
}

class AddNewStaffMember : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewStaffMember(QWidget *parent = 0);
    ~AddNewStaffMember();

private:
    Ui::AddNewStaffMember *ui;
};

#endif // ADDNEWSTAFFMEMBER_H
