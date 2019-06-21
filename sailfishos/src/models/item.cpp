/*
    Chennzeihhan - Vehicle Registration Code Database for SailfishOS
    Copyright (C) 2014-2016  Buschtrommel/Matthias Fehring

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

#include "item.h"
#include "../coverconnector.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

/*!
 * \brief Constructs a new Item object.
 */
Item::Item(QObject *parent) :
    QObject(parent)
{
    m_founded = 0;
    m_disbanded = 0;
    m_optional = 0;
    m_inOperation = false;
    m_id = 0;
    m_coverConnector = nullptr;
}


/*!
 * \brief Deconstructs the Item object.
 */
Item::~Item()
{
}


/*!
 * \property Item::sign
 * \brief The car plate sign.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>sign() const</TD></TR><TR><TD>void</TD><TD>setSign(const QString &nSign)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>signChanged(const QString &sign)</TD></TR></TABLE>
 */


QString Item::sign() const { return m_sign; }

void Item::setSign(const QString &nSign)
{
    if (nSign != m_sign) {
        m_sign = nSign;
#ifdef QT_DEBUG
        qDebug() << "Changed sign to" << m_sign;
#endif
        emit signChanged(sign());
        if (m_coverConnector) {
            m_coverConnector->setSign(m_sign);
        }
    }
}




/*!
 * \property Item::name
 * \brief The name of the district.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>name() const</TD></TR><TR><TD>void</TD><TD>setName(const QString &nName)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>nameChanged(const QString &name)</TD></TR></TABLE>
 */


QString Item::name() const { return m_name; }

void Item::setName(const QString &nName)
{
    if (nName != m_name) {
        m_name = nName;
#ifdef QT_DEBUG
        qDebug() << "Changed name to" << m_name;
#endif
        emit nameChanged(name());
        if (m_coverConnector) {
            m_coverConnector->setName(m_name);
        }
    }
}




/*!
 * \property Item::capital
 * \brief The name of the districts capital.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>capital() const</TD></TR><TR><TD>void</TD><TD>setCapital(const QString &nCapital)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>capitalChanged(const QString &capital)</TD></TR></TABLE>
 */


QString Item::capital() const { return m_capital; }

void Item::setCapital(const QString &nCapital)
{
    if (nCapital != m_capital) {
        m_capital = nCapital;
#ifdef QT_DEBUG
        qDebug() << "Changed capital to" << m_capital;
#endif
        emit capitalChanged(capital());
    }
}




/*!
 * \property Item::type
 * \brief The type of the district.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>type() const</TD></TR><TR><TD>void</TD><TD>setType(const QString &nType)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>typeChanged(const QString &type)</TD></TR></TABLE>
 */


QString Item::type() const { return m_type; }

void Item::setType(const QString &nType)
{
    if (nType != m_type) {
        m_type = nType;
#ifdef QT_DEBUG
        qDebug() << "Changed type to" << m_type;
#endif
        emit typeChanged(type());
        if (m_coverConnector) {
            m_coverConnector->setType(m_type);
        }
    }
}




/*!
 * \property Item::state
 * \brief Name of the state the district belongs to.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>state() const</TD></TR><TR><TD>void</TD><TD>setState(const QString &nState)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>stateChanged(const QString &state)</TD></TR></TABLE>
 */


QString Item::state() const { return m_state; }

void Item::setState(const QString &nState)
{
    if (nState != m_state) {
        m_state = nState;
#ifdef QT_DEBUG
        qDebug() << "Changed state to" << m_state;
#endif
        emit stateChanged(state());
        if (m_coverConnector) {
            m_coverConnector->setState(m_state);
        }
    }
}




/*!
 * \property Item::founded
 * \brief The year the district was founded.
 *
 * \par Access functions:
 * <TABLE><TR><TD>quint16</TD><TD>founded() const</TD></TR><TR><TD>void</TD><TD>setFounded(quint16 nFounded)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>foundedChanged(quint16 founded)</TD></TR></TABLE>
 */


quint16 Item::founded() const { return m_founded; }

void Item::setFounded(quint16 nFounded)
{
    if (nFounded != m_founded) {
        m_founded = nFounded;
#ifdef QT_DEBUG
        qDebug() << "Changed founded to" << m_founded;
#endif
        emit foundedChanged(founded());
    }
}




/*!
 * \property Item::disbanded
 * \brief The year the district was disbanded.
 *
 * \par Access functions:
 * <TABLE><TR><TD>quint16</TD><TD>disbanded() const</TD></TR><TR><TD>void</TD><TD>setDisbanded(quint16 nDisbanded)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>disbandedChanged(quint16 disbanded)</TD></TR></TABLE>
 */


quint16 Item::disbanded() const { return m_disbanded; }

void Item::setDisbanded(quint16 nDisbanded)
{
    if (nDisbanded != m_disbanded) {
        m_disbanded = nDisbanded;
#ifdef QT_DEBUG
        qDebug() << "Changed disbanded to" << m_disbanded;
#endif
        emit disbandedChanged(disbanded());
    }
}




/*!
 * \property Item::optional
 * \brief The year since when the car plate sign is available optional.
 *
 * \par Access functions:
 * <TABLE><TR><TD>quint16</TD><TD>optional() const</TD></TR><TR><TD>void</TD><TD>setOptional(quint16 nOptional)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>optionalChanged(quint16 optional)</TD></TR></TABLE>
 */


quint16 Item::optional() const { return m_optional; }

void Item::setOptional(quint16 nOptional)
{
    if (nOptional != m_optional) {
        m_optional = nOptional;
#ifdef QT_DEBUG
        qDebug() << "Changed optional to" << m_optional;
#endif
        emit optionalChanged(optional());
    }
}




