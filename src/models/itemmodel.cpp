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
#include <QDebug>

ItemModel::ItemModel(QObject *parent) :
    QObject(parent)
{
}


QVariantMap ItemModel::getItemData(const QString &cc, int id)
{
    if (cc == "de") {
        return getDeData(id);
    } else if (cc == "ch") {
        return getChData(id);
    } else if (cc == "at") {
        return getAtData(id);
    }
}


QVariantMap ItemModel::getAtData(int id)
{
    QVariantMap itemresult;
    QSqlQuery query;
    query.exec(QString("SELECT id, sign, name, capital, type, state, assigned, successor, admin, closed, optional, wikipedia, coa FROM at WHERE id = %1").arg(id));

    if (query.next())
    {
        itemresult["itemId"] = query.value(0).toInt();
        itemresult["sign"] = query.value(1).toString();
        itemresult["name"] = query.value(2).toString();
        itemresult["capital"] = query.value(3).toString();
        itemresult["type"] = atHelper->getType(query.value(4).toInt());
        itemresult["state"] = atHelper->getState(query.value(5).toInt());
        itemresult["founded"] = query.value(6).toInt();
        itemresult["disbanded"] = query.value(9).toInt();
        itemresult["optional"] = query.value(10).toInt();
        itemresult["wikipedia"] = query.value(11).toString();
        itemresult["succId"] = query.value(7).toInt(); // id of the district it was merged in
        itemresult["succName"] = "";
        itemresult["succType"] = "";
        itemresult["succSign"] = "";
        itemresult["tpoId"] = query.value(8).toInt(); // id of the the current district it is part of
        itemresult["tpoName"] = "";
        itemresult["tpoType"] = "";
        itemresult["tpoSign"] = "";
        itemresult["optionalSigns"] = "";
        itemresult["coa"] = query.value(12).toString();
    }

    if (itemresult["succId"].toInt() != 0)
    {
        query.exec(QString("SELECT name, type, sign FROM at WHERE id = %1").arg(itemresult["succId"].toInt()));
        if (query.next())
        {
            itemresult["succName"] = query.value(0).toString();
            itemresult["succType"] = atHelper->getType(query.value(1).toInt());
            itemresult["succSign"] = query.value(2).toString();
        }
    }


    // check if district today belongs to another district than it was first merged into
    if (itemresult["succId"] != itemresult["tpoId"] && itemresult["tpoId"].toInt() != 0)
    {
        query.exec(QString("SELECT name, type, sign FROM at WHERE id = %1").arg(itemresult["tpoId"].toInt()));
        if (query.next())
        {
            itemresult["tpoName"] = query.value(0).toString();
            itemresult["tpoType"] = atHelper->getType(query.value(1).toInt());
            itemresult["tpoSign"] = query.value(2).toString();
        }
    } else {
        itemresult["tpoId"] = 0;
    }

    if (itemresult["disbanded"].toInt() == 0)
    {

        QStringList optSigns;
        QList<int> subOptSignIds;
        QList<int> subSubOptSignIds;
        query.exec(QString("SELECT id, sign FROM at WHERE successor = %1 AND optional > 0").arg(itemresult["itemId"].toInt()));
        while (query.next()) {
            subOptSignIds << query.value(0).toInt();
            optSigns << query.value(1).toString();
        }

        for (int i = 0; i < subOptSignIds.size(); ++i)
        {
            query.exec(QString("SELECT id, sign FROM at WHERE successor = %1 AND optional > 0").arg(subOptSignIds.at(i)));
            while (query.next()) {
                subSubOptSignIds << query.value(0).toInt();
                optSigns << query.value(1).toString();
            }
        }

        for (int i = 0; i < subSubOptSignIds.size(); ++i)
        {
            query.exec(QString("SELECT sign FROM at WHERE successor = %1 AND optional > 0").arg(subSubOptSignIds.at(i)));
            while (query.next()) {
                optSigns << query.value(0).toString();
            }
        }

        if (!optSigns.isEmpty())
            itemresult["optionalSigns"] = optSigns.join(", ");

    }

    return itemresult;
}


