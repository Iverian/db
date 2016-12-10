#include "OrderEdit.h"
#include "OrderDependencyEdit.h"
#include "ui_OrderEdit.h"
#include "utility.h"

#include <QAbstractButton>
#include <QSqlQuery>
#include <QSqlQueryModel>

OrderEdit::OrderEdit(QWidget* parent, QSqlDatabase& db, int orderId)
    : QWizard(parent)
    , m_id(orderId)
    , m_algoModel(nullptr)
    , m_db(db)
    , m_algoList()
    , ui(new Ui::OrderEdit)
{
    ui->setupUi(this);
}

bool OrderEdit::checkUniqueOrderTitle(const QString& text) { return !contains(m_ordNames, text); }

QString OrderEdit::getOperTitle(int operId)
{
    return std::find_if(m_oprNames.begin(), m_oprNames.end(),
        [&operId](const std::pair<int, QString>& val) { return val.first == operId; })
        ->second;
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
            db.exec(s("INSERT INTO OrderTypes(Title, Description) VALUES (%1,%2);")
                        .arg(edit.ui->orderTitle->text())
                        .arg(edit.ui->orderDesc->toPlainText()));

            auto orderId = getFirstQueryVal<int>("SELECT last_value FROM ordertypes_id_seq", db);
            edit.insertAlgo(orderId);
        }
        db.commit();
    }
}

void OrderEdit::edit(QWidget* parent, QSqlDatabase& db, int orderId)
{
    if (db.isOpen()) {
        db.transaction();
        auto orderTitle = getFirstQueryVal<QString>(
            s("SELECT Title FROM OrderTypes WHERE Id = %1;").arg(orderId), db);
        if (!orderTitle.isEmpty()) {
            OrderEdit edit(parent, db, orderId);
            edit.setWindowIcon(QIcon(":/MainWindowRes/edit_order.png"));
            edit.setWindowTitle(s("Edit order %1").arg(orderTitle));
            if (edit.exec() == QDialog::Accepted) {
                db.exec(
                    s("UPDATE OrderTypes SET (Title, Description) = ('%1','%2') WHERE Id = %3;")
                        .arg(edit.ui->orderTitle->text())
                        .arg(edit.ui->orderDesc->toPlainText())
                        .arg(orderId));
                edit.insertAlgo(orderId);
            }
        }
        db.commit();
    }
}

void OrderEdit::insertAlgo(int orderId)
{
    auto lastAlgoId = getFirstQueryVal<int>("SELECT last_value FROM algorithm_id_seq", m_db);
    auto algoSize = m_algoList.size();

    QString insertAlgoStr
            = "INSERT INTO Algorithm(Id_orderType, Id_operationType) VALUES ";
    QString insertDependStr = "INSERT INTO AlgDependencies VALUES ";

    for (size_t i = 0; i != algoSize; ++i) {
        insertAlgoStr += s("(%1,%2)%3")
                .arg(orderId)
                .arg(m_algoList[i].id)
                .arg(i + 1 == algoSize ? ";" : ",");

        auto& parentInd = m_algoList[i].parentIndex;
        for (auto j = parentInd.begin(); j != parentInd.end(); ++j) {
            insertDependStr += s("(%1,%2)%3")
                    .arg(lastAlgoId + *j)
                    .arg(lastAlgoId + i)
                    .arg(std::next(j) == parentInd.end() ? "" : ",");
        }
    }
    m_db.exec(insertAlgoStr);
    m_db.exec(insertDependStr);
}

OrderEdit::~OrderEdit() { delete ui; }

void OrderEdit::initializePage(int id)
{
    switch (id) {
    case 0: {
        auto q = m_db.exec((m_id == -1)
                ? "SELECT Id, Title FROM OrderTypes;"
                : s("SELECT Id, Title FROM OrderTypes WHERE Id <> %1;").arg(m_id));
        while (q.next())
            m_ordNames.insert(q.value(1).toString());
        break;
    }
    case 1: {
        auto q = m_db.exec("SELECT Id, Title FROM OperationTypes;");
        auto operNamesModel = new QSqlQueryModel;
        operNamesModel->setQuery(q);
        ui->operNames->setModel(operNamesModel);
        ui->operNames->setColumnHidden(0, true);
        while (q.next())
            m_oprNames.push_back({q.value(0).toInt(), q.value(1).toString()});
        m_algoModel = new AlgoModel(this);
        ui->algoList->setModel(m_algoModel);
        break;
    }
    default:
        break;
    }
    if (m_id != -1)
        initializeEditPage(id);
}

