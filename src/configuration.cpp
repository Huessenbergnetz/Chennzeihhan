/*
    Chennzeihhan - Vehicle Registration Code Database for SailfishOS
    Copyright (C) 2014  Buschtrommel/Matthias Fehring

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "configuration.h"

Configuration::Configuration(QObject *parent) :
    QSettings(parent)
{
}

void Configuration::setFav(const QString &sign)
{
    QStringList favs = value(QStringLiteral("display/favourites")).toString().split(QChar(','));
    favs.append(sign);
    setValue(QStringLiteral("display/favourites"), favs.join(QChar(',')));

    emit favsChanged();
}



void Configuration::removeFav(const QString &sign)
{
    QStringList favs = value(QStringLiteral("display/favourites")).toString().split(QChar(','));

    if (favs.contains(sign)) {
        favs.removeOne(sign);
    }

    setValue(QStringLiteral("display/favourites"), favs.join(QChar(',')));

    emit favsChanged();

}



QStringList Configuration::getFavs()
{
    return value(QStringLiteral("display/favourites")).toString().split(QChar(','));
}



bool Configuration::isFav(const QString &sign)
{
    return value(QStringLiteral("display/favourites")).toString().split(QChar(',')).contains(sign);
}



void Configuration::set(const QString &key, const QString &val)
{
    setValue(key, val);

    emit configChanged();
}



QVariant Configuration::get(const QString &key, const QString &def)
{
    return value(key, def);
}
