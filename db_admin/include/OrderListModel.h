#pragma once

#include <BasicListModel.h>

#include <QAbstractListModel>
#include <QSet>
#include <QSqlDatabase>
#include <QString>

struct Order : BasicItem {
    struct AlgoItem {
        explicit AlgoItem(int operId = 0, const QSet<int>& parentIndex = QSet<int>());
        int operId;
        QSet<int> parentIndex;
    };
    explicit Order(int id = 0,
        const QString& title = QString::null,
        bool isActive = true,
        const QString& desc = QString::null,
        const QVector<AlgoItem>& algo = QVector<AlgoItem>());
    QString desc;
    QVector<AlgoItem> algo;
};

class OrderListModel : public BasicListModel {
    Q_OBJECT
public:
    enum createFlags { LoadInactive = 0x1, LoadDescription = 0x2, LoadAlgorithm = 0x4 };

    static OrderListModel* createFromDb(QObject* parent = Q_NULLPTR,
        int flags = LoadAlgorithm,
        QSqlDatabase db = QSqlDatabase::database());

private:
    explicit OrderListModel(
        QObject* parent, const dataType& data, bool activeFlag, int activeCount);
};
