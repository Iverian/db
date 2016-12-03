#include "utility.h"

#include <QSqlQuery>
#include <QVariant>

int getFirstIntQueryVal(const QString& text, const QSqlDatabase& db)
{
    auto q = db.exec(text);
    q.next();
    return q.value(0).toInt();
}
