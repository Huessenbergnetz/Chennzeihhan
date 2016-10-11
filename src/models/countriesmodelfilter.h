#ifndef COUNTRIESMODELFILTER_H
#define COUNTRIESMODELFILTER_H

#include <QObject>
#include <QSortFilterProxyModel>
#include "../globals.h"

class CountriesModelFilter : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(Chennzeihhan::Target searchTarget READ searchTarget WRITE setSearchTarget NOTIFY searchTargetChanged)
    Q_PROPERTY(Chennzeihhan::Target sortTarget READ sortTarget WRITE setSortTarget NOTIFY sortTargetChanged)
    Q_PROPERTY(QString search READ search WRITE setSearch NOTIFY searchChanged)
    Q_PROPERTY(QString firstChar READ firstChar WRITE setFirstChar NOTIFY firstCharChanged)
    Q_ENUMS(Chennzeihhan::Target)
public:
    explicit CountriesModelFilter(QObject *parent = nullptr);


    Chennzeihhan::Target searchTarget() const;
    Chennzeihhan::Target sortTarget() const;
    QString search() const;
    QString firstChar() const;

    void setSearchTarget(Chennzeihhan::Target nSearchTarget);
    void setSortTarget(Chennzeihhan::Target nSortTarget);
    void setSearch(const QString &nSearch);
    void setFirstChar(const QString &nFirstChar);

signals:
    void searchTargetChanged(Chennzeihhan::Target searchTarget);
    void sortTargetChanged(Chennzeihhan::Target sortTarget);
    void searchChanged(const QString &search);
    void firstCharChanged(const QString &firstChar);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

private:
    Q_DISABLE_COPY(CountriesModelFilter)
    Chennzeihhan::Target m_searchTarget;
    Chennzeihhan::Target m_sortTarget;
    QString m_search;
    QString m_firstChar;
};

#endif // COUNTRIESMODELFILTER_H
