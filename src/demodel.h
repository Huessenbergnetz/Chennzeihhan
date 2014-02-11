#ifndef DEMODEL_H
#define DEMODEL_H

#include <QSqlQueryModel>

#include "helper.h"

class DeModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit DeModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    QHash<int,QByteArray> roleNames() const;

signals:

public slots:
    void refresh(int sort, int searchTarget, const QString &search);

private:
    const static char* COLUMN_NAMES[];
    Helper *helper;

};

#endif // DEMODEL_H