QVariantMap ItemModel::getChData(int id)
{
    QVariantMap itemresult;
    QSqlQuery query;
    query.exec(QString("SELECT id, sign, name, capital, wikipedia, coa FROM ch WHERE id = %1").arg(id));

    if (query.next())
    {
        itemresult["itemId"] = query.value(0).toInt();
        itemresult["sign"] = query.value(1).toString();
        itemresult["name"] = query.value(2).toString();
        itemresult["capital"] = query.value(3).toString();
        itemresult["wikipedia"] = query.value(4).toString();
        itemresult["coa"] = query.value(5).toString();
    }

    return itemresult;
}


QVariantMap ItemModel::getDeData(int id)
{
    QVariantMap itemresult;
    QSqlQuery query;
    query.exec(QString("SELECT id, sign, name, capitol, type, state, assign, successor, admin, closed, optional, wikipedia, coa FROM de WHERE id = %1").arg(id));

    if (query.next())
    {
        itemresult["itemId"] = query.value(0).toInt();
        itemresult["sign"] = query.value(1).toString();
        itemresult["name"] = query.value(2).toString();
        itemresult["capital"] = query.value(3).toString();
        itemresult["type"] = deHelper->getType(query.value(4).toInt());
        itemresult["state"] = deHelper->getState(query.value(5).toInt());
        itemresult["founded"] = query.value(6).toInt();
        itemresult["disbanded"] = query.value(9).toInt();
        itemresult["optional"] = query.value(10).toInt();
        itemresult["wikipedia"] = query.value(11).toString();
        itemresult["succId"] = query.value(7).toInt(); // id of the district it was merged in
        itemresult["succName"] = "";
        itemresult["succType"] = "";
        itemresult["succSign"] = "";
        itemresult["tpoId"] = query.value(8).toInt(); // id of the the current district it is part of
        itemresult["tpoName"] = "";
        itemresult["tpoType"] = "";
        itemresult["tpoSign"] = "";
        itemresult["optionalSigns"] = "";
        itemresult["coa"] = query.value(12).toString();
    }

    if (itemresult["succId"].toInt() != 0)
    {
        query.exec(QString("SELECT name, type, sign FROM de WHERE id = %1").arg(itemresult["succId"].toInt()));
        if (query.next())
        {
            itemresult["succName"] = query.value(0).toString();
            itemresult["succType"] = deHelper->getType(query.value(1).toInt());
            itemresult["succSign"] = query.value(2).toString();
        }
    }


    // check if district today belongs to another district than it was first merged into
    if (itemresult["succId"] != itemresult["tpoId"] && itemresult["tpoId"].toInt() != 0)
    {
        query.exec(QString("SELECT name, type, sign FROM de WHERE id = %1").arg(itemresult["tpoId"].toInt()));
        if (query.next())
        {
            itemresult["tpoName"] = query.value(0).toString();
            itemresult["tpoType"] = deHelper->getType(query.value(1).toInt());
            itemresult["tpoSign"] = query.value(2).toString();
        }
    } else {
        itemresult["tpoId"] = 0;
    }

    if (itemresult["disbanded"].toInt() == 0)
    {

        QStringList optSigns;
        QList<int> subOptSignIds;
        QList<int> subSubOptSignIds;
        query.exec(QString("SELECT id, sign FROM de WHERE successor = %1 AND optional > 0").arg(itemresult["itemId"].toInt()));
        while (query.next()) {
            subOptSignIds << query.value(0).toInt();
            optSigns << query.value(1).toString();
        }

        for (int i = 0; i < subOptSignIds.size(); ++i)
        {
            query.exec(QString("SELECT id, sign FROM de WHERE successor = %1 AND optional > 0").arg(subOptSignIds.at(i)));
            while (query.next()) {
                subSubOptSignIds << query.value(0).toInt();
                optSigns << query.value(1).toString();
            }
        }

        for (int i = 0; i < subSubOptSignIds.size(); ++i)
        {
            query.exec(QString("SELECT sign FROM de WHERE successor = %1 AND optional > 0").arg(subSubOptSignIds.at(i)));
            while (query.next()) {
                optSigns << query.value(0).toString();
            }
        }

        if (!optSigns.isEmpty())
            itemresult["optionalSigns"] = optSigns.join(", ");

    }

    return itemresult;
}
