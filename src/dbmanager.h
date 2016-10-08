#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>

class DbManager : public QObject
{
    Q_OBJECT
public:
    explicit DbManager(QObject *parent = nullptr);
    Q_INVOKABLE bool checkDB();

public slots:
    bool openDB();
    bool closeDB();

private:
    QSqlDatabase db;

};

#endif // DBMANAGER_H
