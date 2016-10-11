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

#include "alphabetmodel.h"
#include <QSqlQuery>
#include <QCoreApplication>
#include <QStringListModel>
#include "../dbmanager.h"
#ifdef QT_DEBUG
#include <QtDebug>
#endif

AlphabetModel::AlphabetModel(QObject *parent) : QAbstractListModel(parent)
{
    m_sorting = Chennzeihhan::Code;
    m_inOperation = false;
    m_dbManager = nullptr;
}



AlphabetModel::~AlphabetModel()
{
    qDeleteAll(m_alphabet);
    m_alphabet.clear();
}



int AlphabetModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_alphabet.count();
}


QHash<int, QByteArray> AlphabetModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(Row, QByteArrayLiteral("row"));
    return roles;
}


QModelIndex AlphabetModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    return createIndex(row, column);
}


QVariant AlphabetModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() > (rowCount() - 1)) {
        return QVariant();
    }

    if (role == Row) {
        return QVariant::fromValue(m_alphabet.at(index.row()));
//        return QVariant::fromValue(m_alphabet.at(index.row()));
    } else {
        return QVariant();
    }
}



/*!
 * \property AlphabetModel::sorting
 * \brief The sorting property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>Chennzeihhan::Target</TD><TD>sorting() const</TD></TR><TR><TD>void</TD><TD>setSorting(Chennzeihhan::Target nSorting)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>sortingChanged(Chennzeihhan::Target sorting)</TD></TR></TABLE>
 */


Chennzeihhan::Target AlphabetModel::sorting() const { return m_sorting; }

void AlphabetModel::setSorting(Chennzeihhan::Target nSorting)
{
    if (nSorting != m_sorting) {
        m_sorting = nSorting;
#ifdef QT_DEBUG
        qDebug() << "Changed sorting to" << m_sorting;
#endif
        emit sortingChanged(sorting());
    }
}




/*!
 * \property AlphabetModel::inOperation
 * \brief The inOperation property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>bool</TD><TD>inOperation() const</TD></TR><TR><TD>void</TD><TD>setInOperation(bool nInOperation)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>inOperationChanged(bool inOperation)</TD></TR></TABLE>
 */


bool AlphabetModel::inOperation() const { return m_inOperation; }

void AlphabetModel::setInOperation(bool nInOperation)
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
 * \property AlphabetModel::dbManager
 * \brief The dbManager property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>DbManager*</TD><TD>dbManager() const</TD></TR><TR><TD>void</TD><TD>setDbManager(DbManager *nDbManager)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>dbManagerChanged(DbManager *dbManager)</TD></TR></TABLE>
 */


DbManager *AlphabetModel::dbManager() const { return m_dbManager; }

void AlphabetModel::setDbManager(DbManager *nDbManager)
{
    if (nDbManager != m_dbManager) {

        if (m_dbManager) {
            disconnect(m_dbManager, &DbManager::dbExistsChanged, this, &AlphabetModel::dbChanged);
        }

        m_dbManager = nDbManager;

        if (m_dbManager) {
            connect(m_dbManager, &DbManager::dbExistsChanged, this, &AlphabetModel::dbChanged);
        }

#ifdef QT_DEBUG
        qDebug() << "Changed dbManager to" << m_dbManager;
#endif
        emit dbManagerChanged(dbManager());
    }
}




void AlphabetModel::init(Chennzeihhan::Target sorting)
{
    QSqlQuery q;

    setSorting(sorting);

    if (!m_alphabet.isEmpty()) {
        beginRemoveRows(QModelIndex(), 0, rowCount() - 1);

        qDeleteAll(m_alphabet);
        m_alphabet.clear();

        endRemoveRows();
    }

    if (dbManager() && dbManager()->dbExists()) {

        if (sorting == Chennzeihhan::Code) {
            q.exec(QStringLiteral("SELECT DISTINCT SUBSTR(sign, 1, 1) AS c FROM countries ORDER BY c ASC"));

            QList<QStringListModel*> _l;
            QStringList sl;

            while (q.next()) {

                if (sl.count() >= 5) {
                    QStringListModel *slm = new QStringListModel(this);
                    slm->setStringList(sl);
                    _l.append(slm);
                    sl.clear();
                    sl.append(q.value(0).toString());
                } else {
                    sl.append(q.value(0).toString());
                }
            }

            if (!sl.isEmpty()) {
                QStringListModel *slm = new QStringListModel(this);
                slm->setStringList(sl);
                _l.append(slm);
            }

            if (!_l.isEmpty()) {

                beginInsertRows(QModelIndex(), 0, _l.count() - 1);

                m_alphabet = _l;

                endInsertRows();
            }

        } else {
            q.exec(QStringLiteral("SELECT en FROM countries"));
            QStringList _l;

            while (q.next()) {
                _l.append(QCoreApplication::translate("DBStrings", q.value(0).toString().toUtf8().constData()).left(1));
            }

            if (!_l.isEmpty()) {

                _l.removeDuplicates();
                _l.sort();

                QList<QStringListModel*> _ll;
                QStringList sl;

                for (int i = 0; i < _l.count(); ++i) {
                    if (sl.count() >= 5) {
                        QStringListModel *slm = new QStringListModel(this);
                        slm->setStringList(sl);
                        _ll.append(slm);
                        sl.clear();
                        sl.append(_l.at(i));
                    } else {
                        sl.append(_l.at(i));
                    }
                }

                if (!sl.isEmpty()) {
                    QStringListModel *slm = new QStringListModel(this);
                    slm->setStringList(sl);
                    _ll.append(slm);
                }

                if (!_ll.isEmpty()) {

                    beginInsertRows(QModelIndex(), 0, _ll.count() - 1);

                    m_alphabet = _ll;

                    endInsertRows();
                }

            }

        }

    }
}


void AlphabetModel::dbChanged()
{
    init(sorting());
}
