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

#ifndef EXTENDEDITEM_H
#define EXTENDEDITEM_H

#include <QObject>
#include "item.h"

class SimpleItemModel;

/*!
 * \brief The ExtendedItem class.
 */
class ExtendedItem : public Item
{
    Q_OBJECT
    Q_PROPERTY(SimpleItemModel *antecessors READ antecessors CONSTANT)
    Q_PROPERTY(QString successor READ successor NOTIFY successorChanged)
    Q_PROPERTY(uint successorId READ successorId NOTIFY successorIdChanged)
    Q_PROPERTY(QString tpo READ tpo NOTIFY tpoChanged)
    Q_PROPERTY(uint tpoId READ tpoId NOTIFY tpoIdChanged)
    Q_PROPERTY(QString optionalSigns READ optionalSigns NOTIFY optionalSignsChanged)
public:
    explicit ExtendedItem(QObject *parent = nullptr);
    ~ExtendedItem();

    SimpleItemModel *antecessors() const;
    QString successor() const;
    uint successorId() const;
    QString tpo() const;
    uint tpoId() const;
    QString optionalSigns() const;

signals:
    void antecessorsChanged(SimpleItemModel *antecessors);
    void successorChanged(const QString &successor);
    void successorIdChanged(uint successorId);
    void tpoChanged(const QString &tpo);
    void tpoIdChanged(uint tpoId);
    void optionalSignsChanged(const QString &optionalSigns);

protected:
    void setSuccessor(const QString &nSuccessor);
    void setSuccessorId(uint nSuccessorId);
    void setTpo(const QString &nTpo);
    void setTpoId(uint nTpoId);
    void setOptionalSigns(const QString &nOptionalSigns);

    void clear();
    void query();

private:
    Q_DISABLE_COPY(ExtendedItem)
    SimpleItemModel *m_antecessors;
    QString m_successor;
    uint m_successorId;
    QString m_tpo;
    uint m_tpoId;
    QString m_optionalSigns;
};

#endif // EXTENDEDITEM_H
