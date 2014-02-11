#ifndef DEITEMMODEL_H
#define DEITEMMODEL_H

#include <QObject>
#include <QSqlQuery>
#include <QVariantMap>
#include <QStringList>

#include "helper.h"

class DeItemModel : public QObject
{
    Q_OBJECT
public:
    explicit DeItemModel(QObject *parent = 0);

    Q_INVOKABLE QVariantMap getItemData(int id);

signals:

public slots:

private:
    bool isValid(const QString &assign, int closed);

    Helper helper;

};

#endif // DEITEMMODEL_H