/*!
 * \property Item::wikipedia
 * \brief Name of the wikipedia page.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>wikipedia() const</TD></TR><TR><TD>void</TD><TD>setWikipedia(const QString &nWikipedia)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>wikipediaChanged(const QString &wikipedia)</TD></TR></TABLE>
 */


QString Item::wikipedia() const { return m_wikipedia; }

void Item::setWikipedia(const QString &nWikipedia)
{
    if (nWikipedia != m_wikipedia) {
        m_wikipedia = nWikipedia;
#ifdef QT_DEBUG
        qDebug() << "Changed wikipedia to" << m_wikipedia;
#endif
        emit wikipediaChanged(wikipedia());
    }
}




/*!
 * \property Item::coa
 * \brief ID of the coat of arms/logo of the district.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>coa() const</TD></TR><TR><TD>void</TD><TD>setCoa(const QString &nCoa)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>coaChanged(const QString &coa)</TD></TR></TABLE>
 */


QString Item::coa() const { return m_coa; }

void Item::setCoa(const QString &nCoa)
{
    if (nCoa != m_coa) {
        m_coa = nCoa;
#ifdef QT_DEBUG
        qDebug() << "Changed coa to" << m_coa;
#endif
        emit coaChanged(coa());
    }
}




/*!
 * \property Item::inOperation
 * \brief Returns true while the data is requested.
 *
 * \par Access functions:
 * <TABLE><TR><TD>bool</TD><TD>inOperation() const</TD></TR><TR><TD>void</TD><TD>setInOperation(bool nInOperation)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>inOperationChanged(bool inOperation)</TD></TR></TABLE>
 */


bool Item::inOperation() const { return m_inOperation; }

void Item::setInOperation(bool nInOperation)
{
    if (nInOperation != m_inOperation) {
        m_inOperation = nInOperation;
#ifdef QT_DEBUG
        qDebug() << "Changed inOperation to" << m_inOperation;
#endif
        emit inOperationChanged(inOperation());
    }
}




/*!
 * \property Item::id
 * \brief Database ID of the item.
 *
 * \par Access functions:
 * <TABLE><TR><TD>uint</TD><TD>id() const</TD></TR><TR><TD>void</TD><TD>setId(uint nId)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>idChanged(uint id)</TD></TR></TABLE>
 */


uint Item::id() const { return m_id; }

void Item::setId(uint nId)
{
    if (nId != m_id) {
        m_id = nId;
#ifdef QT_DEBUG
        qDebug() << "Changed id to" << m_id;
#endif
        emit idChanged(id());
        query();
    }
}




/*!
 * \property Item::countryCode
 * \brief The countryCode property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>countryCode() const</TD></TR></TABLE>
 */

QString Item::countryCode() const { return m_countryCode; }

void Item::setCountryCode(const QString &cc) { m_countryCode = cc; }


/*!
 * \property Item::countryName
 * \brief The countryName property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>countryName() const</TD></TR></TABLE>
 */

QString Item::countryName() const { return m_countryName; }

void Item::setCountryName(const QString &cn) { m_countryName = cn; if (coverConnector()) {coverConnector()->setCountry(cn);} }



/*!
 * \property Item::coverConnector
 * \brief Pointer to a covver connector object.
 *
 * \par Access functions:
 * <TABLE><TR><TD>CoverConnector*</TD><TD>coverConnector() const</TD></TR><TR><TD>void</TD><TD>setCoverConnector(CoverConnector *nCoverConnector)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>coverConnectorChanged(CoverConnector *coverConnector)</TD></TR></TABLE>
 */


CoverConnector *Item::coverConnector() const { return m_coverConnector; }

void Item::setCoverConnector(CoverConnector *nCoverConnector)
{
    if (nCoverConnector != m_coverConnector) {
        m_coverConnector = nCoverConnector;
#ifdef QT_DEBUG
        qDebug() << "Changed coverConnector to" << m_coverConnector;
#endif
        emit coverConnectorChanged(coverConnector());
        if (m_coverConnector) {
            m_coverConnector->setCountry(countryName());
            m_coverConnector->setName(name());
            m_coverConnector->setType(type());
            m_coverConnector->setSign(sign());
            m_coverConnector->setState(state());
        }
    }
}



void Item::clear()
{
    m_sign.clear();
    emit signChanged(m_sign);
    m_name.clear();
    emit nameChanged(m_name);
    m_capital.clear();
    emit capitalChanged(m_capital);
    m_type.clear();
    emit typeChanged(m_type);
    m_state.clear();
    emit stateChanged(m_state);
    m_founded = 0;
    emit foundedChanged(0);
    m_disbanded = 0;
    emit disbandedChanged(0);
    m_optional = 0;
    emit optionalChanged(0);
    m_wikipedia.clear();
    emit wikipediaChanged(m_wikipedia);
    m_coa.clear();
    emit coaChanged(m_coa);
}



void Item::query()
{
    if ((id() <= 0) || countryCode().isEmpty()) {
        return;
    }

    QSqlQuery q;
    if (q.exec(QStringLiteral("SELECT sign, name, capital, wikipedia, coa FROM %1 WHERE id = %2").arg(countryCode()).arg(id()))) {

        if (q.next()) {
            setSign(q.value(0).toString());
            setName(q.value(1).toString());
            setCapital(q.value(2).toString());
            setWikipedia(q.value(3).toString());
            setCoa(q.value(4).toString());
        }

    } else {
        qCritical("Failed to perform query: %s", qPrintable(q.lastError().text()));
    }
}
