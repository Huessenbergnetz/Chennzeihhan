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

#include "countrymodel.h"
#include <QCoreApplication>
#include <QSqlQuery>
#ifdef QT_DEBUG
#include <QtDebug>
#endif


CountryModel::CountryModel(QObject *parent) :
    SimpleItemModel(parent)
{
}



QString CountryModel::countryCode() const { return m_countryCode; }

void CountryModel::setCountryCode(const QString &nCountryCode)
{
    if (nCountryCode != m_countryCode) {
        m_countryCode = nCountryCode;
#ifdef QT_DEBUG
        qDebug() << "Changed countryCode to" << m_countryCode;
#endif
        init();
    }
}




bool CountryModel::inOperation() const { return m_inOperation; }

void CountryModel::setInOperation(bool nInOperation)
{
    if (nInOperation != m_inOperation) {
        m_inOperation = nInOperation;
#ifdef QT_DEBUG
        qDebug() << "Changed inOperation to" << m_inOperation;
#endif
        emit inOperationChanged(inOperation());
    }
}



void CountryModel::init()
{
    setInOperation(true);

    clear();

    if (countryCode().isEmpty()) {
        setInOperation(false);
        return;
    }

    QSqlQuery q;
    if (!q.exec(QStringLiteral("SELECT id AS itemId, name, type, sign, state, closed FROM %1").arg(countryCode()))) {
        setInOperation(false);
        return;
    } else {

        QList<SimpleItem*> _l;

        while (q.next()) {

            _l.append(new SimpleItem(q.value(0).toUInt(), q.value(1).toString(), QCoreApplication::translate("DBStrings", q.value(2).toString().toUtf8().constData()), q.value(3).toString(), QCoreApplication::translate("DBStrings", q.value(4).toString().toUtf8().constData()), q.value(5).toBool()));

        }

        addItems(_l);

    }

    setInOperation(false);
}

