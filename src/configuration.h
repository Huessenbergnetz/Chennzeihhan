#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>
#include <QSettings>
#include <QStringList>
#include "models/countrymodelfilter.h"

class Configuration : public QSettings
{
    Q_OBJECT
    Q_PROPERTY(CountryModelFilter::Target defaultSearchTarget READ defaultSearchTarget WRITE setDefaultSearchTarget NOTIFY defaultSearchTargetChanged)
    Q_PROPERTY(CountryModelFilter::Target defaultOrderTarget READ defaultOrderTarget WRITE setDefaultOrderTarget NOTIFY defaultOrderTargetChanged)
    Q_PROPERTY(QString displayLanguage READ displayLanguage WRITE setDisplayLanguage NOTIFY displayLanguageChanged)
    Q_PROPERTY(uint databaseVersion READ databaseVersion WRITE setDatabaseVersion NOTIFY databaseVersionChanged)
    Q_ENUMS(CountryModelFilter::Target)
public:
    explicit Configuration(QObject *parent = nullptr);

//    enum Target {
//        Code = 0,
//        Name = 1,
//        Both = 2
//    };
//    Q_ENUMS(Target)

    Q_INVOKABLE void setFav(const QString &sign);
    Q_INVOKABLE QStringList getFavs();
    Q_INVOKABLE void removeFav(const QString &sign);
    Q_INVOKABLE bool isFav(const QString &sign);
    Q_INVOKABLE QVariant get(const QString &key, const QString &def);
    Q_INVOKABLE void set(const QString &key, const QString &val);

    CountryModelFilter::Target defaultSearchTarget() const;
    CountryModelFilter::Target defaultOrderTarget() const;
    QString displayLanguage() const;
    uint databaseVersion() const;

    void setDefaultSearchTarget(CountryModelFilter::Target nDefaultSearchTarget);
    void setDefaultOrderTarget(CountryModelFilter::Target nDefaultOrderTarget);
    void setDisplayLanguage(const QString &nDisplayLanguage);
    void setDatabaseVersion(uint nDatabaseVersion);

signals:
    void favsChanged();
    void configChanged();
    void defaultSearchTargetChanged(CountryModelFilter::Target defaultSearchTarget);
    void defaultOrderTargetChanged(CountryModelFilter::Target defaultOrderTarget);
    void displayLanguageChanged(const QString &displayLanguage);
    void databaseVersionChanged(uint databaseVersion);

private:
    Q_DISABLE_COPY(Configuration)
    CountryModelFilter::Target m_defaultSearchTarget;
    CountryModelFilter::Target m_defaultOrderTarget;
    QString m_displayLanguage;
    uint m_databaseVersion;
};
//Q_DECLARE_METATYPE(Configuration::Target)

#endif // CONFIGURATION_H
