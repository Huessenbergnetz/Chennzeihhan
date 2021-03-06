/*
    Chennzeihhan - Vehicle Registration Code Database for SailfishOS
    Copyright (C) 2014-2019 Hüssenbergnetz/Matthias Fehring

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

#ifndef COUNTRIESMODELFILTER_H
#define COUNTRIESMODELFILTER_H

#include <QObject>
#include <QSortFilterProxyModel>
#include "../globals.h"

class CountriesModelFilter : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(Chennzeihhan::Target searchTarget READ searchTarget WRITE setSearchTarget NOTIFY searchTargetChanged)
    Q_PROPERTY(Chennzeihhan::Target sortTarget READ sortTarget WRITE setSortTarget NOTIFY sortTargetChanged)
    Q_PROPERTY(QString search READ search WRITE setSearch NOTIFY searchChanged)
    Q_PROPERTY(QString firstChar READ firstChar WRITE setFirstChar NOTIFY firstCharChanged)
    Q_ENUMS(Chennzeihhan::Target)
public:
    explicit CountriesModelFilter(QObject *parent = nullptr);


    Chennzeihhan::Target searchTarget() const;
    Chennzeihhan::Target sortTarget() const;
    QString search() const;
    QString firstChar() const;

    void setSearchTarget(Chennzeihhan::Target nSearchTarget);
    void setSortTarget(Chennzeihhan::Target nSortTarget);
    void setSearch(const QString &nSearch);
    void setFirstChar(const QString &nFirstChar);

signals:
    void searchTargetChanged(Chennzeihhan::Target searchTarget);
    void sortTargetChanged(Chennzeihhan::Target sortTarget);
    void searchChanged(const QString &search);
    void firstCharChanged(const QString &firstChar);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

private:
    Q_DISABLE_COPY(CountriesModelFilter)
    Chennzeihhan::Target m_searchTarget;
    Chennzeihhan::Target m_sortTarget;
    QString m_search;
    QString m_firstChar;
};

#endif // COUNTRIESMODELFILTER_H
