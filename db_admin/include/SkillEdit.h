#ifndef SKILLEDIT_H
#define SKILLEDIT_H

#include <QDialog>

namespace Ui {
class SkillEdit;
}

class SkillEdit : public QDialog
{
	Q_OBJECT

public:
	explicit SkillEdit(QWidget *parent = 0);
	~SkillEdit();

private:
	Ui::SkillEdit *ui;
};

#endif // SKILLEDIT_H
