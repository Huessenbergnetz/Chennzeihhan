#ifndef CHITEMMODEL_H
#define CHITEMMODEL_H

#include <QObject>
#include <QSqlQuery>
#include <QVariantMap>

class ChItemModel : public QObject
{
    Q_OBJECT
public:
    explicit ChItemModel(QObject *parent = 0);

    Q_INVOKABLE QVariantMap getItemData(int id);

signals:

public slots:

};

#endif // CHITEMMODEL_H
