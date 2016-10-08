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

DbManager::DbManager(QObject *parent) :
    QObject(parent)
{
}


bool DbManager::checkDB()
{
    QFile dbFile(QDir::homePath().append(QLatin1String(DATA_DIR)).append(QLatin1String("/carplates.sqlite")));
    if (dbFile.exists()) {
        return openDB();
    } else {
        return false;
    }
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
        db.close();
    }
    return true;
}
