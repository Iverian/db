#pragma once

#include <BasicItem.h>
#include <QAbstractListModel>
#include <QSqlDatabase>
#include <memory>

enum ModelSelector { OperationModel, OrderModel, StaffModel };

template <class T>
BasicListModel*&& toBasic(T*&& ptr);

BasicListModel* createFromDb(ModelSelector x, int flags, QObject* parent = Q_NULLPTR,
    QSqlDatabase db = QSqlDatabase::database());

class BasicListModel : public QAbstractListModel {
    Q_OBJECT
public:
    using dataType = QVector<std::unique_ptr<BasicItem>>;

    explicit BasicListModel(
        QObject* parent, const dataType& data, bool activeFlag, int activeCount);

    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    const dataType& cont() const;
    const BasicItem& at(int i) const;
    int& activeCount();
    void setActiveFlag(bool x);

protected:
    void toggleActiveFlag();
    virtual QVariant notDisplayData(const QModelIndex& index, int role) const;

private:
    QVector<std::unique_ptr<BasicItem>> m_data;
    bool m_activeFlag;
    int m_activeCount;
};
