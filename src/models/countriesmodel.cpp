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


void CountriesModel::refresh()
{

    if (tables.contains(lang)) {
        this->setQuery(QString("SELECT id AS itemId, code, sign, type, official, colors, %1 AS name FROM countries;").arg(lang));
    } else {
        this->setQuery(QString("SELECT id AS itemId, code, sign, type, official, colors, en AS name FROM countries;"));
    }
}
