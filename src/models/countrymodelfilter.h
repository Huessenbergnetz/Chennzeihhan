#ifndef COUNTRYMODELFILTER_H
#define COUNTRYMODELFILTER_H

#include <QObject>
#include <QSortFilterProxyModel>

class QTimer;
class CountryModel;

class CountryModelFilter : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString search READ search WRITE setSearch NOTIFY searchChanged)
    Q_PROPERTY(Target searchTarget READ searchTarget WRITE setSearchTarget NOTIFY searchTargetChanged)
    Q_PROPERTY(Target sortTarget READ sortTarget WRITE setSortTarget NOTIFY sortTargetChanged)
    Q_PROPERTY(QString countryCode READ countryCode WRITE setCountryCode NOTIFY countryCodeChanged)
    Q_PROPERTY(bool inOperation READ inOperation NOTIFY inOperationChanged)
public:
    explicit CountryModelFilter(QObject *parent = nullptr);

    enum Target {
        Code = 0,
        Name = 1,
        Both = 2
    };
    Q_ENUMS(Target)

    QString search() const;
    Target searchTarget() const;
    Target sortTarget() const;
    QString countryCode() const;
    bool inOperation() const;

    void setSearch(const QString &nSearch);
    void setSearchTarget(Target nSearchTarget);
    void setSortTarget(Target nSortTarget);
    void setCountryCode(const QString &nCountryCode);

signals:
    void searchChanged(const QString &search);
    void searchTargetChanged(Target searchTarget);
    void sortTargetChanged(Target sortTarget);
    void countryCodeChanged(const QString &countryCode);
    void inOperationChanged(bool inOperation);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private slots:
    void searchStringChanged();

private:
    Q_DISABLE_COPY(CountryModelFilter)
    QString m_search;
    Target m_searchTarget;
    Target m_sortTarget;
    QTimer *m_timer;
    CountryModel *m_cm;
};
Q_DECLARE_METATYPE(CountryModelFilter::Target)

#endif // COUNTRYMODELFILTER_H
