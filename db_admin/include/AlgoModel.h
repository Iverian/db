#pragma once

#include <QAbstractTableModel>
#include <QSet>
#include <QString>
#include <QVariant>
#include <QVector>

struct AlgoItem {
    int id;
    QString title;
    QSet<int> parentIndex;
};

class AlgoModel : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit AlgoModel(
        QObject* parent = Q_NULLPTR, const QVector<AlgoItem>& data = QVector<AlgoItem>());
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    void eraseRow(int i);
    void appendRow(const AlgoItem& newItem);
    void updateRow(int i, const AlgoItem& newItem = {-1, "", QSet<int>()});
    AlgoItem& at(int index);

private:
    QString parentsString(const QSet<int>& parentIndex) const;
    QVector<AlgoItem> m_data;
};
