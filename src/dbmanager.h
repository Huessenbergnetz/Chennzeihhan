#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QtSql>
#include <QFile>

class DbManager : public QObject
{
    Q_OBJECT
public:
    explicit DbManager(QObject *parent = 0);
    Q_INVOKABLE bool checkDB();

signals:

public slots:
    bool openDB();
    bool closeDB();

private:
    QSqlDatabase db;

};

#endif // DBMANAGER_H
