#include "OrderEdit.h"
#include "OrderDependencyEdit.h"
#include "ui_OrderEdit.h"
#include "utility.h"

#include <QSqlQueryModel>

// TODO::test the heck out of it

OrderEdit::OrderEdit(QWidget* parent, QSqlDatabase& db, int orderId)
    : QWizard(parent)
    , m_id(orderId)
    , m_db(db)
    , m_algoModel(nullptr)
    , m_ordNames()
    , m_oprNames()
    , ui(new Ui::OrderEdit)
{
    ui->setupUi(this);
}

bool OrderEdit::checkUniqueOrderTitle(const QString& text) { return !contains(m_ordNames, text); }

QString OrderEdit::getOperTitle(int operId)
{
    return std::find_if(m_oprNames.begin(), m_oprNames.end(), [&operId](
                                                                  const QPair<int, QString>& val) {
        return val.first == operId;
    })->second;
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
			auto q = "INSERT INTO OrderTypes(Title, Description) VALUES ('%1','%2');"_q
					 .arg(edit.ui->orderTitle->text())
					 .arg(edit.ui->orderDesc->toPlainText());
			qDebug() << q;
			db.exec(q);

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
            "SELECT Title FROM OrderTypes WHERE Id = %1;"_q.arg(orderId), db);
        if (!orderTitle.isEmpty()) {
            OrderEdit edit(parent, db, orderId);
            edit.setWindowIcon(QIcon(":/MainWindowRes/edit_order.png"));
            edit.setWindowTitle("Edit order %1"_q.arg(orderTitle));
            if (edit.exec() == QDialog::Accepted) {
                db.exec("UPDATE OrderTypes SET (Title, Description) = ('%1','%2') WHERE Id = %3;"_q
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
    auto algoSize = m_algoModel->rowCount();

    QString insertAlgoStr = "INSERT INTO Algorithm(Id_orderType, Id_operationType) VALUES ";
    QString insertDependStr = "INSERT INTO AlgDependencies VALUES ";

	for (auto i = 0; i != algoSize; ++i) {
        insertAlgoStr += "(%1,%2)%3"_q.arg(orderId)
                             .arg(m_algoModel->at(i).id)
                             .arg(i + 1 == algoSize ? ";" : ",");

        auto& parentInd = m_algoModel->at(i).parentIndex;
        for (auto j = parentInd.begin(); j != parentInd.end(); ++j) {
            insertDependStr += "(%1,%2)%3"_q.arg(lastAlgoId + *j)
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
        auto q
            = m_db.exec((m_id == -1) ? "SELECT Title FROM OrderTypes;"
                                     : "SELECT Title FROM OrderTypes WHERE Id <> %1;"_q.arg(m_id));
        while (q.next())
            m_ordNames.insert(q.value(0).toString());
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
        auto q = m_db.exec("SELECT Title, Description FROM OrderTypes WHERE Id = %1;"_q.arg(m_id));
        q.next();
        ui->orderTitle->setText(q.value(0).toString());
        ui->orderDesc->setPlainText(q.value(1).toString());
        break;
    }
    case 1: {
        auto dep
            = m_db.exec("WITH AlgoId AS (SELECT Id FROM Algorithm WHERE Id_orderType = %1) "
                        "SELECT Id_parent, Id_dependent FROM AlgDependencies WHERE Id_parent IN "
                        "AlgoId AND "
                        "Id_dependent IN AlgoId;"_q.arg(m_id));
        auto alg = m_db.exec(
            "SELECT Id, Id_operationType FROM Algorithm WHERE Id_orderType = %1;"_q.arg(m_id));

        QMap<int, int> idMapper;
        while (alg.next()) {
            auto operId = alg.value(1).toInt();
            m_algoModel->appendRow({operId, getOperTitle(operId), QSet<int>()});
            idMapper.insert(alg.value(0).toInt(), m_algoModel->rowCount() - 1);
        }
        while (dep.next())
            m_algoModel->at(idMapper.value(dep.value(1).toInt()))
                .parentIndex.insert(idMapper.value(dep.value(0).toInt()));

        m_db.exec(
            "WITH AlgoId AS (SELECT Id FROM Algorithm WHERE Id_orderType =%1)"
            "DELETE FROM AlgDependecies WHERE Id_parent IN AlgoId OR Id_dependent IN AlgoId;"_q
                .arg(m_id));
        m_db.exec("DELETE FROM Algorithm WHERE Id_orderType = %1;"_q.arg(m_id));
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
    auto oper = m_oprNames.value(index.row());
    m_algoModel->appendRow({oper.first, oper.second, QSet<int>()});
}

void OrderEdit::on_act_editParents_triggered()
{
    auto cur = ui->algoList->currentIndex().row();
    auto& algoItem = m_algoModel->at(cur);
    QMap<QString, int> titleToIndex;
    for (auto i = 0, size = m_algoModel->rowCount(); i != size; ++i) {
        if (i == cur || m_algoModel->at(i).parentIndex.contains(i))
            continue;
        titleToIndex.insert(m_algoModel->at(i).title, i);
    }
    algoItem.parentIndex = OrderDependencyEdit::edit(algoItem.parentIndex, titleToIndex, this);
    m_algoModel->updateRow(cur);
}

void OrderEdit::on_act_deleteItem_triggered()
{
    m_algoModel->eraseRow(ui->algoList->currentIndex().row());
}

void OrderEdit::on_algoList_customContextMenuRequested(const QPoint& pos)
{
    popupMenu(pos, ui->algoList->viewport(), {ui->act_editParents, ui->act_deleteItem}, this);
}
