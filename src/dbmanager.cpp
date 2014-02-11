#include "dbmanager.h"
#include "globals.h"

DbManager::DbManager(QObject *parent) :
    QObject(parent)
{
}


bool DbManager::openDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString path(DB_PATH);
    path = QDir::toNativeSeparators(path);

    db.setDatabaseName(path);
    db.setConnectOptions("QSQLITE_OPEN_READONLY");

    return db.open();
}


bool DbManager::closeDB()
{
    db.close();
    return true;
}
