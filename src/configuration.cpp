#include "configuration.h"

Configuration::Configuration(QObject *parent) :
    QSettings(parent)
{
}

void Configuration::setFav(const QString &sign)
{
    QStringList favs = value("display/favourites", "").toString().split(",");
    favs.append(sign);
    setValue("display/favourites", favs.join(","));

    emit favsChanged();
}



void Configuration::removeFav(const QString &sign)
{
    QStringList favs = value("display/favourites", "").toString().split(",");

    if (favs.contains(sign))
        favs.removeOne(sign);

    setValue("display/favourites", favs.join(","));

    emit favsChanged();
}



QStringList Configuration::getFavs()
{
    return value("display/favourites", "").toString().split(",");
}



bool Configuration::isFav(const QString &sign)
{
    return value("display/favourites", "").toString().split(",").contains(sign);
}
