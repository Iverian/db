#include "OrderDependencyEdit.h"
#include "ui_OrderDependencyEdit.h"
#include "utility.h"

#include <QSqlQuery>
#include <QVariant>
#include <QVBoxLayout>

OrderDependencyEdit::OrderDependencyEdit(QWidget* parent, int orderId, int operId)
    : QDialog(parent)
    , m_orderId(orderId)
    , m_operId(operId)
{
    ui->setupUi(this);
}

void OrderDependencyEdit::setupList(const QSqlQuery &q)
{
    auto boxLayout = new QVBoxLayout(this);
    while(q.next()) {
        auto item = new MyCheckBox(q.value(1).toString(), boxLayout);
        item->id() = q.value(0).toInt();
        boxLayout->addWidget(item);
    }
    ui->buttonBox->setLayout(boxLayout);
}

void OrderDependencyEdit::edit(QWidget* parent, QSqlDatabase& db, int orderId, int operId)
{
    if (db.isOpen()) {
        db.transaction();
        auto strId = QString::number(orderId);
        auto correctId = getFirstIntQueryVal("SELECT COUNT (*) FROM Algorithm WHERE Id_orderType = " + strId + ";");
        if (correctId == 1) {
            OrderDependencyEdit edit(parent, orderId, operId);
            edit.setupList(db.exec("SELECT Id, Title FROM OrderTypes WHERE Id <> " + strId + " AND ;"));
            if (edit.exec() == QDialog::Accepted) {
                auto layout = ui->buttonBox->layout();
                for(const auto& i : layout->children()) {
                    auto ptr = qobject_cast<MyCheckBox*>(i);
                    if (ptr->isChecked()) {
                        db.exec("INSERT INTO ")
                    }
                }
            }
        }
        db.commit();
    }
}

OrderDependencyEdit::~OrderDependencyEdit() { delete ui; }

int& MyCheckBox::id() { return m_id; }

const int& MyCheckBox::id() const { return m_id; }
