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

#include "itemmodel.h"
#include "dehelper.h"
#include "athelper.h"
#include <QSqlQuery>
#include <QStringList>

ItemModel::ItemModel(QObject *parent) :
    QObject(parent)
{
}


QVariantMap ItemModel::getItemData(const QString &cc, int id)
{
    if (cc == QLatin1String("de")) {
        return getDeData(id);
    } else if (cc == QLatin1String("ch")) {
        return getChData(id);
    } else if (cc == QLatin1String("at")) {
        return getAtData(id);
    } else {
        return QVariantMap();
    }
}


QVariantMap ItemModel::getAtData(int id)
{
    QVariantMap itemresult;
    QSqlQuery query;
    AtHelper atHelper;
    query.exec(QStringLiteral("SELECT id, sign, name, capital, type, state, assigned, successor, admin, closed, optional, wikipedia, coa FROM at WHERE id = %1").arg(id));

    if (query.next())
    {
        itemresult[QStringLiteral("itemId")] = query.value(0).toInt();
        itemresult[QStringLiteral("sign")] = query.value(1).toString();
        itemresult[QStringLiteral("name")] = query.value(2).toString();
        itemresult[QStringLiteral("capital")] = query.value(3).toString();
        itemresult[QStringLiteral("type")] = atHelper.getType(query.value(4).toInt());
        itemresult[QStringLiteral("state")] = atHelper.getState(query.value(5).toInt());
        itemresult[QStringLiteral("founded")] = query.value(6).toInt();
        itemresult[QStringLiteral("disbanded")] = query.value(9).toInt();
        itemresult[QStringLiteral("optional")] = query.value(10).toInt();
        itemresult[QStringLiteral("wikipedia")] = query.value(11).toString();
        itemresult[QStringLiteral("succId")] = query.value(7).toInt(); // id of the district it was merged in
        itemresult[QStringLiteral("succName")] = QStringLiteral("");
        itemresult[QStringLiteral("succType")] = QStringLiteral("");
        itemresult[QStringLiteral("succSign")] = QStringLiteral("");
        itemresult[QStringLiteral("tpoId")] = query.value(8).toInt(); // id of the the current district it is part of
        itemresult[QStringLiteral("tpoName")] = QStringLiteral("");
        itemresult[QStringLiteral("tpoType")] = QStringLiteral("");
        itemresult[QStringLiteral("tpoSign")] = QStringLiteral("");
        itemresult[QStringLiteral("optionalSigns")] = QStringLiteral("");
        itemresult[QStringLiteral("coa")] = query.value(12).toString();
    }

    if (itemresult[QStringLiteral("succId")].toInt() != 0)
    {
        query.exec(QStringLiteral("SELECT name, type, sign FROM at WHERE id = %1").arg(itemresult[QStringLiteral("succId")].toInt()));
        if (query.next())
        {
            itemresult[QStringLiteral("succName")] = query.value(0).toString();
            itemresult[QStringLiteral("succType")] = atHelper.getType(query.value(1).toInt());
            itemresult[QStringLiteral("succSign")] = query.value(2).toString();
        }
    }


    // check if district today belongs to another district than it was first merged into
    if (itemresult[QStringLiteral("succId")] != itemresult[QStringLiteral("tpoId")] && itemresult[QStringLiteral("tpoId")].toInt() != 0)
    {
        query.exec(QStringLiteral("SELECT name, type, sign FROM at WHERE id = %1").arg(itemresult[QStringLiteral("tpoId")].toInt()));
        if (query.next())
        {
            itemresult[QStringLiteral("tpoName")] = query.value(0).toString();
            itemresult[QStringLiteral("tpoType")] = atHelper.getType(query.value(1).toInt());
            itemresult[QStringLiteral("tpoSign")] = query.value(2).toString();
        }
    } else {
        itemresult[QStringLiteral("tpoId")] = 0;
    }

    if (itemresult[QStringLiteral("disbanded")].toInt() == 0)
    {

        QStringList optSigns;
        QList<int> subOptSignIds;
        QList<int> subSubOptSignIds;
        query.exec(QStringLiteral("SELECT id, sign FROM at WHERE successor = %1 AND optional > 0").arg(itemresult[QStringLiteral("itemId")].toInt()));
        while (query.next()) {
            subOptSignIds << query.value(0).toInt();
            optSigns << query.value(1).toString();
        }

        for (int i = 0; i < subOptSignIds.size(); ++i)
        {
            query.exec(QStringLiteral("SELECT id, sign FROM at WHERE successor = %1 AND optional > 0").arg(subOptSignIds.at(i)));
            while (query.next()) {
                subSubOptSignIds << query.value(0).toInt();
                optSigns << query.value(1).toString();
            }
        }

        for (int i = 0; i < subSubOptSignIds.size(); ++i)
        {
            query.exec(QStringLiteral("SELECT sign FROM at WHERE successor = %1 AND optional > 0").arg(subSubOptSignIds.at(i)));
            while (query.next()) {
                optSigns << query.value(0).toString();
            }
        }

        if (!optSigns.isEmpty())
            itemresult[QStringLiteral("optionalSigns")] = optSigns.join(QStringLiteral(", "));

    }

    return itemresult;
}


