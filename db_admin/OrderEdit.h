#pragma once

#include <QAbstractTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QWizard>

namespace Ui {
class OrderEdit;
}

struct dependItem {
    int id;
    bool isParent;
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
    void on_lineEdit_editingFinished();
    void on_algoList_doubleClicked(const QModelIndex&);
    void on_operNames_doubleClicked(const QModelIndex& index);
    void on_act_editParents_triggered();
    void on_act_deleteItem_triggered();

    void on_algoList_customContextMenuRequested(const QPoint &pos);

private:
    explicit OrderEdit(QWidget* parent, QSqlDatabase& db, int orderId = -1);
    bool checkUniqueOrderTitle(const QString& text);
    QString getOperTitle(int operId);

    int m_id;
    QSqlDatabase& m_db;
    QSqlQuery m_orderNames;
    QSqlQuery m_operNames;
    QVector<QPair<int, QVector<dependItem>>> m_algoList;
    Ui::OrderEdit* ui;
};

class AlgoModel : public QAbstractTableModel {
    Q_OBJECT
    friend class OrderEdit;

public:
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;

private:
    explicit AlgoModel(OrderEdit& data, QObject* parent = Q_NULLPTR);
    static QString parentStr(const QVector<dependItem>& x);

    OrderEdit& m_data;
};
