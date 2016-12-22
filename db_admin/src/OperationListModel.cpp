#include "OperationListModel.h"

#include <QSqlQuery>
#include <utility.h>

using namespace std;

Operation::Operation(int id, const QString& title, bool isActive, const QString& desc)
    : BasicItem(id, title, isActive)
    , desc(desc)
{
}

OperationListModel* OperationListModel::createFromDb(QObject* parent, int flags, QSqlDatabase db)
{
    OperationListModel* retval = nullptr;
    dataType data;
    int active = 0;
    if (db.isOpen()) {
        active
            = getFirstQueryVal<int>("SELECT COUNT(*) FROM OperationTypes WHERE IsActive=true", db);
        auto q = db.exec(
            "SELECT Id,Title,IsActive%1 FROM OperationTypes ORDER BY not(IsActive);"_q.arg(
                isSet(flags, LoadDescription) ? ",Description" : ""));
        while (q.next()) {
            auto newItem
                = new Operation(q.value(0).toInt(), q.value(1).toString(), q.value(2).toBool());
            if (isSet(flags, LoadDescription))
                newItem->desc = q.value(3).toString();
            data.append(unique_ptr<BasicItem>(newItem));
        }
        retval = new OperationListModel(parent, data, isSet(flags, LoadInactive), active);
    }
    return retval;
}

OperationListModel::OperationListModel(
    QObject* parent, const dataType& data, bool activeFlag, int activeCount)
    : BasicListModel(parent, data, activeFlag, activeCount)
{
}