QVariantMap ItemModel::getChData(int id)
{
    QVariantMap itemresult;
    QSqlQuery query;
    query.exec(QStringLiteral("SELECT id, sign, name, capital, wikipedia, coa FROM ch WHERE id = %1").arg(id));

    if (query.next())
    {
        itemresult[QStringLiteral("itemId")] = query.value(0).toInt();
        itemresult[QStringLiteral("sign")] = query.value(1).toString();
        itemresult[QStringLiteral("name")] = query.value(2).toString();
        itemresult[QStringLiteral("capital")] = query.value(3).toString();
        itemresult[QStringLiteral("wikipedia")] = query.value(4).toString();
        itemresult[QStringLiteral("coa")] = query.value(5).toString();
    }

    return itemresult;
}


QVariantMap ItemModel::getDeData(int id)
{
    DeHelper deHelper;
    QVariantMap itemresult;
    QSqlQuery query;
    query.exec(QStringLiteral("SELECT id, sign, name, capitol, type, state, assign, successor, admin, closed, optional, wikipedia, coa FROM de WHERE id = %1").arg(id));

    if (query.next())
    {
        itemresult[QStringLiteral("itemId")] = query.value(0).toInt();
        itemresult[QStringLiteral("sign")] = query.value(1).toString();
        itemresult[QStringLiteral("name")] = query.value(2).toString();
        itemresult[QStringLiteral("capital")] = query.value(3).toString();
        itemresult[QStringLiteral("type")] = deHelper.getType(query.value(4).toInt());
        itemresult[QStringLiteral("state")] = deHelper.getState(query.value(5).toInt());
        itemresult[QStringLiteral("founded")] = query.value(6).toInt();
        itemresult[QStringLiteral("disbanded")] = query.value(9).toInt();
        itemresult[QStringLiteral("optional")] = query.value(10).toInt();
        itemresult[QStringLiteral("wikipedia")] = query.value(11).toString();
        itemresult[QStringLiteral("succId")] = query.value(7).toInt(); // id of the district it was merged in
        itemresult[QStringLiteral("succName")] = QStringLiteral("");
        itemresult[QStringLiteral("succType")] = QStringLiteral("");
        itemresult[QStringLiteral("succSign")] = QStringLiteral("");
        itemresult[QStringLiteral("tpoId")] = query.value(8).toInt(); // id of the the current district it is part of
        itemresult[QStringLiteral("tpoName")] = QStringLiteral("");
        itemresult[QStringLiteral("tpoType")] = QStringLiteral("");
        itemresult[QStringLiteral("tpoSign")] = QStringLiteral("");
        itemresult[QStringLiteral("optionalSigns")] = QStringLiteral("");
        itemresult[QStringLiteral("coa")] = query.value(12).toString();
    }

    if (itemresult[QStringLiteral("succId")].toInt() != 0)
    {
        query.exec(QStringLiteral("SELECT name, type, sign FROM de WHERE id = %1").arg(itemresult[QStringLiteral("succId")].toInt()));
        if (query.next())
        {
            itemresult[QStringLiteral("succName")] = query.value(0).toString();
            itemresult[QStringLiteral("succType")] = deHelper.getType(query.value(1).toInt());
            itemresult[QStringLiteral("succSign")] = query.value(2).toString();
        }
    }


    // check if district today belongs to another district than it was first merged into
    if (itemresult[QStringLiteral("succId")] != itemresult[QStringLiteral("tpoId")] && itemresult[QStringLiteral("tpoId")].toInt() != 0)
    {
        query.exec(QStringLiteral("SELECT name, type, sign FROM de WHERE id = %1").arg(itemresult[QStringLiteral("tpoId")].toInt()));
        if (query.next())
        {
            itemresult[QStringLiteral("tpoName")] = query.value(0).toString();
            itemresult[QStringLiteral("tpoType")] = deHelper.getType(query.value(1).toInt());
            itemresult[QStringLiteral("tpoSign")] = query.value(2).toString();
        }
    } else {
        itemresult[QStringLiteral("tpoId")] = 0;
    }

    if (itemresult[QStringLiteral("disbanded")].toInt() == 0)
    {

        QStringList optSigns;
        QList<int> subOptSignIds;
        QList<int> subSubOptSignIds;
        query.exec(QStringLiteral("SELECT id, sign FROM de WHERE successor = %1 AND optional > 0").arg(itemresult[QStringLiteral("itemId")].toInt()));
        while (query.next()) {
            subOptSignIds << query.value(0).toInt();
            optSigns << query.value(1).toString();
        }

        for (int i = 0; i < subOptSignIds.size(); ++i)
        {
            query.exec(QStringLiteral("SELECT id, sign FROM de WHERE successor = %1 AND optional > 0").arg(subOptSignIds.at(i)));
            while (query.next()) {
                subSubOptSignIds << query.value(0).toInt();
                optSigns << query.value(1).toString();
            }
        }

        for (int i = 0; i < subSubOptSignIds.size(); ++i)
        {
            query.exec(QStringLiteral("SELECT sign FROM de WHERE successor = %1 AND optional > 0").arg(subSubOptSignIds.at(i)));
            while (query.next()) {
                optSigns << query.value(0).toString();
            }
        }

        if (!optSigns.isEmpty())
            itemresult[QStringLiteral("optionalSigns")] = optSigns.join(QStringLiteral(", "));

    }

    return itemresult;
}
