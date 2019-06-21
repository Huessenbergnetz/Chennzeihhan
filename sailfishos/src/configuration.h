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

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>
#include <QSettings>
#include <QStringList>
#include "globals.h"

class Configuration : public QSettings
{
    Q_OBJECT
    Q_PROPERTY(Chennzeihhan::Target defaultSearchTarget READ defaultSearchTarget WRITE setDefaultSearchTarget NOTIFY defaultSearchTargetChanged)
    Q_PROPERTY(Chennzeihhan::Target defaultOrderTarget READ defaultOrderTarget WRITE setDefaultOrderTarget NOTIFY defaultOrderTargetChanged)
    Q_PROPERTY(QString displayLanguage READ displayLanguage WRITE setDisplayLanguage NOTIFY displayLanguageChanged)
    Q_PROPERTY(uint databaseVersion READ databaseVersion NOTIFY databaseVersionChanged)
    Q_PROPERTY(uint minimumDbVersion READ minimumDbVersion CONSTANT)
    Q_ENUMS(Chennzeihhan::Target)
public:
    explicit Configuration(QObject *parent = nullptr);

    Q_INVOKABLE void setFav(const QString &sign);
    Q_INVOKABLE QStringList getFavs();
    Q_INVOKABLE void removeFav(const QString &sign);
    Q_INVOKABLE bool isFav(const QString &sign);
    Q_INVOKABLE QVariant get(const QString &key, const QString &def);
    Q_INVOKABLE void set(const QString &key, const QString &val);

    Chennzeihhan::Target defaultSearchTarget() const;
    Chennzeihhan::Target defaultOrderTarget() const;
    QString displayLanguage() const;
    uint databaseVersion() const;
    uint minimumDbVersion() const;

    void setDefaultSearchTarget(Chennzeihhan::Target nDefaultSearchTarget);
    void setDefaultOrderTarget(Chennzeihhan::Target nDefaultOrderTarget);
    void setDisplayLanguage(const QString &nDisplayLanguage);
    void setDatabaseVersion(uint nDatabaseVersion);

signals:
    void favsChanged();
    void configChanged();
    void defaultSearchTargetChanged(Chennzeihhan::Target defaultSearchTarget);
    void defaultOrderTargetChanged(Chennzeihhan::Target defaultOrderTarget);
    void displayLanguageChanged(const QString &displayLanguage);
    void databaseVersionChanged(uint databaseVersion);

private:
    Q_DISABLE_COPY(Configuration)
    Chennzeihhan::Target m_defaultSearchTarget;
    Chennzeihhan::Target m_defaultOrderTarget;
    QString m_displayLanguage;
    uint m_databaseVersion;
};

#endif // CONFIGURATION_H
