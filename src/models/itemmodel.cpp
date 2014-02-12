#include "itemmodel.h"

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
    }
}


QVariantMap ItemModel::getChData(int id)
{
    QVariantMap itemresult;
    QSqlQuery query;
    query.exec(QString("SELECT id, sign, name, capital, wikipedia FROM ch WHERE id = %1").arg(id));

    if (query.next())
    {
        itemresult["itemId"] = query.value(0).toInt();
        itemresult["sign"] = query.value(1).toString();
        itemresult["name"] = query.value(2).toString();
        itemresult["capital"] = query.value(3).toString();
        itemresult["wikipedia"] = query.value(4).toString();
    }

    return itemresult;
}


QVariantMap ItemModel::getDeData(int id)
{
    QVariantMap itemresult;
    QSqlQuery query;
    query.exec(QString("SELECT id, sign, name, capitol, type, state, assign, successor, admin, closed, optional, wikipedia FROM de WHERE id = %1").arg(id));

    if (query.next())
    {
        itemresult["itemId"] = query.value(0).toInt();
        itemresult["sign"] = query.value(1).toString();
        itemresult["name"] = query.value(2).toString();
        itemresult["capitol"] = query.value(3).toString();
        itemresult["type"] = deHelper->getType(query.value(4).toInt());
        itemresult["state"] = deHelper->getState(query.value(5).toInt());
        itemresult["assign"] = query.value(6).toString();
        itemresult["successor"] = query.value(7).toInt();
        itemresult["admin"] = query.value(8).toString();
        itemresult["closed"] = query.value(9).toInt();
        itemresult["optional"] = query.value(10).toInt();
        itemresult["wikipedia"] = query.value(11).toString();
        itemresult["valid"] = deHelper->isValid(itemresult["assign"].toString(), itemresult["closed"].toInt());
        itemresult["succId"] = 0;
        itemresult["succName"] = "";
        itemresult["succType"] = "";
        itemresult["succSign"] = "";
        itemresult["optionalSigns"] = "";
    }

    if (itemresult["successor"].toInt() != 0)
    {
        query.exec(QString("SELECT id, name, type, sign FROM de WHERE id = %1").arg(itemresult["successor"].toInt()));
        if (query.next())
        {
            itemresult["succId"] = query.value(0).toInt();
            itemresult["succName"] = query.value(1).toString();
            itemresult["succType"] = deHelper->getType(query.value(2).toInt());
            itemresult["succSign"] = query.value(3).toString();
        }
    }

    QStringList optSigns;
    query.exec(QString("SELECT sign FROM de WHERE successor = %1 AND optional > 0").arg(itemresult["itemId"].toInt()));
    while (query.next()) {
        optSigns << query.value(0).toString();
    }
    if (!optSigns.isEmpty())
        itemresult["optionalSigns"] = optSigns.join(", ");


    return itemresult;
}
