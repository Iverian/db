#pragma once

#include <AlgoModel.h>
#include <OperationListModel.h>

#include <QMap>
#include <QPair>
#include <QSet>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVector>
#include <QWizard>

namespace Ui {
class OrderEdit;
}

class OrderEdit : public QWizard {

    Q_OBJECT
    friend class AlgoModel;

public:
    explicit OrderEdit(QWidget* parent, QSqlDatabase& db, int orderId = -1);
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
    bool checkUniqueOrderTitle(const QString& text);
    QString getOperTitle(int operId);
    void initializeEditPage(int id);
    void insertAlgo(int orderId);

    int m_id;
    QSqlDatabase& m_db;
    AlgoModel* m_algoModel;
    OperationListModel* m_oprNames;
    QSet<QString> m_ordNames;
    Ui::OrderEdit* ui;
};
