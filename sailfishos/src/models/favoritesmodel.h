/*
    Chennzeihhan - Vehicle Registration Code Database for SailfishOS
    Copyright (C) 2014-2016  Buschtrommel/Matthias Fehring

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

#ifndef FAVORITESMODEL_H
#define FAVORITESMODEL_H

#include <QObject>
#include "countriesbasemodel.h"

class Configuration;

class FavoritesModel : public CountriesBaseModel
{
    Q_OBJECT
public:
    explicit FavoritesModel(Configuration *conf, QObject *parent = nullptr);

    void init();

    Q_INVOKABLE void remove(const QString &sign);
    Q_INVOKABLE void add(const QString &sign);
    Q_INVOKABLE bool isFav(const QString &sign);

signals:
    void modelChanged();

private:
    Q_DISABLE_COPY(FavoritesModel)
    Configuration *m_conf;
    QStringList m_favs;
};

#endif // FAVORITESMODEL_H
