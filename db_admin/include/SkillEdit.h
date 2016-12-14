#include <QDialog>
#include <QRadioButton>
#include <map>
#include <set>

namespace Ui {
class SkillEdit;
}

class SkillEdit : public QDialog {
    Q_OBJECT
public:
    static int add(const std::map<QString, int>& oper,
        const std::set<int>& oldSkills = std::set<int>(), QWidget* parent = nullptr);
    ~SkillEdit();

private slots:
    void on_group_buttonClicked(int id);

private:
    explicit SkillEdit(QWidget* parent = 0);
    QButtonGroup* setupList(const std::map<QString, int>& oper, const std::set<int>& skills);
    Ui::SkillEdit* ui;
};
