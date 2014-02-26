#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>
#include <QSettings>
#include <QStringList>

class Configuration : public QSettings
{
    Q_OBJECT
public:
    explicit Configuration(QObject *parent = 0);
    Q_INVOKABLE void setFav(const QString &sign);
    Q_INVOKABLE QStringList getFavs();
    Q_INVOKABLE void removeFav(const QString &sign);
    Q_INVOKABLE bool isFav(const QString &sign);

signals:
    void favsChanged();

public slots:

private:

};

#endif // CONFIGURATION_H
