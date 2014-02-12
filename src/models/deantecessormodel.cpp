#include "deantecessormodel.h"

const char* DeAntecessorModel::COLUMN_NAMES[] = {
    "itemId",
    "sign",
    "name",
    "type",
    NULL
};

DeAntecessorModel::DeAntecessorModel(QObject *parent) :
    QSqlQueryModel(parent)
{
}


QHash<int,QByteArray> DeAntecessorModel::roleNames() const
{
    int idx = 0;
    QHash<int, QByteArray> roles;
    while (COLUMN_NAMES[idx]) {
        roles[Qt::UserRole + idx + 1] = COLUMN_NAMES[idx];
        idx++;
    }
    return roles;
}


QVariant DeAntecessorModel::data(const QModelIndex &index, int role) const
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

            value = helper->getType(value.toInt());

        } else if (columnIdx == 4) {

            value = helper->getState(value.toInt());
        }
    }

    return value;

}


void DeAntecessorModel::refresh(int successor)
{
    this->setQuery(QString("SELECT id AS itemId, sign, name, type FROM de WHERE successor = %1").arg(successor));
}
