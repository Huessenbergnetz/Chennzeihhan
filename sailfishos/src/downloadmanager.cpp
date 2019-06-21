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

#include "downloadmanager.h"
#include <QNetworkReply>
#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>
#include <QDir>
#include <QUrl>
#include <QNetworkRequest>
#include <QTimer>
#include "dbmanager.h"
#include "configuration.h"
#ifdef QT_DEBUG
#include <QDebug>
#endif

DownloadManager::DownloadManager(QObject *parent) :
    QObject(parent), m_dbCacheFileName(QDir::homePath()), m_dbFileName(QDir::homePath()), m_process(new QProcess(this)), m_timer(new QTimer(this))
{
    m_dbCacheFileName.append(QLatin1String(DATA_DIR)).append(QLatin1String("/carplates.sqlite.gz"));
    m_dbFileName.append(QLatin1String(DATA_DIR)).append(QLatin1String("/carplates.sqlite"));
    m_availableVersion = 0;
    m_inOperation = false;
    m_configuration = nullptr;
    m_dbManager = nullptr;
    m_checkingVersion = false;
    m_timer->setTimerType(Qt::PreciseTimer);
    m_timer->setSingleShot(true);
    m_timer->setInterval(500);
}


void DownloadManager::downloadDB()
{
    setInOperation(true);

    if (dbManager()) {
        dbManager()->closeDB();
    }

    dbCacheFile.setFileName(m_dbCacheFileName);

    if (dbCacheFile.exists()) {
        dbCacheFile.remove();
    }

    if (!dbCacheFile.open(QIODevice::WriteOnly))
    {
        qCritical("Can not open cache file.");
        emit dbDownloadFailed();
        setInOperation(false);
        return;
    }

    QUrl url(dbUrl);

    if (availableVersion() > 0) {
#ifdef QT_DEBUG
        qDebug() << "Start downloading database";
#endif
        QNetworkRequest request(url);
        reply = manager.get(request);
        connect(reply, &QNetworkReply::downloadProgress, this, &DownloadManager::downloadDBProgress);
        connect(reply, &QNetworkReply::finished, this, &DownloadManager::downloadDBFinished);
        connect(reply, &QNetworkReply::readyRead, this, &DownloadManager::downloadDBReadyRead);
    } else {
        qCritical("Can not retrieve DB info file.");
        setInOperation(false);
        emit dbDownloadFailed();
    }

}


void DownloadManager::downloadDBProgress(qint64 bytesReceived, qint64 bytesTotal)
{
#ifdef QT_DEBUG
    qDebug() << "Downloadprogress: " << bytesReceived << "/" << bytesTotal;
#endif
    emit dbDownloadProgress((int)bytesReceived, (int)bytesTotal);
}


void DownloadManager::downloadDBFinished()
{
#ifdef QT_DEBUG
    qDebug() << "Finished downloading DB.";
#endif

    dbCacheFile.close();
    reply->deleteLater();

    QFile dbFile;
    dbFile.setFileName(m_dbFileName);
    if (dbFile.exists())
    {
#ifdef QT_DEBUG
        qDebug() << "Removing existing DB file.";
#endif
        if (!dbFile.remove())
        {
            emit dbDownloadFailed();
            setInOperation(false);
            qCritical("Failed to remove current DB file.");
            return;
        }
    }

#ifdef QT_DEBUG
    qDebug() << "Decompressing downloaded DB.";
#endif

    m_process->start(QStringLiteral("gzip"), QStringList({QStringLiteral("-d"), m_dbCacheFileName}));

#ifdef QT_DEBUG
    qDebug() << m_process->program() << m_process->arguments();
#endif

    if (m_process->exitCode() != 0) {
        emit dbDownloadFailed();
        qCritical("Failed to decompress DB.");
        if (configuration()) {
            configuration()->setDatabaseVersion(0);
        }
        setInOperation(false);
        return;
    }

    if (configuration()) {
        configuration()->setDatabaseVersion(availableVersion());
    }

    QEventLoop loop;



    if (dbManager()) {
        connect(m_timer, &QTimer::timeout, dbManager(), &DbManager::checkDB);
        m_timer->start();
    }

    emit dbDownloadFinished();

    setInOperation(false);
}


void DownloadManager::downloadDBReadyRead()
{
    dbCacheFile.write(reply->readAll());
}

int DownloadManager::getOnlineDBVersion()
{
    setCheckingVersion(true);

    uint newVersion = 0;

    QNetworkRequest request(QUrl(QStringLiteral("https://www.buschmann23.de/chennzeihhan-data/database.json")));
    reply = manager.get(request);

    QEventLoop dlLoop;
    connect(reply, &QNetworkReply::finished, &dlLoop, &QEventLoop::quit);
    dlLoop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        QJsonObject result = QJsonDocument::fromJson(reply->readAll()).object();

#ifdef QT_DEBUG
        qDebug() << "JSON-Result: " << result;
#endif

        newVersion = result.value(QStringLiteral("version")).toInt();
        dbUrl = result.value(QStringLiteral("url")).toString();
        setAvailableVersion(newVersion);
        setChangelog(result.value(QStringLiteral("changelog")).toString());
        setDownloadSize(result.value(QStringLiteral("cSize")).toString());
        setInstalledSize(result.value(QStringLiteral("uSize")).toString());
    }
    reply->deleteLater();

    setCheckingVersion(false);

    return newVersion;
}



/*!
 * \property DownloadManager::availableVersion
 * \brief The online available database version.
 *
 * \par Access functions:
 * <TABLE><TR><TD>uint</TD><TD>availableVersion() const</TD></TR><TR><TD>void</TD><TD>setAvailableVersion(uint nAvailableVersion)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>availableVersionChanged(uint availableVersion)</TD></TR></TABLE>
 */


