#include "utility.h"

#include <QSqlQuery>
#include <QVariant>
#include <QMenu>

using namespace std;

int getFirstIntQueryVal(const QString& text, const QSqlDatabase& db)
{
    auto q = db.exec(text);
    q.next();
    return q.value(0).toInt();
}

void popupMenu(const QPoint& pos, QWidget* viewport, const initializer_list<QAction*>& actList,
    QWidget* parent = Q_NULLPTR)
{
    auto menu = new QMenu(parent);
    for (auto& i : actList)
        menu->addAction(i);
    menu->popup(viewport->mapToGlobal(pos));
}
