#pragma once

#include <BasicListModel.h>
#include <QAbstractListModel>
#include <QSqlDatabase>

struct Operation : BasicItem {
    explicit Operation(int id = 0,
        const QString& title = QString::null,
        bool isActive = true,
        const QString& desc = QString::null);
    QString desc;
};

class OperationListModel : public BasicListModel {
    Q_OBJECT
public:
    enum createFlags { LoadInactive = 0x1, LoadDescription = 0x2 };

    static OperationListModel* createFromDb(QObject* parent = Q_NULLPTR,
        int flags = LoadDescription,
        QSqlDatabase db = QSqlDatabase::database());

private:
    explicit OperationListModel(
        QObject* parent, const dataType& data, bool activeFlag, int activeCount);
};
