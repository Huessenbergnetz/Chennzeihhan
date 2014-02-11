#ifndef DEANTECESSORMODEL_H
#define DEANTECESSORMODEL_H

#include <QSqlQueryModel>

#include "helper.h"

class DeAntecessorModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit DeAntecessorModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    QHash<int,QByteArray> roleNames() const;

signals:

public slots:
    void refresh(int successor);

private:
    const static char* COLUMN_NAMES[];
    Helper *helper;

};

#endif // DEANTECESSORMODEL_H
