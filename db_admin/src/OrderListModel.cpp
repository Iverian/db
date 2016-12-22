#include <OrderListModel.h>
#include <utility.h>

using namespace std;

Order::AlgoItem::AlgoItem(int operId, const QSet<int>& parentIndex)
    : operId(operId)
    , parentIndex(parentIndex)
{
}

Order::Order(int id, const QString& title, bool isActive, const QString& desc,
    const QVector<AlgoItem>& algo)
    : BasicItem(id, title, isActive)
    , desc(desc)
    , algo(algo)
{
}

OrderListModel* OrderListModel::createFromDb(QObject* parent, int flags, QSqlDatabase db)
{
    OrderListModel* retval = nullptr;
    auto active = 0;
    if (db.isOpen()) {
        dataType data;
        active = getFirstQueryVal("SELECT COUNT(*) FROM OrderTypes WHERE IsActive=true;", db);
        auto ord
            = db.exec("SELECT Id,Title,IsActive%1 FROM OrderTypes ORDER BY not(IsActive);"_q.arg(
                isSet(flags, LoadDescription) ? ",Description" : ""));
        QMap<int, int> orderIdToIndex;
        while (ord.next()) {
            auto newOrderIndex = data.size();
            auto newItem
                = new Order(ord.value(0).toInt(), ord.value(1).toString(), ord.value(2).toBool());
            if (isSet(flags, LoadDescription))
                newItem->desc = ord.value(3).toString();
            data.append(unique_ptr<BasicItem>(newItem));
            orderIdToIndex.insert(ord.value(0).toInt(), newOrderIndex);
        }
        if (isSet(flags, LoadAlgorithm)) {
            auto alg = db.exec("SELECT Id,Id_orderType,Id_operationType FROM Algorithm;");
            auto dep = db.exec("SELECT Id_parent,Id_dependent FROM AlgDependencies;");

            QMap<int, QPair<int, int>> algoIdToIndex;
            while (alg.next()) {
                auto& orderIndex = orderIdToIndex.find(alg.value(1).toInt()).value();
                auto newAlgoIndex = reinterpret_cast<Order&>(data[orderIndex]).algo.size();
                reinterpret_cast<Order&>(data[orderIndex])
                    .algo.append(Order::AlgoItem(alg.value(2).toInt()));
                algoIdToIndex.insert(alg.value(0).toInt(), {orderIndex, newAlgoIndex});
            }
            while (dep.next()) {
                auto& parentIndex = algoIdToIndex.find(dep.value(0).toInt()).value();
                auto& dependendIndex = algoIdToIndex.find(dep.value(1).toInt()).value();
                reinterpret_cast<Order&>(data[dependendIndex.first])
                    .algo[dependendIndex.second]
                    .parentIndex.insert(parentIndex.second);
            }
        }
        retval = new OrderListModel(parent, data, isSet(flags, LoadInactive), active);
    }
    return retval;
}

OrderListModel::OrderListModel(
    QObject* parent, const dataType& data, bool activeFlag, int activeCount)
    : BasicListModel(parent, data, activeFlag, activeCount)
{
}
