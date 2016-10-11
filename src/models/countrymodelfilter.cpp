#include "countrymodelfilter.h"
#include "countrymodel.h"
#include <QTimer>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

CountryModelFilter::CountryModelFilter(QObject *parent) : QSortFilterProxyModel(parent), m_timer(new QTimer(this)), m_cm(new CountryModel(this))
{
    m_searchTarget = Chennzeihhan::Code;
    m_sortTarget = Chennzeihhan::Code;
    m_timer->setSingleShot(true);
    m_timer->setInterval(300);
    m_timer->setTimerType(Qt::PreciseTimer);
    connect(m_timer, &QTimer::timeout, this, &CountryModelFilter::searchStringChanged);
    connect(m_cm, &CountryModel::inOperationChanged, this, &CountryModelFilter::inOperationChanged);
    setSourceModel(m_cm);
    setDynamicSortFilter(true);
    setSortLocaleAware(true);
    setSortRole(CountryModel::Sign);
    setFilterRole(CountryModel::Sign);
}



/*!
 * \property CountryModelFilter::search
 * \brief String to search.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>search() const</TD></TR><TR><TD>void</TD><TD>setSearch(const QString &nSearch)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>searchChanged(const QString &search)</TD></TR></TABLE>
 */


QString CountryModelFilter::search() const { return m_search; }

void CountryModelFilter::setSearch(const QString &nSearch)
{
    if (nSearch != m_search) {
        m_search = nSearch;
#ifdef QT_DEBUG
        qDebug() << "Changed search to" << m_search;
#endif
        emit searchChanged(search());
        m_timer->start();
    }
}




/*!
 * \property CountryModelFilter::searchTarget
 * \brief The search target.
 *
 * \par Access functions:
 * <TABLE><TR><TD>Chennzeihhan::Target</TD><TD>searchTarget() const</TD></TR><TR><TD>void</TD><TD>setSearchTarget(Chennzeihhan::Target nSearchTarget)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>searchTargetChanged(Chennzeihhan::Target searchTarget)</TD></TR></TABLE>
 */


Chennzeihhan::Target CountryModelFilter::searchTarget() const { return m_searchTarget; }

void CountryModelFilter::setSearchTarget(Chennzeihhan::Target nSearchTarget)
{
    if (nSearchTarget != m_searchTarget) {
        m_searchTarget = nSearchTarget;
#ifdef QT_DEBUG
        qDebug() << "Changed searchTarget to" << m_searchTarget;
#endif
        emit searchTargetChanged(searchTarget());
        if (!search().isEmpty()) {
            this->invalidate();
            this->invalidateFilter();
        }
    }
}




/*!
 * \property CountryModelFilter::sortTarget
 * \brief The sort target.
 *
 * \par Access functions:
 * <TABLE><TR><TD>Chennzeihhan::Target</TD><TD>sortTarget() const</TD></TR><TR><TD>void</TD><TD>setSortTarget(Chennzeihhan::Target nSortTarget)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>sortTargetChanged(Chennzeihhan::Target sortTarget)</TD></TR></TABLE>
 */


Chennzeihhan::Target CountryModelFilter::sortTarget() const { return m_sortTarget; }

void CountryModelFilter::setSortTarget(Chennzeihhan::Target nSortTarget)
{
    if (nSortTarget != m_sortTarget) {
        m_sortTarget = nSortTarget;
#ifdef QT_DEBUG
        qDebug() << "Changed sortTarget to" << m_sortTarget;
#endif
        emit sortTargetChanged(sortTarget());
        if (m_sortTarget == Chennzeihhan::Code) {
            setSortRole(CountryModel::Sign);
        } else {
            setSortRole(CountryModel::Name);
        }
        this->sort(0);
        if (!search().isEmpty()) {
            this->invalidate();
            this->invalidateFilter();
        }
    }
}



/*!
 * \property CountryModelFilter::countryCode
 * \brief Country code to request data for.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>countryCode() const</TD></TR><TR><TD>void</TD><TD>setCountryCode(const QString &nCountryCode)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>countryCodeChanged(const QString &countryCode)</TD></TR></TABLE>
 */


QString CountryModelFilter::countryCode() const { if (m_cm) { return m_cm->countryCode(); } else { return QString(); } }

void CountryModelFilter::setCountryCode(const QString &nCountryCode)
{
    if (m_cm) {
        m_cm->setCountryCode(nCountryCode);
        emit countryCodeChanged(countryCode());
    }
}




/*!
 * \property CountryModelFilter::inOperation
 * \brief Returns true, while the model is loading data.
 *
 * \par Access functions:
 * <TABLE><TR><TD>bool</TD><TD>inOperation() const</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>inOperationChanged(bool inOperation)</TD></TR></TABLE>
 */


bool CountryModelFilter::inOperation() const { if (m_cm) { return m_cm->inOperation(); } else { return false; } }




void CountryModelFilter::searchStringChanged()
{
    this->sort(0);
    this->invalidate();
    this->invalidateFilter();
}




bool CountryModelFilter::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex index = sourceModel()->index(source_row, 0, source_parent);

    switch(searchTarget()) {
    case Chennzeihhan::Code:
        return sourceModel()->data(index, CountryModel::Sign).toString().contains(search(), Qt::CaseInsensitive);
    case Chennzeihhan::Name:
        return sourceModel()->data(index, CountryModel::Name).toString().contains(search(), Qt::CaseInsensitive);
    default:
        return (sourceModel()->data(index, CountryModel::Sign).toString().contains(search(), Qt::CaseInsensitive) || sourceModel()->data(index, CountryModel::Name).toString().contains(search(), Qt::CaseInsensitive));
    }
}
