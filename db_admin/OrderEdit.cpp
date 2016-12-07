#include "OrderEdit.h"
#include "ui_OrderEdit.h"
#include "utility.h"
#include "OrderDependencyEdit.h"

#include <QAbstractButton>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include <iterator>

using namespace std;

OrderEdit::OrderEdit(QWidget* parent, QSqlDatabase& db, int orderId)
    : QWizard(parent)
    , m_id(orderId)
    , m_db(db)
    , m_orderNames(db)
    , m_operNames(db)
    , m_algoList()
    , ui(new Ui::OrderEdit)
{
    ui->setupUi(this);
}

bool OrderEdit::checkUniqueOrderTitle(const QString& text)
{
    auto retval = true;
    for (auto q = m_orderNames; q.next();)
        if (q.value(1).toString() == text) {
            retval = false;
            break;
        }
    return retval;
}

QString OrderEdit::getOperTitle(int operId)
{
    QString retval;
    for (auto q = m_operNames; q.next();)
        if (q.value(0).toInt() == operId) {
            retval = q.value(1).toString();
            break;
        }
    return retval;
}

void OrderEdit::add(QWidget* parent, QSqlDatabase& db)
{
    if (db.isOpen()) {
        db.transaction();
        OrderEdit edit(parent, db, -1);
        edit.setWindowIcon(QIcon(":/MainWindowRes/new_order.png"));
        edit.setWindowTitle("Add new order");
        edit.button(QWizard::NextButton)->setEnabled(false);
        if (edit.exec() == QDialog::Accepted) {
        }
        db.commit();
    }
}

void OrderEdit::edit(QWidget* parent, QSqlDatabase& db, int orderId) {}

OrderEdit::~OrderEdit() { delete ui; }

void OrderEdit::initializePage(int id)
{
    switch (id) {
    case 0:
        m_orderNames.exec((m_id == -1)
                ? "SELECT Id, Title FROM OrderTypes;"
                : "SELECT Id, Title FROM OrderTypes WHERE Id <> " + QString::number(m_id) + ";");
        break;
	case 1: {
        m_operNames.exec("SELECT Id, Title FROM OperationTypes;");
        auto operNamesModel = new QSqlQueryModel;
        operNamesModel->setQuery(m_operNames);
        ui->operNames->setModel(operNamesModel);
        break;
	}
    default:
        break;
    }
}

void OrderEdit::on_lineEdit_editingFinished()
{
    auto text = ui->lineEdit->text();
    if (button(QWizard::NextButton)->isEnabled()) {
        if (text.isEmpty() || !checkUniqueOrderTitle(text))
            button(QWizard::NextButton)->setEnabled(false);
    } else if (!text.isEmpty() && checkUniqueOrderTitle(text))
        button(QWizard::NextButton)->setEnabled(true);
}

void OrderEdit::on_algoList_doubleClicked(const QModelIndex&) {}

void OrderEdit::on_operNames_doubleClicked(const QModelIndex& index) {}

void OrderEdit::on_act_editParents_triggered()
{
	//OrderDependencyEdit::edit(this, )
}

void OrderEdit::on_act_deleteItem_triggered() {}

int AlgoModel::rowCount(const QModelIndex& parent) const
{
    return parent.isValid() ? m_data.m_algoList.size() : 0;
}

int AlgoModel::columnCount(const QModelIndex& parent) const { return parent.isValid() ? 2 : 0; }

QVariant AlgoModel::data(const QModelIndex& index, int role) const
{
    QVariant retval;
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            retval = QVariant::fromValue(m_data.getOperTitle(m_data.m_algoList.at(index.row()).first));
            break;
        case 1:
            retval = QVariant::fromValue(parentStr(m_data.m_algoList.at(index.row()).second));
            break;
        default:
            break;
        }
    }
    return retval;
}

QString AlgoModel::parentStr(const QVector<dependItem>& x)
{
    QString retval;
    for (auto i = x.begin(); i != x.end(); ++i)
		if (i->isParent)
            retval += i->id + (next(i) != x.end() ? ", " : "");
    return retval;
}

void OrderEdit::on_algoList_customContextMenuRequested(const QPoint& pos)
{
    popupMenu(pos, ui->algoList->viewport(), {ui->act_editParents, ui->act_deleteItem}, this);
}
