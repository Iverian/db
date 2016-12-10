#pragma once

#include <QAbstractTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QWizard>

#include <map>
#include <memory>
#include <set>
#include <vector>

namespace Ui {
class OrderEdit;
}

class OrderEdit;

class AlgoModel : public QAbstractTableModel {
    Q_OBJECT
    friend class OrderEdit;

public:
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

private:
    explicit AlgoModel(OrderEdit* parent);
    static QString parentStr(const std::set<int>& x);

    OrderEdit& m_data;
};

class OrderEdit : public QWizard {
    Q_OBJECT
    friend class AlgoModel;

public:
    ~OrderEdit();
    static void add(QWidget* parent, QSqlDatabase& db);
    static void edit(QWidget* parent, QSqlDatabase& db, int orderId);

protected:
    void initializePage(int id) override;
private slots:
    void on_orderTitle_editingFinished();
    void on_algoList_doubleClicked(const QModelIndex&);
    void on_operNames_doubleClicked(const QModelIndex& index);
    void on_act_editParents_triggered();
    void on_act_deleteItem_triggered();

    void on_algoList_customContextMenuRequested(const QPoint& pos);

private:
    struct algoItem {
        int id;
        QString title;
        std::set<int> parentIndex;

    };

    explicit OrderEdit(QWidget* parent, QSqlDatabase& db, int orderId = -1);

    bool checkUniqueOrderTitle(const QString& text);
    QString getOperTitle(int operId);
    void initializeEditPage(int id);
    void insertAlgo(int orderId);

    int m_id;
    QSqlDatabase& m_db;
    AlgoModel* m_algoModel;

    std::set<QString> m_ordNames;
    std::vector<std::pair<int, QString>> m_oprNames;
    std::vector<algoItem> m_algoList;

    Ui::OrderEdit* ui;
};
