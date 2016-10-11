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

#ifndef SIMPLEITEMMODEL_H
#define SIMPLEITEMMODEL_H

#include <QAbstractListModel>
#include "simpleitem.h"

class SimpleItemModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SimpleItemModel(QObject *parent = nullptr);

    ~SimpleItemModel();

    enum Roles {
        Id = Qt::UserRole + 1,
        Name,
        Type,
        Sign,
        State,
        Closed
    };

    /*!
     * \brief Reimplemented from QAbstractItemModel.
     */
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
    /*!
     * \brief Reimplemented from QAbstractItemModel.
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    /*!
     * \brief Reimplemented from QAbstractListModel.
     */
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    /*!
     * \brief Reimplemented from QAbstractItemModel.
     */
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;


    void addItem(SimpleItem *i);

    void addItem(uint id, const QString &name, const QString &type, const QString &sign);

    void addItems(const QList<SimpleItem*> &items);

    void clear();

private:
    Q_DISABLE_COPY(SimpleItemModel)
    QList<SimpleItem*> m_items;
};

#endif // SIMPLEITEMMODEL_H
