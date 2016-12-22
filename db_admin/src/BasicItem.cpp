#include "BasicItem.h"

BasicItem::BasicItem(int id, const QString& data, bool isActive)
    : id(id)
    , data(data)
	, isActive(isActive)
{
}

const int& BasicItem::get_id() const
{
    return id;
}






