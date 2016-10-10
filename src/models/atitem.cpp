#include "atitem.h"

AtItem::AtItem(QObject *parent) : ExtendedItem(parent)
{
    setCountryCode(QStringLiteral("at"));
    setCountryName(tr("Austria"));
}



AtItem::~AtItem()
{

}



void AtItem::clear()
{
    ExtendedItem::clear();
}



void AtItem::query()
{
    setInOperation(true);

    clear();

    ExtendedItem::query();

    setInOperation(false);
}
