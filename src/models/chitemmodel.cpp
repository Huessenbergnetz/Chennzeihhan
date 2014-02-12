#include "chitemmodel.h"

ChItemModel::ChItemModel(QObject *parent) :
    QObject(parent)
{
}


QVariantMap ChItemModel::getItemData(int id)
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
