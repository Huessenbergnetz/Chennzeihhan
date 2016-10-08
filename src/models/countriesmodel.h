#ifndef COUNTRIESMODEL_H
#define COUNTRIESMODEL_H

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSettings>
#include <QLocale>
#include <QStringList>

class CountriesModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit CountriesModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const;
    QHash<int,QByteArray> roleNames() const;

public slots:
    void refresh(const QString &search, int target, int sort);
    void setFirstChar(const QString &fc, int target);
    void getFavs();
    QStringList getAbc(int sort);

private:
    const static char* COLUMN_NAMES[];
    QString lang;
    QSettings settings;

};

#endif // COUNTRIESMODEL_H
