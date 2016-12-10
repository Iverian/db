#pragma once

#include <QAction>
#include <QPoint>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QWidget>

int getFirstIntQueryVal(
	const QString& text, const QSqlDatabase& db = QSqlDatabase::database());
void popupMenu(const QPoint& pos, QWidget* viewport,
	const std::initializer_list<QAction*>& actList, QWidget* parent);

template <class T, class U> bool contains(const T& container, const U& value)
{
	return container.find(value) != container.end();
}

template <class T>
T getFirstQueryVal(const QString& text,
	const QSqlDatabase& db = QSqlDatabase::database(), bool* const status = nullptr)
{
	auto q = db.exec(text);
	auto stat = q.isSelect() && q.next() && q.value(0).isValid();
	auto retval = stat ? q.value(0).value<T>() : T();
	if (status)
		*status = stat;
	return retval;
}

QString s(const char* const string);
