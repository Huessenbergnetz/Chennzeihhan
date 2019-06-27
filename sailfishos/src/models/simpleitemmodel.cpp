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

#include "simpleitemmodel.h"

SimpleItemModel::SimpleItemModel(QObject *parent) : QAbstractListModel(parent)
{

}


SimpleItemModel::~SimpleItemModel()
{
    qDeleteAll(m_items);
    m_items.clear();
}



void SimpleItemModel::clear()
{
    if (!m_items.isEmpty()) {
        beginRemoveRows(QModelIndex(), 0, m_items.count() - 1);

        qDeleteAll(m_items);
        m_items.clear();

        endRemoveRows();
    }
}


int SimpleItemModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_items.count();
}



QHash<int, QByteArray> SimpleItemModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(Id, QByteArrayLiteral("id"));
    roles.insert(Name, QByteArrayLiteral("name"));
    roles.insert(Type, QByteArrayLiteral("type"));
    roles.insert(Sign, QByteArrayLiteral("sign"));
    roles.insert(State, QByteArrayLiteral("state"));
    roles.insert(Closed, QByteArrayLiteral("closed"));
    return roles;
}



QModelIndex SimpleItemModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    return createIndex(row, column);
}


QVariant SimpleItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() > (rowCount() - 1)) {
        return QVariant();
    }

    SimpleItem *si = m_items.at(index.row());

    switch(role) {
    case Id:
        return QVariant::fromValue(si->id);
    case Name:
        return QVariant::fromValue(si->name);
    case Type:
        return QVariant::fromValue(si->type);
    case Sign:
        return QVariant::fromValue(si->sign);
    case State:
        return QVariant::fromValue(si->state);
    case Closed:
        return QVariant::fromValue(si->closed);
    default:
        return QVariant();
    }
}



void SimpleItemModel::addItem(SimpleItem *i)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    m_items.append(i);

    endInsertRows();
}



void SimpleItemModel::addItem(uint id, const QString &name, const QString &type, const QString &sign)
{
    addItem(new SimpleItem(id, name, type, sign));
}



void SimpleItemModel::addItems(const QList<SimpleItem *> &items)
{
    if (!items.isEmpty()) {
        beginInsertRows(QModelIndex(), rowCount(), rowCount() + items.count() -1);

        m_items.append(items);

        endInsertRows();
    }
}
