#ifndef FAVORITESMODEL_H
#define FAVORITESMODEL_H

#include <QObject>
#include "countriesbasemodel.h"

class Configuration;

class FavoritesModel : public CountriesBaseModel
{
    Q_OBJECT
public:
    explicit FavoritesModel(Configuration *conf, QObject *parent = nullptr);

    void init();

    Q_INVOKABLE void remove(const QString &sign);
    Q_INVOKABLE void add(const QString &sign);
    Q_INVOKABLE bool isFav(const QString &sign);

signals:
    void modelChanged();

private:
    Q_DISABLE_COPY(FavoritesModel)
    Configuration *m_conf;
    QStringList m_favs;
};

#endif // FAVORITESMODEL_H
