#pragma once

#include <QSet>
#include <QString>
#include <QtCore/QVector>

struct BasicItem {
    explicit BasicItem(int id, const QString& data, bool isActive);
    virtual ~BaseItem()
    {
    }
    const int& get_id() const;
    int id;
    QString data;
    bool isActive;
};



