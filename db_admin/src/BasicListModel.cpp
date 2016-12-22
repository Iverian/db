#include "BasicListModel.h"

#include <OperationListModel.h>
#include <OrderListModel.h>
#include <QBrush>
#include <StaffMemberModel.h>

BasicListModel::BasicListModel(
    QObject* parent, const dataType& data, bool activeFlag, int activeCount)
    : QAbstractListModel(parent)
    , m_data(data)
    , m_activeFlag(activeFlag)
    , m_activeCount(activeCount)
{
}

QVariant BasicListModel::data(const QModelIndex& index, int role) const
{
    QVariant retval;
    if (role == Qt::DisplayRole)
        retval = m_data.at(index.row())->data;
    else
        retval = notDisplayData(index, role);
    return retval;
}

int BasicListModel::rowCount(const QModelIndex& parent) const
{
    return m_activeFlag ? m_activeCount : m_data.size();
}

const BasicListModel::dataType& BasicListModel::cont() const
{
    return m_data;
}

const BasicItem& BasicListModel::at(int i) const
{
    return *m_data[i];
}

int& BasicListModel::activeCount()
{
    return m_activeCount;
}

void BasicListModel::setActiveFlag(bool x)
{
    if (x != m_activeFlag)
        toggleActiveFlag();
    m_activeFlag = x;
}

void BasicListModel::toggleActiveFlag()
{
    if (m_activeFlag) {
        beginRemoveRows(QModelIndex(), m_activeCount, m_data.size() - 1);
        endRemoveRows();
    } else {
        beginInsertRows(QModelIndex(), m_activeCount, m_data.size() - 1);
        endInsertRows();
    }
}

QVariant BasicListModel::notDisplayData(const QModelIndex& index, int role) const
{
    QVariant retval;
    if (role == Qt::ForegroundRole)
        retval = at(index.row()).isActive ? QBrush(Qt::black) : QBrush(Qt::lightGray);
    return retval;
}

BasicListModel* createFromDb(ModelSelector x, int flags, QObject* parent, QSqlDatabase db)
{
    BasicListModel* retval = nullptr;
    switch (x) {
    case OperationModel:
        retval = OperationListModel::createFromDb(parent, flags, db);
        break;
    case OrderModel:
        retval = OrderListModel::createFromDb(parent, flags, db);
        break;
    case StaffModel:
        retval = StaffMemberModel::createFromDb(parent, flags, db);
        break;
    default:
        break;
    }
    return retval;
}
