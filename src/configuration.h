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
    Q_INVOKABLE QVariant get(const QString &key, const QString &def);
    Q_INVOKABLE void set(const QString &key, const QString &val);

signals:
    void favsChanged();
    void configChanged();

public slots:

private:

};

#endif // CONFIGURATION_H
