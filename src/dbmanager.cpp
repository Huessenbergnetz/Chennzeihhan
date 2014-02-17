#include "dbmanager.h"
#include "globals.h"
#include <QDebug>

DbManager::DbManager(QObject *parent) :
    QObject(parent)
{
}


bool DbManager::checkDB()
{
    bool ret;
    QFile dbFile(QDir::homePath().append(DATA_DIR).append("/carplates.sqlite"));
    if (dbFile.exists())
    {
        ret = openDB();
    } else {
        ret = false;
    }

    return ret;
}


bool DbManager::openDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(QDir::homePath().append(DATA_DIR).append("/carplates.sqlite"));
    db.setConnectOptions("QSQLITE_OPEN_READONLY");

    return db.open();
}


bool DbManager::closeDB()
{
    if (db.isOpen())
        db.close();
    return true;
}
