#ifndef ANTECESSORMODEL_H
#define ANTECESSORMODEL_H

#include <QSqlQueryModel>
#include "dehelper.h"
#include "athelper.h"

class AntecessorModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit AntecessorModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const;
    QHash<int,QByteArray> roleNames() const;

public slots:
    void refresh(const QString &cc, int successor);

private:
    const static char* COLUMN_NAMES[];
    QString countryCode;
    AtHelper *atHelper;
    DeHelper *deHelper;
};

#endif // ANTECESSORMODEL_H
