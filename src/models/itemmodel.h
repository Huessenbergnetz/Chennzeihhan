#ifndef ITEMMODEL_H
#define ITEMMODEL_H

#include <QObject>
#include <QSqlQuery>
#include <QVariantMap>
#include <QStringList>
#include "dehelper.h"

class ItemModel : public QObject
{
    Q_OBJECT
public:
    explicit ItemModel(QObject *parent = 0);

    Q_INVOKABLE QVariantMap getItemData(const QString &cc, int id);

signals:

public slots:

private:
    DeHelper *deHelper;
    QVariantMap getDeData(int id);
    QVariantMap getChData(int id);

};

#endif // ITEMMODEL_H
