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

#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QObject>
#include <QFile>
#include <QNetworkAccessManager>
#include "globals.h"

class QNetworkReply;
class QProcess;
class Configuration;
class DbManager;
class QTimer;

class DownloadManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(uint availableVersion READ availableVersion NOTIFY availableVersionChanged)
    Q_PROPERTY(QString changelog READ changelog NOTIFY changelogChanged)
    Q_PROPERTY(QString downloadSize READ downloadSize NOTIFY downloadSizeChanged)
    Q_PROPERTY(QString installedSize READ installedSize NOTIFY installedSizeChanged)
    Q_PROPERTY(bool inOperation READ inOperation NOTIFY inOperationChanged)
    Q_PROPERTY(Configuration *configuration READ configuration WRITE setConfiguration NOTIFY configurationChanged)
    Q_PROPERTY(DbManager *dbManager READ dbManager WRITE setDbManager NOTIFY dbManagerChanged)
    Q_PROPERTY(bool checkingVersion READ checkingVersion NOTIFY checkingVersionChanged)
public:
    explicit DownloadManager(QObject *parent = nullptr);

    Q_INVOKABLE void downloadDB();
    Q_INVOKABLE int getOnlineDBVersion();

    uint availableVersion() const;
    QString changelog() const;
    QString downloadSize() const;
    QString installedSize() const;
    bool inOperation() const;
    Configuration *configuration() const;
    DbManager *dbManager() const;
    bool checkingVersion() const;

    void setConfiguration(Configuration *nConfiguration);
    void setDbManager(DbManager *nDbManager);

signals:
    void finishedDbDownload();
    void failedDBVersion();
    void dbDownloadProgress(int rec, int tot);
    void dbDownloadFinished();
    void dbDownloadFailed();
    void dbDownloadStarted();
    void availableVersionChanged(uint availableVersion);
    void changelogChanged(const QString &changelog);
    void downloadSizeChanged(const QString &downloadSize);
    void installedSizeChanged(const QString &installedSize);
    void inOperationChanged(bool inOperation);
    void configurationChanged(Configuration *configuration);
    void dbManagerChanged(DbManager *dbManager);
    void checkingVersionChanged(bool checkingVersion);

private slots:
    void downloadDBProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadDBFinished();
    void downloadDBReadyRead();

private:
    Q_DISABLE_COPY(DownloadManager)
    uint m_availableVersion;
    QString m_changelog;
    QString m_downloadSize;
    QString m_installedSize;
    bool m_inOperation;
    Configuration *m_configuration;
    DbManager *m_dbManager;
    bool m_checkingVersion;

    QNetworkAccessManager manager;
    QNetworkReply *reply;
    QFile dbCacheFile;
    QString m_dbCacheFileName;
    QString m_dbFileName;
    QProcess *m_process;
    QString dbUrl;
    QTimer *m_timer;

    void setAvailableVersion(uint nAvailableVersion);
    void setChangelog(const QString &nChangelog);
    void setDownloadSize(const QString &nDownloadSize);
    void setInstalledSize(const QString &nInstalledSize);
    void setInOperation(bool nInOperation);
    void setCheckingVersion(bool nCheckingVersion);

};

#endif // DOWNLOADMANAGER_H
