#pragma once

#include <QAction>
#include <QDebug>
#include <QPoint>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QWidget>
#include <iostream>

#ifndef NDEBUG
#define outQuery(q)                                                                               \
    do {                                                                                          \
        std::cerr << std::string(__FUNCTION__) << ": " << std::to_string(__LINE__) << std::endl;  \
        outputQuery(q);                                                                           \
    } while (0)
#define outQuery_(t, d)                                                                           \
    do {                                                                                          \
        std::cerr << std::string(__FUNCTION__) << ": " << std::to_string(__LINE__) << std::endl;  \
        outputQuery(t, d);                                                                        \
    } while (0)
#else
#define outQuery(q)
#define outQuery_(t, d)
#endif

#define echo _echo()

struct _echo {
};

template<class T>
T operator<<(_echo, T&& obj)
{
	qDebug() << obj;
	return obj;
}

template<class T>
const T& operator<<(_echo, const T& obj)
{
	qDebug() << obj;
	return obj;
}

int getFirstIntQueryVal(const QString& text, const QSqlDatabase& db = QSqlDatabase::database());
void popupMenu(const QPoint& pos, QWidget* viewport,
		const std::initializer_list<QAction*>& actList, QWidget* parent);

template<class T, class U>
bool contains(const T& container, const U& value)
{
	return container.find(value) != container.end();
}

void outputQuery(const QString& text, const QSqlDatabase& db);
void outputQuery(QSqlQuery query);

template<class T>
T getFirstQueryVal(const QString& text, const QSqlDatabase& db = QSqlDatabase::database(),
		bool* const status = nullptr)
{
	auto q = db.exec(text);
	outQuery_(text, db);
	auto stat = q.isSelect() && q.next() && q.value(0).isValid();
	auto retval = stat ? q.value(0).value<T>() : T();
	if (status)
		*status = stat;
	q.finish();
	return retval;
}

QString operator ""_q(const char* const string, size_t);
QString operator ""_q(const wchar_t* const string, size_t);

bool isSet(int x, int flag);
