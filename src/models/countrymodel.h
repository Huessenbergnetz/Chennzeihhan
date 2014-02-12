#ifndef COUNTRYMODEL_H
#define COUNTRYMODEL_H

#include <QSqlQueryModel>

#include "dehelper.h"

class CountryModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit CountryModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    QHash<int,QByteArray> roleNames() const;

signals:

public slots:
    void refresh(const QString &cc, int sort, int searchTarget, const QString &search);

private:
    const static char* COLUMN_NAMES[];
    DeHelper *deHelper;
    QString countryCode;

};

#endif // COUNTRYMODEL_H
