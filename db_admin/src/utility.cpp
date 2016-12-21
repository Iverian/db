#include "utility.h"

#include <QDebug>
#include <QMenu>
#include <QSqlRecord>
#include <iostream>

using namespace std;

int getFirstIntQueryVal(const QString& text, const QSqlDatabase& db)
{
    auto q = db.exec(text);
    outQuery(q);
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

QString operator""_q(const char* const string, size_t) { return QString(string); }

QString operator""_q(const wchar_t* const string, size_t)
{
    return QString::fromWCharArray(string);
}

std::ostream& operator<<(std::ostream& os, const QString& str) { return os << str.toStdString(); }

void outputQuery(QSqlQuery query)
{
    cerr << "'%1':\n"_q.arg(query.lastQuery());
    if (query.isSelect()) {
        query.next();
        cerr << " [ \n";
        auto rec = query.record();
        do {
            auto count = rec.count();
            cerr << "{ ";
            for (auto i = 0; i != count; ++i)
                cerr << "%1%2 "_q.arg(rec.value(i).toString()).arg(i == count - 1 ? "" : ",");
            query.next();
            cerr << "}%1\n"_q.arg(query.isValid() ? "; " : "");
        } while (rec = query.record(), query.isValid());
        cerr << " ]\n";
    }
}

void outputQuery(const QString& text, const QSqlDatabase& db) { outputQuery(db.exec(text)); }
