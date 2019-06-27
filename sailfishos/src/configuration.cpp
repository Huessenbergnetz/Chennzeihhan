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

#include "configuration.h"
#ifdef QT_DEBUG
#include <QtDebug>
#endif

Configuration::Configuration(QObject *parent) :
    QSettings(parent)
{
    m_defaultSearchTarget = (Chennzeihhan::Target)value(QStringLiteral("display/search"), 0).toInt();
    m_defaultOrderTarget = (Chennzeihhan::Target)value(QStringLiteral("display/ordering"), 0).toInt();
    m_displayLanguage = value(QStringLiteral("display/language"), QStringLiteral("C")).toString();
    m_databaseVersion = value(QStringLiteral("database/version"), 0).toUInt();
}

void Configuration::setFav(const QString &sign)
{
    QStringList favs = value(QStringLiteral("display/favourites")).toString().split(QChar(','), QString::SkipEmptyParts);
    favs.append(sign);
    setValue(QStringLiteral("display/favourites"), favs.join(QChar(',')));

    emit favsChanged();
}



void Configuration::removeFav(const QString &sign)
{
    QStringList favs = value(QStringLiteral("display/favourites")).toString().split(QChar(','), QString::SkipEmptyParts);

    if (favs.contains(sign)) {
        favs.removeOne(sign);
    }

    setValue(QStringLiteral("display/favourites"), favs.join(QChar(',')));

    emit favsChanged();

}



QStringList Configuration::getFavs()
{
    return value(QStringLiteral("display/favourites")).toString().split(QChar(','), QString::SkipEmptyParts);
}



bool Configuration::isFav(const QString &sign)
{
    return value(QStringLiteral("display/favourites")).toString().split(QChar(','), QString::SkipEmptyParts).contains(sign);
}



void Configuration::set(const QString &key, const QString &val)
{
    setValue(key, val);

    emit configChanged();
}



QVariant Configuration::get(const QString &key, const QString &def)
{
    return value(key, def);
}



/*!
 * \property Configuration::defaultSearchTarget
 * \brief The default search target.
 *
 * \par Access functions:
 * <TABLE><TR><TD>Chennzeihhan::Target</TD><TD>defaultSearchTarget() const</TD></TR><TR><TD>void</TD><TD>setDefaultSearchTarget(Chennzeihhan::Target nDefaultSearchTarget)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>defaultSearchTargetChanged(Chennzeihhan::Target defaultSearchTarget)</TD></TR></TABLE>
 */


Chennzeihhan::Target Configuration::defaultSearchTarget() const { return m_defaultSearchTarget; }

void Configuration::setDefaultSearchTarget(Chennzeihhan::Target nDefaultSearchTarget)
{
    if (nDefaultSearchTarget != m_defaultSearchTarget) {
        m_defaultSearchTarget = nDefaultSearchTarget;
#ifdef QT_DEBUG
        qDebug() << "Changed defaultSearchTarget to" << m_defaultSearchTarget;
#endif
        setValue(QStringLiteral("display/search"), (int)m_defaultSearchTarget);
        emit defaultSearchTargetChanged(defaultSearchTarget());
    }
}




/*!
 * \property Configuration::defaultOrderTarget
 * \brief Thew default order target.
 *
 * \par Access functions:
 * <TABLE><TR><TD>Chennzeihhan::Target</TD><TD>defaultOrderTarget() const</TD></TR><TR><TD>void</TD><TD>setDefaultOrderTarget(Chennzeihhan::Target nDefaultOrderTarget)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>defaultOrderTargetChanged(Chennzeihhan::Target defaultOrderTarget)</TD></TR></TABLE>
 */


Chennzeihhan::Target Configuration::defaultOrderTarget() const { return m_defaultOrderTarget; }

void Configuration::setDefaultOrderTarget(Chennzeihhan::Target nDefaultOrderTarget)
{
    if (nDefaultOrderTarget != m_defaultOrderTarget) {
        m_defaultOrderTarget = nDefaultOrderTarget;
#ifdef QT_DEBUG
        qDebug() << "Changed defaultOrderTarget to" << m_defaultOrderTarget;
#endif
        setValue(QStringLiteral("display/ordering"), (int)m_defaultOrderTarget);
        emit defaultOrderTargetChanged(defaultOrderTarget());
    }
}




/*!
 * \property Configuration::displayLanguage
 * \brief The display language of the app.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>displayLanguage() const</TD></TR><TR><TD>void</TD><TD>setDisplayLanguage(const QString &nDisplayLanguage)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>displayLanguageChanged(const QString &displayLanguage)</TD></TR></TABLE>
 */


QString Configuration::displayLanguage() const { return m_displayLanguage; }

void Configuration::setDisplayLanguage(const QString &nDisplayLanguage)
{
    if (nDisplayLanguage != m_displayLanguage) {
        m_displayLanguage = nDisplayLanguage;
#ifdef QT_DEBUG
        qDebug() << "Changed displayLanguage to" << m_displayLanguage;
#endif
        setValue(QStringLiteral("display/language"), m_displayLanguage);
        emit displayLanguageChanged(displayLanguage());
    }
}




/*!
 * \property Configuration::databaseVersion
 * \brief The currently installed database version.
 *
 * \par Access functions:
 * <TABLE><TR><TD>uint</TD><TD>databaseVersion() const</TD></TR><TR><TD>void</TD><TD>setDatabaseVersion(uint nDatabaseVersion)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>databaseVersionChanged(uint databaseVersion)</TD></TR></TABLE>
 */


uint Configuration::databaseVersion() const { return m_databaseVersion; }

void Configuration::setDatabaseVersion(uint nDatabaseVersion)
{
    if (nDatabaseVersion != m_databaseVersion) {
        m_databaseVersion = nDatabaseVersion;
#ifdef QT_DEBUG
        qDebug() << "Changed databaseVersion to" << m_databaseVersion;
#endif
        setValue(QStringLiteral("database/version"), m_databaseVersion);
        emit databaseVersionChanged(databaseVersion());
    }
}



uint Configuration::minimumDbVersion() const
{
    return MIN_DB_VERSION;
}
