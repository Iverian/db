#pragma once

#include <BasicListModel.h>
#include <QAbstractTableModel>
#include <QSqlDatabase>

struct StaffMember : BasicItem {
    enum Status { Deactivated, Available, LoggedIn };
    explicit StaffMember(int id = 0,
        const QString& name = QString::null,
        int status = Available,
        const QStringList& skills = QStringList());
    int status;
    QStringList skills;
};

class StaffMemberModel : public BasicListModel {
    Q_OBJECT
public:
    enum createFlags { LoadInactive = 0x1, LoadSkills = 0x2 };

    static StaffMemberModel* createFromDb(QObject* parent = Q_NULLPTR,
        int flags = LoadSkills,
        QSqlDatabase db = QSqlDatabase::database());

protected:
    QVariant notDisplayData(const QModelIndex& index, int role) const Q_DECL_OVERRIDE;

private:
    explicit StaffMemberModel(
        QObject* parent, const dataType& data, bool activeFlag, int activeCount);
};
