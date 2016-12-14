#include "SkillEdit.h"
#include "ui_SkillEdit.h"
#include "utility.h"

#include <QPushButton>

using namespace std;

SkillEdit::SkillEdit(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::SkillEdit)
{
    ui->setupUi(this);
}

SkillEdit::~SkillEdit() { delete ui; }

QButtonGroup* SkillEdit::setupList(const map<QString, int>& oper, const set<int>& skills)
{
    QButtonGroup* retval = new QButtonGroup(this);
    for (const auto& i : oper)
        if (!contains(skills, i.second)) {
            auto box = new QRadioButton(i.first, this);
            retval->addButton(box);
        }
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    connect(ui->buttonBox, SIGNAL(buttonClicked(int)), this, SLOT(on_group_buttonClicked(int)));
    return retval;
}

int SkillEdit::add(const std::map<QString, int>& oper, const set<int>& oldSkills, QWidget* parent)
{
    SkillEdit edit(parent);
    auto retval = -1;
    auto group = edit.setupList(oper, oldSkills);
    if (edit.exec() == QDialog::Accepted)
        retval = oper.at(group->checkedButton()->text());
    return retval;
}

void SkillEdit::on_group_buttonClicked(int) {
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}
