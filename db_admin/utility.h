#pragma once

#include <QString>
#include <QSqlDatabase>

int getFirstIntQueryVal(const QString& text, const QSqlDatabase& db = QSqlDatabase::database());
