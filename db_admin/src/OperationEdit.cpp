#include "OperationEdit.h"
#include "ui_OperationEdit.h"
#include "utility.h"

#include <QPushButton>

OperationEdit::OperationEdit(QWidget* parent, QSqlDatabase& db, int operationId)
	: QDialog(parent)
	, m_db(db)
	, m_id(operationId)
	, m_names()
	, ui(new Ui::OperationEdit)
{
	ui->setupUi(this);
	auto q = db.exec((operationId == -1)
			? "SELECT Title FROM OperationTypes;"
			: "SELECT Title FROM OperationTypes WHERE Id <> %1;"_q.arg(operationId));
	while (q.next())
		m_names.push_back(q.value(0).toString());
}

bool OperationEdit::checkUniqueTitle(const QString& text)
{
	return !m_names.contains(text);
}

void OperationEdit::add(QWidget* parent, QSqlDatabase& db)
{
	if (db.isOpen()) {
		db.transaction();
		OperationEdit edit(parent, db, -1);

		edit.ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
		edit.setWindowTitle("Add new operation");
		edit.setWindowIcon(QIcon(":/MainWindowRes/new_oper.png"));

		if (edit.exec() == QDialog::Accepted) {
			auto title = edit.ui->lineEdit->text();
			auto desc = edit.ui->plainTextEdit->toPlainText();
			db.exec(
				"INSERT INTO OperationTypes (Title, Description) VALUES ('%1','%2');"_q
					.arg(title)
					.arg(desc));
		}
		db.commit();
	}
}

void OperationEdit::edit(QWidget* parent, QSqlDatabase& db, int operId)
{
	if (db.isOpen()) {
		db.transaction();
		auto strId = QString::number(operId);
		auto correctId = getFirstQueryVal<int>(
			"SELECT COUNT (*) FROM OperationTypes WHERE Id = %1;"_q.arg(operId), db);
		if (correctId == 1) {
			OperationEdit edit(parent, db, operId);
			auto q = db.exec(
				"SELECT Title, Description FROM OperationTypes WHERE Id = %1;"_q
					.arg(operId));
			outQuery_(q.lastQuery(), db);
			q.next();
			auto title = q.value(0).toString();

			edit.setWindowTitle("Edit operation %1"_q.arg(title));
			edit.setWindowIcon(QIcon(":/MainWindowRes/edit_oper.png"));

			edit.ui->lineEdit->setText(title);
			edit.ui->plainTextEdit->setPlainText(q.value(1).toString());
			if (edit.exec() == QDialog::Accepted) {
				title = edit.ui->lineEdit->text();
				auto desc = edit.ui->plainTextEdit->toPlainText();
				db.exec("UPDATE OperationTypes SET (Title, Description) = ('%1','%2') "
						  "WHERE Id = %3;"_q
							.arg(title)
							.arg(desc)
							.arg(operId));
			}
		}
		db.commit();
	}
}

void OperationEdit::on_lineEdit_editingFinished()
{
	auto text = ui->lineEdit->text();
	if (ui->buttonBox->button(QDialogButtonBox::Ok)->isEnabled()) {
		if (text.isEmpty() || !checkUniqueTitle(text))
			ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
	} else if (!text.isEmpty() && checkUniqueTitle(text))
		ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

OperationEdit::~OperationEdit()
{
	delete ui;
}
