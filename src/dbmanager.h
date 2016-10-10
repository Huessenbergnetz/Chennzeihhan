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
