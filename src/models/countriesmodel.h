#ifndef COUNTRIESMODEL_H
#define COUNTRIESMODEL_H

#include <QSqlQueryModel>
#include <QLocale>

class CountriesModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit CountriesModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    QHash<int,QByteArray> roleNames() const;

signals:

public slots:
    void refresh(const QString search, int target, int sort);

private:
    const static char* COLUMN_NAMES[];
    QString lang;

};

#endif // COUNTRIESMODEL_H
