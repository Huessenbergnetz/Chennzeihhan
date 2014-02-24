#ifndef ITEMMODEL_H
#define ITEMMODEL_H

#include <QObject>
#include <QSqlQuery>
#include <QVariantMap>
#include <QStringList>
#include "dehelper.h"
#include "athelper.h"

class ItemModel : public QObject
{
    Q_OBJECT
public:
    explicit ItemModel(QObject *parent = 0);

    Q_INVOKABLE QVariantMap getItemData(const QString &cc, int id);

signals:

public slots:

private:
    AtHelper *atHelper;
    DeHelper *deHelper;
    QVariantMap getAtData(int id);
    QVariantMap getDeData(int id);
    QVariantMap getChData(int id);

};

#endif // ITEMMODEL_H
