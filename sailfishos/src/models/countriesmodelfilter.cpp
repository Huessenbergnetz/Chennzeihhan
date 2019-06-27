/*
    Chennzeihhan - Vehicle Registration Code Database for SailfishOS
    Copyright (C) 2014-2019 Hüssenbergnetz/Matthias Fehring

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "countriesmodelfilter.h"
#include "countriesmodelnew.h"
#ifdef QT_DEBUG
#include <QtDebug>
#endif

CountriesModelFilter::CountriesModelFilter(QObject *parent) : QSortFilterProxyModel(parent)
{
    setSourceModel(new CountriesModelNew(this));
    m_searchTarget = Chennzeihhan::Code;
    m_sortTarget = Chennzeihhan::Code;
    setSortRole(CountriesModelNew::Sign);
    setDynamicSortFilter(true);
    setSortLocaleAware(true);
}



/*!
 * \property CountriesModelFilter::searchTarget
 * \brief The searchTarget property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>Chennzeihhan::Target</TD><TD>searchTarget() const</TD></TR><TR><TD>void</TD><TD>setSearchTarget(Chennzeihhan::Target nSearchTarget)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>searchTargetChanged(Chennzeihhan::Target searchTarget)</TD></TR></TABLE>
 */


Chennzeihhan::Target CountriesModelFilter::searchTarget() const { return m_searchTarget; }

void CountriesModelFilter::setSearchTarget(Chennzeihhan::Target nSearchTarget)
{
    if (nSearchTarget != m_searchTarget) {
        m_searchTarget = nSearchTarget;
#ifdef QT_DEBUG
        qDebug() << "Changed searchTarget to" << m_searchTarget;
#endif
        emit searchTargetChanged(searchTarget());
        this->invalidateFilter();
    }
}




/*!
 * \property CountriesModelFilter::sortTarget
 * \brief The sortTarget property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>Chennzeihhan::Target</TD><TD>sortTarget() const</TD></TR><TR><TD>void</TD><TD>setSortTarget(Chennzeihhan::Target nSortTarget)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>sortTargetChanged(Chennzeihhan::Target sortTarget)</TD></TR></TABLE>
 */


Chennzeihhan::Target CountriesModelFilter::sortTarget() const { return m_sortTarget; }

void CountriesModelFilter::setSortTarget(Chennzeihhan::Target nSortTarget)
{
    if (nSortTarget != m_sortTarget) {
        m_sortTarget = nSortTarget;
#ifdef QT_DEBUG
        qDebug() << "Changed sortTarget to" << m_sortTarget;
#endif
        emit sortTargetChanged(sortTarget());
        if (m_sortTarget == Chennzeihhan::Code) {
            setSortRole(CountriesModelNew::Sign);
        } else {
            setSortRole(CountriesModelNew::Name);
        }
        this->sort(0);
        this->invalidate();
    }
}




/*!
 * \property CountriesModelFilter::search
 * \brief The search property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>search() const</TD></TR><TR><TD>void</TD><TD>setSearch(const QString &nSearch)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>searchChanged(const QString &search)</TD></TR></TABLE>
 */


QString CountriesModelFilter::search() const { return m_search; }

void CountriesModelFilter::setSearch(const QString &nSearch)
{
    if (nSearch != m_search) {
        m_search = nSearch;
#ifdef QT_DEBUG
        qDebug() << "Changed search to" << m_search;
#endif
        emit searchChanged(search());
        this->invalidateFilter();
    }
}




/*!
 * \property CountriesModelFilter::firstChar
 * \brief The firstChar property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>firstChar() const</TD></TR><TR><TD>void</TD><TD>setFirstChar(const QString &nFirstChar)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>firstCharChanged(const QString &firstChar)</TD></TR></TABLE>
 */


QString CountriesModelFilter::firstChar() const { return m_firstChar; }

void CountriesModelFilter::setFirstChar(const QString &nFirstChar)
{
    if (nFirstChar != m_firstChar) {
        m_firstChar = nFirstChar;
#ifdef QT_DEBUG
        qDebug() << "Changed firstChar to" << m_firstChar;
#endif
        emit firstCharChanged(firstChar());
        this->invalidateFilter();
    }
}




bool CountriesModelFilter::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex index = sourceModel()->index(source_row, 0, source_parent);

    if (!search().isEmpty()) {
        switch(searchTarget()) {
        case Chennzeihhan::Code:
            return sourceModel()->data(index, CountriesModelNew::Sign).toString().contains(search(), Qt::CaseInsensitive);
        case Chennzeihhan::Name:
            return sourceModel()->data(index, CountriesModelNew::Name).toString().contains(search(), Qt::CaseInsensitive);
        default:
            return (sourceModel()->data(index, CountriesModelNew::Name).toString().contains(search(), Qt::CaseInsensitive)) || (sourceModel()->data(index, CountriesModelNew::Sign).toString().contains(search(), Qt::CaseInsensitive));
        }
    } else if (!firstChar().isEmpty()) {
        if (sortTarget() == Chennzeihhan::Code) {
            return sourceModel()->data(index, CountriesModelNew::Sign).toString().startsWith(firstChar(), Qt::CaseInsensitive);
        } else {
            return sourceModel()->data(index, CountriesModelNew::Name).toString().startsWith(firstChar(), Qt::CaseInsensitive);
        }
    } else {
        return false;
    }
}
