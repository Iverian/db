#include <AlgoModel.h>
#include <utility.h>

AlgoModel::AlgoModel(QObject* parent, const QVector<AlgoItem>& data)
    : QAbstractTableModel(parent)
    , m_data(data)
{
}

int AlgoModel::rowCount(const QModelIndex& parent) const
{
    return !parent.isValid() ? m_data.size() : 0;
}

int AlgoModel::columnCount(const QModelIndex& parent) const { return !parent.isValid() ? 2 : 0; }

QVariant AlgoModel::data(const QModelIndex& index, int role) const
{
    QVariant retval;
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            retval = QVariant::fromValue(m_data.at(index.row()).title);
            break;
        case 1:
            retval = QVariant::fromValue(parentsString(m_data.at(index.row()).parentIndex));
            break;
        default:
            break;
        }
    }
    return retval;
}

AlgoItem& AlgoModel::at(int index) { return m_data[index]; }

QString AlgoModel::parentsString(const QSet<int>& parentIndex) const
{
    QString retval;
    for (auto i = parentIndex.begin(); i != parentIndex.end(); ++i)
        retval += "%1%2"_q.arg(*i + 1).arg(std::next(i) == parentIndex.end() ? "" : ", ");
    return retval;
}

void AlgoModel::eraseRow(int i)
{
    QAbstractTableModel::beginRemoveRows(QModelIndex(), i, i);
    m_data.remove(i);
    QAbstractTableModel::endRemoveRows();
    for (auto& j : m_data)
        j.parentIndex.remove(i);
    dataChanged(index(0, 1), index(rowCount(), 1), {Qt::DisplayRole});
}

void AlgoModel::appendRow(const AlgoItem& newItem)
{
    QAbstractTableModel::beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data.append(newItem);
    QAbstractTableModel::endInsertRows();
}

void AlgoModel::updateRow(int i, const AlgoItem& newItem)
{
    if (newItem.id != -1)
        at(i) = newItem;
    dataChanged(index(i, 0), index(i, 1), {Qt::DisplayRole});
}
