#pragma once

#include <QSqlDatabase>
#include <QString>
#include <QPoint>
#include <QWidget>
#include <QAction>

int getFirstIntQueryVal(const QString& text, const QSqlDatabase& db = QSqlDatabase::database());
void popupMenu(
    const QPoint& pos, QWidget* viewport, const std::initializer_list<QAction*>& actList, QWidget* parent);
