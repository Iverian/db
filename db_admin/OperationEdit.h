#pragma once

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class OperationEdit;
}

class OperationEdit : public QDialog {
    Q_OBJECT
    struct Operation {
        QString title;
        QString description;
    };

public:
    ~OperationEdit();
    static void add(QWidget* parent, QSqlDatabase& db);
    static void edit(QWidget* parent, QSqlDatabase& db, int operId);

private slots:
    void on_lineEdit_editingFinished();

private:
    explicit OperationEdit(QWidget* parent, QSqlDatabase& db, int operationId = -1);
    bool checkUniqueTitle(const QString& text);

    QSqlDatabase& m_db;
    int m_id;
    QStringList m_names;
    Ui::OperationEdit* m_ui;
};
