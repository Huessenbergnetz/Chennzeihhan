#ifndef COUNTRYMODELFILTER_H
#define COUNTRYMODELFILTER_H

#include <QObject>
#include <QSortFilterProxyModel>
#include "../globals.h"

class QTimer;
class CountryModel;

class CountryModelFilter : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString search READ search WRITE setSearch NOTIFY searchChanged)
    Q_PROPERTY(Chennzeihhan::Target searchTarget READ searchTarget WRITE setSearchTarget NOTIFY searchTargetChanged)
    Q_PROPERTY(Chennzeihhan::Target sortTarget READ sortTarget WRITE setSortTarget NOTIFY sortTargetChanged)
    Q_PROPERTY(QString countryCode READ countryCode WRITE setCountryCode NOTIFY countryCodeChanged)
    Q_PROPERTY(bool inOperation READ inOperation NOTIFY inOperationChanged)
    Q_ENUMS(Chennzeihhan::Target)
public:
    explicit CountryModelFilter(QObject *parent = nullptr);

//    enum Target {
//        Code = 0,
//        Name = 1,
//        Both = 2
//    };
//    Q_ENUMS(Target)

    QString search() const;
    Chennzeihhan::Target searchTarget() const;
    Chennzeihhan::Target sortTarget() const;
    QString countryCode() const;
    bool inOperation() const;

    void setSearch(const QString &nSearch);
    void setSearchTarget(Chennzeihhan::Target nSearchTarget);
    void setSortTarget(Chennzeihhan::Target nSortTarget);
    void setCountryCode(const QString &nCountryCode);

signals:
    void searchChanged(const QString &search);
    void searchTargetChanged(Chennzeihhan::Target searchTarget);
    void sortTargetChanged(Chennzeihhan::Target sortTarget);
    void countryCodeChanged(const QString &countryCode);
    void inOperationChanged(bool inOperation);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private slots:
    void searchStringChanged();

private:
    Q_DISABLE_COPY(CountryModelFilter)
    QString m_search;
    Chennzeihhan::Target m_searchTarget;
    Chennzeihhan::Target m_sortTarget;
    QTimer *m_timer;
    CountryModel *m_cm;
};
//Q_DECLARE_METATYPE(CountryModelFilter::Target)

#endif // COUNTRYMODELFILTER_H