void OrderEdit::initializeEditPage(int id)
{
    switch (id) {
    case 0: {
        auto q
            = m_db.exec(s("SELECT Title, Description FROM OrderTypes WHERE Id = %1;").arg(m_id));
        q.next();
        ui->orderTitle->setText(q.value(0).toString());
        ui->orderDesc->setPlainText(q.value(1).toString());
        break;
    }
    case 1: {
        auto dep = m_db.exec(
            s("WITH AlgoId AS (SELECT Id FROM Algorithm WHERE Id_orderType = %1) "
              "SELECT Id_parent, Id_dependent FROM AlgDependencies WHERE Id_parent IN AlgoId AND "
              "Id_dependent IN AlgoId;")
                .arg(m_id));
        auto alg = m_db.exec(
            s("SELECT Id, Id_operationType, Id_orderType FROM Algorithm WHERE Id_orderType = %1;")
                .arg(m_id));

        while (alg.next()) {
            auto operId = alg.value(1).toInt();
            m_algoList.push_back({operId, getOperTitle(operId), std::set<int>()});
        }
        while (dep.next())
            m_algoList[dep.value(1).toInt()].parentIndex.insert(dep.value(0).toInt());
        m_algoModel->insertRows(0, m_algoList.size());

        m_db.exec(
            s("WITH AlgoId AS (SELECT Id FROM Algorithm WHERE Id_orderType =%1)"
              "DELETE FROM AlgDependecies WHERE Id_parent IN AlgoId OR Id_dependent IN AlgoId;")
                .arg(m_id));
        m_db.exec(s("DELETE FROM Algorithm WHERE Id_orderType = %1;").arg(m_id));
        break;
    }
    default:
        break;
    }
}

void OrderEdit::on_orderTitle_editingFinished()
{
    auto text = ui->orderTitle->text();
    if (button(QWizard::NextButton)->isEnabled()) {
        if (text.isEmpty() || !checkUniqueOrderTitle(text))
            button(QWizard::NextButton)->setEnabled(false);
    } else if (!text.isEmpty() && checkUniqueOrderTitle(text))
        button(QWizard::NextButton)->setEnabled(true);
}

void OrderEdit::on_algoList_doubleClicked(const QModelIndex&) { on_act_editParents_triggered(); }

void OrderEdit::on_operNames_doubleClicked(const QModelIndex& index)
{
    auto oper = m_oprNames[index.row()];
    m_algoList.push_back({oper.first, oper.second, std::set<int>()});
    m_algoModel->insertRows(m_oprNames.size(), 1);
}

void OrderEdit::on_act_editParents_triggered()
{
    auto& algoItem = m_algoList[ui->algoList->currentIndex().row()];
    std::map<QString, int> titleToIndex;
    for (const auto& i : algoItem.parentIndex)
        titleToIndex.insert({m_algoList[i].title, i});
    algoItem.parentIndex = OrderDependencyEdit::edit(algoItem.parentIndex, titleToIndex, this);
}

void OrderEdit::on_act_deleteItem_triggered()
{
    auto current = ui->algoList->currentIndex().row();
    for (auto& i : m_algoList)
        i.parentIndex.erase(i.parentIndex.find(current));
    m_algoList.erase(m_algoList.begin() + current);
    m_algoModel->removeRows(current, 1);
}

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
            retval = QVariant::fromValue(m_data.m_algoList[index.row()].title);
            break;
        case 1:
            retval = QVariant::fromValue(parentStr(m_data.m_algoList[index.row()].parentIndex));
            break;
        default:
            break;
        }
    }
    return retval;
}

QString AlgoModel::parentStr(const std::set<int>& x)
{
    QString retval;
    for (auto i = x.begin(); i != x.end(); ++i)
        retval += *i + (next(i) != x.end() ? ", " : "");
    return retval;
}

AlgoModel::AlgoModel(OrderEdit* parent)
    : QAbstractTableModel(parent)
    , m_data(*parent)
{
}

bool AlgoModel::insertRows(int row, int count, const QModelIndex& parent)
{
    return QAbstractItemModel::insertRows(row, count, parent);
}

bool AlgoModel::removeRows(int row, int count, const QModelIndex& parent)
{
    return QAbstractItemModel::removeRows(row, count, parent);
}

void OrderEdit::on_algoList_customContextMenuRequested(const QPoint& pos)
{
    popupMenu(pos, ui->algoList->viewport(), {ui->act_editParents, ui->act_deleteItem}, this);
}


