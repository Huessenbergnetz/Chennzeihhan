#include "favoritesmodel.h"
#include <QSqlQuery>
#include <QCoreApplication>
#include "../configuration.h"

FavoritesModel::FavoritesModel(Configuration *conf, QObject *parent) : CountriesBaseModel(parent), m_conf(conf)
{
    if (m_conf) {
        m_favs = m_conf->value(QStringLiteral("display/favourites")).toString().split(QChar(','), QString::SkipEmptyParts);
    }
    init();
}



void FavoritesModel::init()
{
    clear();

    qDebug("Init favs");

    if (m_favs.isEmpty()) {
        qDebug("Favs emopty");
        return;
    }

    QString favs;
    for (int i = 0; i < m_favs.count(); ++i) {
        favs.append(QLatin1String("'"));
        favs.append(m_favs.at(i));
        favs.append(QLatin1String("'"));
        favs.append(QLatin1String(","));
    }
    favs.chop(1);

    QString queryString = getBaseQueryString();
    queryString.append(QStringLiteral(" WHERE sign IN (%1)").arg(favs));

    QSqlQuery q;
    if (q.exec(queryString)) {
        populate(&q);
    }
}


void FavoritesModel::remove(const QString &sign)
{
    if (removeBySign(sign)) {

        m_favs.removeAll(sign);

        m_conf->setValue(QStringLiteral("display/favourites"), m_favs.join(QChar(',')));

        emit modelChanged();
    }
}



void FavoritesModel::add(const QString &sign)
{
    QString queryString = getBaseQueryString();
    queryString.append(QStringLiteral(" WHERE sign = \"%1\"").arg(sign));

    QSqlQuery q;
    if (q.exec(queryString)) {

        if (q.next()) {

            m_favs.append(sign);
            m_conf->setValue(QStringLiteral("display/favourites"), m_favs.join(QChar(',')));

            addCountry(new Country(q.value(0).toUInt(),
                                   q.value(1).toString(),
                                   q.value(2).toString(),
                                   q.value(3).toUInt(),
                                   q.value(4).toBool(),
                                   q.value(5).toString().split(QChar(',')),
                                   QCoreApplication::translate("DBStrings", q.value(6).toString().toUtf8().constData())
                                   ));

            emit modelChanged();

        }
    }
}



bool FavoritesModel::isFav(const QString &sign)
{
    return m_favs.contains(sign);
}
