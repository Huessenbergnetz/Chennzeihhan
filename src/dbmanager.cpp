/*
    Chennzeihhan - Vehicle Registration Code Database for SailfishOS
    Copyright (C) 2014  Buschtrommel/Matthias Fehring

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

#include "dbmanager.h"
#include "globals.h"
#include <QFile>
#include <QDir>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

DbManager::DbManager(QObject *parent) :
    QObject(parent)
{
}


bool DbManager::checkDB()
{
    bool exists;
    QFile dbFile(QDir::homePath().append(QLatin1String(DATA_DIR)).append(QLatin1String("/carplates.sqlite")));
    if (dbFile.exists()) {
        exists = openDB();
    } else {
        exists = false;
    }

    setDbExists(exists);

    return exists;
}


bool DbManager::openDB()
{
    db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"));

    db.setDatabaseName(QDir::homePath().append(QLatin1String(DATA_DIR)).append(QLatin1String("/carplates.sqlite")));
    db.setConnectOptions(QStringLiteral("QSQLITE_OPEN_READONLY"));

    bool dbStatus = db.open();

    if (dbStatus) {
        tables = db.tables(QSql::Tables);
    }

    return dbStatus;
}


bool DbManager::closeDB()
{
    if (db.isOpen()) {
        setDbExists(false);
        db.close();
    }
    return true;
}


/*!
 * \property DbManager::dbExists
 * \brief Returns true if the database file exists and the database is open.
 *
 * \par Access functions:
 * <TABLE><TR><TD>bool</TD><TD>dbExists() const</TD></TR><TR><TD>void</TD><TD>setDbExists(bool nDbExists)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>dbExistsChanged(bool dbExists)</TD></TR></TABLE>
 */


bool DbManager::dbExists() const { return m_dbExists; }

void DbManager::setDbExists(bool nDbExists)
{
    if (nDbExists != m_dbExists) {
        m_dbExists = nDbExists;
#ifdef QT_DEBUG
        qDebug() << "Changed dbExists to" << m_dbExists;
#endif
        emit dbExistsChanged(dbExists());
    }
}
