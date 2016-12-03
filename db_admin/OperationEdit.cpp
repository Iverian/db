#include "OperationEdit.h"
#include "ui_OperationEdit.h"
#include "utility.h"

#include <QPushButton>
#include <QSqlQuery>

OperationEdit::OperationEdit(QWidget* parent, QSqlDatabase& db, int operationId)
    : QDialog(parent)
    , m_db(db)
    , m_id(operationId)
    , m_ui(new Ui::OperationEdit)
{
    m_ui->setupUi(this);
}

bool OperationEdit::checkUniqueTitle(const QString& text)
{
    int sameTitle;
    if (m_id == -1)
        sameTitle = getFirstIntQueryVal(
            "SELECT COUNT (*) FROM OperationTypes WHERE Title = '" + text + "';", m_db);
    else
        sameTitle = getFirstIntQueryVal("SELECT COUNT (*) FROM OperationTypes WHERE Id <> "
            + QString::number(m_id) + " AND Title = '" + text + "';");
    return sameTitle == 0;
}

void OperationEdit::add(QWidget* parent, QSqlDatabase& db)
{
    if (db.isOpen()) {
        db.transaction();
        OperationEdit edit(parent, db, -1);

        edit.m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        edit.setWindowTitle("Add new operation");
        edit.setWindowIcon(QIcon(":/MainWindowRes/new_oper.png"));

        if (edit.exec() == QDialog::Accepted) {
            auto title = edit.m_ui->lineEdit->text();
            auto desc = edit.m_ui->plainTextEdit->toPlainText();
            db.exec(
                "INSERT INTO OperationTypes (Title, Description) VALUES ('" + title + "', '" + desc + "');");
        }
        db.commit();
    }
}

void OperationEdit::edit(QWidget* parent, QSqlDatabase& db, int operId)
{
    if (db.isOpen()) {
        db.transaction();
        auto strId = QString::number(operId);
        auto correctId
            = getFirstIntQueryVal("SELECT COUNT (*) FROM OperationTypes WHERE Id = " + strId + ";", db);
        if (correctId == 1) {
            OperationEdit edit(parent, db, operId);
            auto q = db.exec("SELECT Title, Description FROM OperationTypes WHERE Id = " + strId + ";");
            q.next();
            auto title = q.value(0).toString();

            edit.setWindowTitle("Edit operation " + title);
            edit.setWindowIcon(QIcon(":/MainWindowRes/edit_oper.png"));

            edit.m_ui->lineEdit->setText(title);
            edit.m_ui->plainTextEdit->setPlainText(q.value(1).toString());
            if (edit.exec() == QDialog::Accepted) {
                auto title = edit.m_ui->lineEdit->text();
                auto desc = edit.m_ui->plainTextEdit->toPlainText();
                db.exec("UPDATE OperationTypes SET (Title, Description) = ('" + title + "', '" + desc
                    + "') WHERE Id = " + strId + ";");
            }
        }
        db.commit();
    }
}

OperationEdit::~OperationEdit() { delete m_ui; }

void OperationEdit::on_lineEdit_editingFinished()
{
    auto text = m_ui->lineEdit->text();
    if (m_ui->buttonBox->button(QDialogButtonBox::Ok)->isEnabled()) {
        if (text.isEmpty() || !checkUniqueTitle(text))
            m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    } else if (!text.isEmpty() && checkUniqueTitle(text))
        m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}
