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

#include "extendeditem.h"
#include "simpleitemmodel.h"
#include <QCoreApplication>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

/*!
 * \brief Constructs a new ExtendedItem object.
 */
ExtendedItem::ExtendedItem(QObject *parent) :
    Item(parent), m_antecessors(new SimpleItemModel(this)), m_successorId(0), m_tpoId(0)
{

}


/*!
 * \brief Deconstructs the ExtendedItem object.
 */
ExtendedItem::~ExtendedItem()
{
}


/*!
 * \property ExtendedItem::antecessors
 * \brief The antecessors property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>SimpleItemModel*</TD><TD>antecessors() const</TD></TR></TABLE>
 */


SimpleItemModel *ExtendedItem::antecessors() const { return m_antecessors; }



/*!
 * \property ExtendedItem::successor
 * \brief Name of the successor district.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>successor() const</TD></TR><TR><TD>void</TD><TD>setSuccessor(const QString &nSuccessor)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>successorChanged(const QString &successor)</TD></TR></TABLE>
 */


QString ExtendedItem::successor() const { return m_successor; }

void ExtendedItem::setSuccessor(const QString &nSuccessor)
{
    if (nSuccessor != m_successor) {
        m_successor = nSuccessor;
#ifdef QT_DEBUG
        qDebug() << "Changed successor to" << m_successor;
#endif
        emit successorChanged(successor());
    }
}




/*!
 * \property ExtendedItem::successorId
 * \brief Database ID of the successor.
 *
 * \par Access functions:
 * <TABLE><TR><TD>uint</TD><TD>successorId() const</TD></TR><TR><TD>void</TD><TD>setSuccessorId(uint nSuccessorId)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>successorIdChanged(uint successorId)</TD></TR></TABLE>
 */


uint ExtendedItem::successorId() const { return m_successorId; }

void ExtendedItem::setSuccessorId(uint nSuccessorId)
{
    if (nSuccessorId != m_successorId) {
        m_successorId = nSuccessorId;
#ifdef QT_DEBUG
        qDebug() << "Changed successorId to" << m_successorId;
#endif
        emit successorIdChanged(successorId());
    }
}




/*!
 * \property ExtendedItem::tpo
 * \brief Today part of this district.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>tpo() const</TD></TR><TR><TD>void</TD><TD>setTpo(const QString &nTpo)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>tpoChanged(const QString &tpo)</TD></TR></TABLE>
 */


QString ExtendedItem::tpo() const { return m_tpo; }

void ExtendedItem::setTpo(const QString &nTpo)
{
    if (nTpo != m_tpo) {
        m_tpo = nTpo;
#ifdef QT_DEBUG
        qDebug() << "Changed tpo to" << m_tpo;
#endif
        emit tpoChanged(tpo());
    }
}




/*!
 * \property ExtendedItem::tpoId
 * \brief Database ID of the district this district is today part of.
 *
 * \par Access functions:
 * <TABLE><TR><TD>uint</TD><TD>tpoId() const</TD></TR><TR><TD>void</TD><TD>setTpoId(uint nTpoId)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>tpoIdChanged(uint tpoId)</TD></TR></TABLE>
 */


uint ExtendedItem::tpoId() const { return m_tpoId; }

void ExtendedItem::setTpoId(uint nTpoId)
{
    if (nTpoId != m_tpoId) {
        m_tpoId = nTpoId;
#ifdef QT_DEBUG
        qDebug() << "Changed tpoId to" << m_tpoId;
#endif
        emit tpoIdChanged(tpoId());
    }
}


/*!
 * \property ExtendedItem::optionalSigns
 * \brief List of optional signs.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>optionalSigns() const</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>optionalSignsChanged(const QString &optionalSigns)</TD></TR></TABLE>
 */


QString ExtendedItem::optionalSigns() const { return m_optionalSigns; }

void ExtendedItem::setOptionalSigns(const QString &nOptionalSigns)
{
    if (nOptionalSigns != m_optionalSigns) {
        m_optionalSigns = nOptionalSigns;
#ifdef QT_DEBUG
        qDebug() << "Changed optionalSigns to" << m_optionalSigns;
#endif
        emit optionalSignsChanged(optionalSigns());
    }
}





void ExtendedItem::clear()
{
    Item::clear();
    if (m_antecessors) {
        m_antecessors->clear();
    }
    m_successor.clear();
    emit successorChanged(m_successor);
    m_successorId = 0;
    emit successorIdChanged(0);
    m_tpo.clear();
    emit tpoChanged(m_tpo);
    m_tpoId = 0;
    emit tpoIdChanged(0);
    m_optionalSigns.clear();
    emit optionalSignsChanged(m_optionalSigns);
}





