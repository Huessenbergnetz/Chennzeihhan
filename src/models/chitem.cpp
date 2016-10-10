#include "chitem.h"

ChItem::ChItem(QObject *parent) : Item(parent)
{
    setCountryCode(QStringLiteral("ch"));
    setCountryName(tr("Switzerland"));
}



ChItem::~ChItem()
{

}



void ChItem::clear()
{
    Item::clear();
}


void ChItem::query()
{
    setInOperation(true);

    clear();

    Item::query();

    setInOperation(false);
}
