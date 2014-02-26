#include "countriesmodel.h"
#include "../globals.h"

const char* CountriesModel::COLUMN_NAMES[] = {
    "itemId",
    "code",
    "sign",
    "type",
    "official",
    "colors",
    "name",
    NULL
};

CountriesModel::CountriesModel(QObject *parent) :
    QSqlQueryModel(parent)
{
    lang = QLocale::system().name().left(2);
}




QHash<int,QByteArray> CountriesModel::roleNames() const
{
    int idx = 0;
    QHash<int, QByteArray> roles;
    while (COLUMN_NAMES[idx]) {
        roles[Qt::UserRole + idx + 1] = COLUMN_NAMES[idx];
        idx++;
    }
    return roles;
}



QVariant CountriesModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);

    if(role < Qt::UserRole)
    {
        value = QSqlQueryModel::data(index, role);
    } else {
        int columnIdx = role - Qt::UserRole - 1;
        QModelIndex modelIndex = this->index(index.row(), columnIdx);
        value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
    }

    return value;
}


void CountriesModel::refresh(const QString &search, int target, int sort)
{

    QString queryString;

    if (tables.contains(lang)) {
        queryString = QString("SELECT id AS itemId, code, sign, type, official, colors, %1 AS name FROM countries").arg(lang);
    } else {
        queryString =  QString("SELECT id AS itemId, code, sign, type, official, colors, en AS name FROM countries");
    }


    if (!search.isEmpty())
    {
        QString t_search = search;
        t_search.prepend("%");
        t_search.append("%");

        switch(target) {
        case 1:
            queryString.append(QString(" WHERE name LIKE \"%1\"").arg(t_search));
            break;
        case 2:
            queryString.append(QString(" WHERE (name LIKE \"%1\") OR (sign LIKE \"%1\")").arg(t_search));
            break;
        default:
            queryString.append(QString(" WHERE sign LIKE \"%1\"").arg(t_search));
            break;
        }
    }


    switch(sort) {
    case 1:
        queryString.append(" ORDER BY name ASC");
        break;
    default:
        queryString.append(" ORDER BY sign ASC");
        break;
    }

    this->setQuery(queryString);
}



void CountriesModel::setFirstChar(const QString &fc, int target)
{
    QString queryString;

    if (tables.contains(lang)) {
        queryString = QString("SELECT id AS itemId, code, sign, type, official, colors, %1 AS name FROM countries").arg(lang);
    } else {
        queryString =  QString("SELECT id AS itemId, code, sign, type, official, colors, en AS name FROM countries");
    }

    QString t_search = fc;
//    t_search.prepend("%");
    t_search.append("%");

    switch(target) {
    case 1:
        queryString.append(QString(" WHERE name LIKE \"%1\"").arg(t_search));
        break;
    default:
        queryString.append(QString(" WHERE sign LIKE \"%1\"").arg(t_search));
        break;
    }

    switch(target) {
    case 1:
        queryString.append(" ORDER BY name ASC");
        break;
    default:
        queryString.append(" ORDER BY sign ASC");
        break;
    }


    this->setQuery(queryString);
}



void CountriesModel::getFavs()
{
    QStringList favList = settings.value("display/favourites", "").toString().split(",");
    QString favs;
    for (int i = 0; i < favList.size(); ++i) {
        if (!favList.at(i).isEmpty()) {
            favs.append("'");
            favs.append(favList.at(i));
            favs.append("'");
            if (i < favList.size()-1)
            favs.append(",");
        }
    }


    QString queryString;

    if (tables.contains(lang)) {
        queryString = QString("SELECT id AS itemId, code, sign, type, official, colors, %1 AS name FROM countries").arg(lang);
    } else {
        queryString =  QString("SELECT id AS itemId, code, sign, type, official, colors, en AS name FROM countries");
    }

    queryString.append(QString(" WHERE sign IN (%1)").arg(favs));

    this->setQuery(queryString);
}
