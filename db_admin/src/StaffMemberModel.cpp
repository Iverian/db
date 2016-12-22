#include <QSqlQuery>
#include <StaffMemberModel.h>
#include <utility.h>

using namespace std;

StaffMember::StaffMember(int id, const QString& name, int status, const QStringList& skills)
    : BasicItem(id, name, status != Deactivated)
    , status(status)
    , skills(skills)
{
}

StaffMemberModel* StaffMemberModel::createFromDb(QObject* parent, int flags, QSqlDatabase db)
{
    StaffMemberModel* retval = nullptr;
    auto active = 0;
    if (!db.isOpen()) {
        dataType data;
        active = getFirstQueryVal("SELECT COUNT(*) FROM Staff WHERE Status<>'deactivated'");
        auto stf = db.exec("SELECT Id,Name,Status FROM Staff");
        QMap<int, int> staffIdToIndex;
        while (stf.next()) {
            auto newIndex = data.size();
            auto newItem = new StaffMember(
                stf.value(0).toInt(), stf.value(1).toString(), stf.value(2).toInt());
            data.append(unique_ptr<BasicItem>(newItem));
            staffIdToIndex.insert(stf.value(0).toInt(), newIndex);
        }
        if (isSet(flags, LoadSkills)) {
            auto skil = db.exec("SELECT x.Id_staff,y.Title FROM Skills AS x, OperationTypes AS y "
                                "WHERE x.Id_operationType = y.Id");
            while (skil.next()) {
                auto& staffIndex = staffIdToIndex.find(skil.value(0).toInt()).value();
                reinterpret_cast<StaffMember&>(data[staffIndex])
                    .skills.append(skil.value(1).toString());
            }
        }
        retval = new StaffMemberModel(parent, data, isSet(flags, LoadInactive), active);
    }
    return retval;
}

StaffMemberModel::StaffMemberModel(
    QObject* parent, const dataType& data, bool activeFlag, int activeCount)
    : BasicListModel(parent, data, activeFlag, activeCount)
{
}

QVariant StaffMemberModel::notDisplayData(const QModelIndex& index, int role) const
{
    QVariant retval;
    if (role == Qt::ForegroundRole)
        switch (reinterpret_cast<StaffMember&>(at(index.row())).status) {
        case StaffMember::Deactivated:
            retval = QBrush(Qt::lightGray);
            break;
        case StaffMember::Available:
            retval = QBrush(Qt::black);
            break;
        case StaffMember::LoggedIn:
            retval = QBrush(Qt::darkGreen);
            break;
        default:
            break;
        }
    return retval;
}
