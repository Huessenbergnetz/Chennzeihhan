#include "deitem.h"
#include "simpleitem.h"
#include "simpleitemmodel.h"
#ifdef QT_DEBUG
#include <QtDebug>
#endif

DeItem::DeItem(QObject *parent) : ExtendedItem(parent)
{
    setCountryCode(QStringLiteral("de"));
    setCountryName(tr("Germany"));
}

DeItem::~DeItem()
{

}



void DeItem::clear()
{
    ExtendedItem::clear();
}



void DeItem::query()
{
    setInOperation(true);

    clear();

    ExtendedItem::query();

    setInOperation(false);
}
