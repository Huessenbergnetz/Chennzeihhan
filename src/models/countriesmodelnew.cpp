#include "countriesmodelnew.h"
#include <QSqlQuery>

CountriesModelNew::CountriesModelNew(QObject *parent) : CountriesBaseModel(parent)
{
    init();
}




void CountriesModelNew::init()
{
    QSqlQuery q;
    if (q.exec(getBaseQueryString())) {
        populate(&q);
    }
}
