#ifndef ITEMMODEL_H
#define ITEMMODEL_H

#include <QObject>
#include <QSqlQuery>
#include <QVariantMap>
#include <QStringList>

class ItemModel : public QObject
{
    Q_OBJECT
public:
    explicit ItemModel(QObject *parent = nullptr);

    Q_INVOKABLE QVariantMap getItemData(const QString &cc, int id);

private:
    QVariantMap getAtData(int id);
    QVariantMap getDeData(int id);
    QVariantMap getChData(int id);

};

#endif // ITEMMODEL_H
