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

#include "countrymodel.h"

const char* CountryModel::COLUMN_NAMES[] = {
    "itemId",
    "sign",
    "name",
    "type",
    "state",
    NULL
};


CountryModel::CountryModel(QObject *parent) :
    QSqlQueryModel(parent)
{
}


QHash<int,QByteArray> CountryModel::roleNames() const
{
    int idx = 0;
    QHash<int, QByteArray> roles;
    while (COLUMN_NAMES[idx]) {
        roles[Qt::UserRole + idx + 1] = COLUMN_NAMES[idx];
        idx++;
    }
    return roles;
}



QVariant CountryModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);

    if(role < Qt::UserRole)
    {
        value = QSqlQueryModel::data(index, role);
    } else {
        int columnIdx = role - Qt::UserRole - 1;
        QModelIndex modelIndex = this->index(index.row(), columnIdx);
        value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
        if (columnIdx == 3) {

            if (countryCode == "de") {
                value = deHelper->getType(value.toInt());
            } else if (countryCode == "at") {
                value = atHelper->getType(value.toInt());
            }

        } else if (columnIdx == 4) {

            if (countryCode == "de") {
                value = deHelper->getState(value.toInt());
            } else if (countryCode == "at") {
                value = atHelper->getState(value.toInt());
            }

        }
    }

    return value;

}


void CountryModel::refresh(const QString &cc, int sort, int searchTarget, const QString &search)
{
    countryCode = cc;

    QString queryString;

    if (cc == "ch") {
        queryString = QString("SELECT id AS itemId, sign, name, '%1' AS type, '' AS state FROM ch").arg(tr("Canton"));
    } else {
        queryString = QString("SELECT id AS itemId, sign, name, type, state FROM %1").arg(cc);
    }

    if (!search.isEmpty())
    {
        QString t_search = search;
//        t_search.prepend("%");
        t_search.append("%");

        switch(searchTarget)
        {
        case 1:
            queryString.append(QString(" WHERE name LIKE \"%1\"").arg(t_search));
            break;
        case 2:
            queryString.append(QString(" WHERE (name LIKE \"%1\") OR (sign LIKE \"%2\")").arg(t_search).arg(t_search.toUpper()));
            break;
        default:
            queryString.append(QString(" WHERE sign LIKE \"%1\"").arg(t_search.toUpper()));
            break;
        }
    }

    switch(sort)
    {
    case 1:
        queryString.append(" ORDER BY name ASC");
        break;
    default:
        queryString.append(" ORDER BY sign ASC");
        break;
    }


    this->setQuery(queryString);

}
