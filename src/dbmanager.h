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

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>

class DbManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool dbExists READ dbExists NOTIFY dbExistsChanged)
public:
    explicit DbManager(QObject *parent = nullptr);

    bool dbExists() const;

    void setDbExists(bool nDbExists);

public slots:
    bool checkDB();
    bool openDB();
    bool closeDB();

signals:
    void dbExistsChanged(bool dbExists);

private:
    Q_DISABLE_COPY(DbManager)
    bool m_dbExists;
    QSqlDatabase db;

};

#endif // DBMANAGER_H
