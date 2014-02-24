#include "antecessormodel.h"

const char* AntecessorModel::COLUMN_NAMES[] = {
    "itemId",
    "sign",
    "name",
    "type",
    NULL
};

AntecessorModel::AntecessorModel(QObject *parent) :
    QSqlQueryModel(parent)
{
}


QHash<int,QByteArray> AntecessorModel::roleNames() const
{
    int idx = 0;
    QHash<int, QByteArray> roles;
    while (COLUMN_NAMES[idx]) {
        roles[Qt::UserRole + idx + 1] = COLUMN_NAMES[idx];
        idx++;
    }
    return roles;
}



QVariant AntecessorModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);

    if(role < Qt::UserRole)
    {
        value = QSqlQueryModel::data(index, role);
    } else {
        int columnIdx = role - Qt::UserRole - 1;
        QModelIndex modelIndex = this->index(index.row(), columnIdx);
        value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
        if (columnIdx == 3) {

            if (countryCode == "at") {
                value = atHelper->getType(value.toInt());
            } else if (countryCode == "de") {
                value = deHelper->getType(value.toInt());
            }

        } else if (columnIdx == 4) {

            if (countryCode == "at") {
                value = atHelper->getState(value.toInt());
            } else if (countryCode == "de") {
                value = deHelper->getState(value.toInt());
            }
        }
    }

    return value;

}


void AntecessorModel::refresh(const QString &cc, int successor)
{
    countryCode = cc;

    this->setQuery(QString("SELECT id AS itemId, sign, name, type FROM %1 WHERE successor = %2").arg(cc).arg(successor));

//    this->setQuery(QString("SELECT id AS itemId, sign, name, type FROM de WHERE successor = %1").arg(successor));
}
