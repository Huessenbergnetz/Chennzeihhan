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

#include "countriesbasemodel.h"
#include <QSqlQuery>
#include <QCoreApplication>

CountriesBaseModel::CountriesBaseModel(QObject *parent) : QAbstractListModel(parent)
{

}

CountriesBaseModel::~CountriesBaseModel()
{
    qDeleteAll(m_countries);
    m_countries.clear();
}



int CountriesBaseModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_countries.count();
}


QHash<int, QByteArray> CountriesBaseModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(Id, QByteArrayLiteral("id"));
    roles.insert(Code, QByteArrayLiteral("code"));
    roles.insert(Sign, QByteArrayLiteral("sign"));
    roles.insert(Type, QByteArrayLiteral("type"));
    roles.insert(Official, QByteArrayLiteral("official"));
    roles.insert(Colors, QByteArrayLiteral("colors"));
    roles.insert(Name, QByteArrayLiteral("name"));

    return roles;
}



QModelIndex CountriesBaseModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    return createIndex(row, column);
}



QVariant CountriesBaseModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() > (rowCount()-1)) {
        return QVariant();
    }

    Country *c = m_countries.at(index.row());

    switch(role) {
    case Id:
        return QVariant::fromValue(c->id);
    case Code:
        return QVariant::fromValue(c->code);
    case Sign:
        return QVariant::fromValue(c->sign);
    case Type:
        return QVariant::fromValue(c->type);
    case Official:
        return QVariant::fromValue(c->official);
    case Colors:
        return QVariant::fromValue(c->colors);
    case Name:
        return QVariant::fromValue(c->name);
    default:
        return QVariant();
    }
}



void CountriesBaseModel::clear()
{
    if (!m_countries.isEmpty()) {

        beginRemoveRows(QModelIndex(), 0, rowCount()-1);

        qDeleteAll(m_countries);
        m_countries.clear();

        endRemoveRows();

    }
}



void CountriesBaseModel::populate(QSqlQuery *q)
{
    clear();

    QList<Country*> _l;

    while (q->next()) {

        _l.append(new Country(q->value(0).toUInt(),
                              q->value(1).toString(),
                              q->value(2).toString(),
                              q->value(3).toUInt(),
                              q->value(4).toBool(),
                              q->value(5).toString().split(QChar(',')),
                              QCoreApplication::translate("DBStrings", q->value(6).toString().toUtf8().constData())
                              ));

        if (!_l.isEmpty()) {

            beginInsertRows(QModelIndex(), 0, _l.count() - 1);

            m_countries = _l;

            endInsertRows();
        }

    }
}




QString CountriesBaseModel::getBaseQueryString() const
{
    return QStringLiteral("SELECT id, code, sign, type, official, colors, en FROM countries");
}



int CountriesBaseModel::findBySign(const QString &s) const
{
    if (m_countries.isEmpty()) {
        return -1;
    }

    int idx = -1;

    for (int i = 0; i < m_countries.count(); ++i) {
        if (m_countries.at(i)->sign == s) {
            idx = i;
            break;
        }
    }

    return idx;
}



bool CountriesBaseModel::removeBySign(const QString &s)
{
    const int idx = findBySign(s);

    if (idx > -1) {

        beginRemoveRows(QModelIndex(), idx, idx);

        delete m_countries.takeAt(idx);

        endRemoveRows();

        return true;
    } else {
        return false;
    }
}



void CountriesBaseModel::addCountry(Country *c)
{
    if (!c) {
        return;
    }

    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    m_countries.append(c);

    endInsertRows();
}