void ExtendedItem::query()
{
    QSqlQuery q;
    if (!q.exec(QStringLiteral("SELECT sign, name, capital, type, state, assigned, successor, admin, closed, optional, wikipedia, coa FROM %1 WHERE id = %2").arg(countryCode()).arg(id()))) {
        qCritical("Failed to perform query: %s", qPrintable(q.lastError().text()));
        setInOperation(false);
        return;
    }

    if (q.next()) {
        setSign(q.value(0).toString());
        setName(q.value(1).toString());
        setCapital(q.value(2).toString());
        setType(QCoreApplication::translate("DBStrings", q.value(3).toString().toUtf8().constData()));
        setState(QCoreApplication::translate("DBStrings", q.value(4).toString().toUtf8().constData()));
        setFounded(q.value(5).toUInt());
        setSuccessorId(q.value(6).toUInt());
        setTpoId(q.value(7).toUInt());
        setDisbanded(q.value(8).toUInt());
        setOptional(q.value(9).toUInt());
        setWikipedia(q.value(10).toString());
        setCoa(q.value(11).toString());
    }

    if (successorId() > 0) {
        if (!q.exec(QStringLiteral("SELECT name, type, sign FROM %1 WHERE id = %2").arg(countryCode()).arg(successorId()))) {
            qWarning("Failed to perform query: %s", qPrintable(q.lastError().text()));
        } else if (q.next()) {
            //: 1 - the carplate sign, 2 - the district type, 3 - the district name
            setSuccessor(tr("%1 - %2 %3").arg(q.value(2).toString(), QCoreApplication::translate("DBStrings", q.value(1).toString().toUtf8().constData()), q.value(0).toString()));
        }
    }

    if ((tpoId() > 0) && (successorId() != tpoId())) {
        if (!q.exec(QStringLiteral("SELECT name, type, sign FROM %1 WHERE id = %2").arg(countryCode()).arg(tpoId()))) {
            qWarning("Failed to perform query: %s", qPrintable(q.lastError().text()));
        } else if (q.next()) {
            //: 1 - the carplate sign, 2 - the district type, 3 - the district name
            setTpo(tr("%1 - %2 %3").arg(q.value(2).toString(), QCoreApplication::translate("DBStrings", q.value(1).toString().toUtf8().constData()), q.value(0).toString()));
        }
    }

    if (disbanded() == 0) {
        QStringList optSigns;
        QList<int> subOptSignIds;
        QList<int> subSubOptSignIds;
        if (q.exec(QStringLiteral("SELECT id, sign FROM %1 WHERE successor = %2 AND optional > 0").arg(countryCode()).arg(id()))) {
            while (q.next()) {
                subOptSignIds << q.value(0).toInt();
                optSigns << q.value(1).toString();
            }

            for (int i = 0; i < subOptSignIds.size(); ++i)
            {
                if (q.exec(QStringLiteral("SELECT id, sign FROM %1 WHERE successor = %2 AND optional > 0").arg(countryCode()).arg(subOptSignIds.at(i)))) {
                    while (q.next()) {
                        subSubOptSignIds << q.value(0).toInt();
                        optSigns << q.value(1).toString();
                    }
                } else {
                    qWarning("Failed to perform query: %s", qPrintable(q.lastError().text()));
                }
            }

            for (int i = 0; i < subSubOptSignIds.size(); ++i)
            {
                if (q.exec(QStringLiteral("SELECT sign FROM %1 WHERE successor = %2 AND optional > 0").arg(countryCode()).arg(subSubOptSignIds.at(i)))) {
                    while (q.next()) {
                        optSigns << q.value(0).toString();
                    }
                } else {
                    qWarning("Failed to perform query: %s", qPrintable(q.lastError().text()));
                }
            }

            if (!optSigns.isEmpty()) {
                setOptionalSigns(optSigns.join(QStringLiteral(", ")));
            }

        } else {
            qWarning("Failed to perform query: %s", qPrintable(q.lastError().text()));
        }
    }

    if (q.exec(QStringLiteral("SELECT id AS itemId, name, type, sign FROM %1 WHERE successor = %2").arg(countryCode()).arg(id()))) {
        QList<SimpleItem*> l;
        while (q.next()) {
            l.append(new SimpleItem(q.value(0).toUInt(), q.value(1).toString(), QCoreApplication::translate("DBStrings", q.value(2).toString().toUtf8().constData()), q.value(3).toString()));
        }
        if (!l.isEmpty() && antecessors()) {
            antecessors()->addItems(l);
        }
    } else {
        qWarning("Failed to perform query: %s", qPrintable(q.lastError().text()));
    }
}