uint DownloadManager::availableVersion() const { return m_availableVersion; }

void DownloadManager::setAvailableVersion(uint nAvailableVersion)
{
    if (nAvailableVersion != m_availableVersion) {
        m_availableVersion = nAvailableVersion;
#ifdef QT_DEBUG
        qDebug() << "Changed availableVersion to" << m_availableVersion;
#endif
        emit availableVersionChanged(availableVersion());
    }
}




/*!
 * \property DownloadManager::changelog
 * \brief The last changelog of the online available database version.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>changelog() const</TD></TR><TR><TD>void</TD><TD>setChangelog(const QString &nChangelog)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>changelogChanged(const QString &changelog)</TD></TR></TABLE>
 */


QString DownloadManager::changelog() const { return m_changelog; }

void DownloadManager::setChangelog(const QString &nChangelog)
{
    if (nChangelog != m_changelog) {
        m_changelog = nChangelog;
#ifdef QT_DEBUG
        qDebug() << "Changed changelog to" << m_changelog;
#endif
        emit changelogChanged(changelog());
    }
}




/*!
 * \property DownloadManager::downloadSize
 * \brief The download size.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>downloadSize() const</TD></TR><TR><TD>void</TD><TD>setDownloadSize(const QString &nDownloadSize)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>downloadSizeChanged(const QString &downloadSize)</TD></TR></TABLE>
 */


QString DownloadManager::downloadSize() const { return m_downloadSize; }

void DownloadManager::setDownloadSize(const QString &nDownloadSize)
{
    if (nDownloadSize != m_downloadSize) {
        m_downloadSize = nDownloadSize;
#ifdef QT_DEBUG
        qDebug() << "Changed downloadSize to" << m_downloadSize;
#endif
        emit downloadSizeChanged(downloadSize());
    }
}




/*!
 * \property DownloadManager::installedSize
 * \brief The installed size.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>installedSize() const</TD></TR><TR><TD>void</TD><TD>setInstalledSize(const QString &nInstalledSize)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>installedSizeChanged(const QString &installedSize)</TD></TR></TABLE>
 */


QString DownloadManager::installedSize() const { return m_installedSize; }

void DownloadManager::setInstalledSize(const QString &nInstalledSize)
{
    if (nInstalledSize != m_installedSize) {
        m_installedSize = nInstalledSize;
#ifdef QT_DEBUG
        qDebug() << "Changed installedSize to" << m_installedSize;
#endif
        emit installedSizeChanged(installedSize());
    }
}




/*!
 * \property DownloadManager::inOperation
 * \brief Returns true while some downloads are ongoing.
 *
 * \par Access functions:
 * <TABLE><TR><TD>bool</TD><TD>inOperation() const</TD></TR><TR><TD>void</TD><TD>setInOperation(bool nInOperation)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>inOperationChanged(bool inOperation)</TD></TR></TABLE>
 */


bool DownloadManager::inOperation() const { return m_inOperation; }

void DownloadManager::setInOperation(bool nInOperation)
{
    if (nInOperation != m_inOperation) {
        m_inOperation = nInOperation;
#ifdef QT_DEBUG
        qDebug() << "Changed inOperation to" << m_inOperation;
#endif
        emit inOperationChanged(inOperation());
    }
}




/*!
 * \property DownloadManager::configuration
 * \brief Pointer to a Configuration object.
 *
 * \par Access functions:
 * <TABLE><TR><TD>Configuration*</TD><TD>configuration() const</TD></TR><TR><TD>void</TD><TD>setConfiguration(Configuration *nConfiguration)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>configurationChanged(Configuration *configuration)</TD></TR></TABLE>
 */


Configuration *DownloadManager::configuration() const { return m_configuration; }

void DownloadManager::setConfiguration(Configuration *nConfiguration)
{
    if (nConfiguration != m_configuration) {
        m_configuration = nConfiguration;
#ifdef QT_DEBUG
        qDebug() << "Changed configuration to" << m_configuration;
#endif
        emit configurationChanged(configuration());
    }
}




/*!
 * \property DownloadManager::dbManager
 * \brief Pointer to a DbManager object.
 *
 * \par Access functions:
 * <TABLE><TR><TD>DbManager*</TD><TD>dbManager() const</TD></TR><TR><TD>void</TD><TD>setDbManager(DbManager *nDbManager)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>dbManagerChanged(DbManager *dbManager)</TD></TR></TABLE>
 */


DbManager *DownloadManager::dbManager() const { return m_dbManager; }

void DownloadManager::setDbManager(DbManager *nDbManager)
{
    if (nDbManager != m_dbManager) {
        m_dbManager = nDbManager;
#ifdef QT_DEBUG
        qDebug() << "Changed dbManager to" << m_dbManager;
#endif
        emit dbManagerChanged(dbManager());
    }
}




/*!
 * \property DownloadManager::checkingVersion
 * \brief Returns true while the available version gets checked.
 *
 * \par Access functions:
 * <TABLE><TR><TD>bool</TD><TD>checkingVersion() const</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>checkingVersionChanged(bool checkingVersion)</TD></TR></TABLE>
 */


bool DownloadManager::checkingVersion() const { return m_checkingVersion; }

void DownloadManager::setCheckingVersion(bool nCheckingVersion)
{
    if (nCheckingVersion != m_checkingVersion) {
        m_checkingVersion = nCheckingVersion;
#ifdef QT_DEBUG
        qDebug() << "Changed checkingVersion to" << m_checkingVersion;
#endif
        emit checkingVersionChanged(checkingVersion());
    }
}

