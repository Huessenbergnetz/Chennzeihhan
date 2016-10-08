/*
    Chennzeihhan - Vehicle Registration Code Database for SailfishOS
    Copyright (C) 2014  Buschtrommel/Matthias Fehring

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
#ifdef QT_DEBUG
#include <QDebug>
#endif

DownloadManager::DownloadManager(QObject *parent) :
    QObject(parent), m_dbCacheFileName(QDir::homePath()), m_dbFileName(QDir::homePath()), m_process(new QProcess(this))
{
    m_dbCacheFileName.append(QLatin1String(DATA_DIR)).append(QLatin1String("/carplates.sqlite.gz"));
    m_dbFileName.append(QLatin1String(DATA_DIR)).append(QLatin1String("/carplates.sqlite"));
}


void DownloadManager::downloadDB()
{
    emit dbDownloadStarted();

    dbCacheFile.setFileName(m_dbCacheFileName);

    if (dbCacheFile.exists()) {
        dbCacheFile.remove();
    }

    if (!dbCacheFile.open(QIODevice::WriteOnly))
    {
        qCritical("Can not open cache file.");
        emit dbDownloadFailed();
        return;
    }

    onlineDBVersion = getOnlineDBVersion();
    QUrl url(dbUrl);

    if (onlineDBVersion > 0) {
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
            qCritical("Failed to remove current DB file.");
            return;
        }
    }

#ifdef QT_DEBUG
    qDebug() << "Decompressing downloaded DB.";
#endif

    m_process->start(QStringLiteral("gzip"), QStringList({QStringLiteral("-d"), m_dbCacheFileName}));

#ifdef QT_DEBUG
    qDebug() << m_process->program() << args;
#endif

    if (m_process->exitCode() != 0) {
        emit dbDownloadFailed();
        qCritical("Failed to decompress DB.");
        settings.setValue(QStringLiteral("database/version"), 0);
        return;
    }

    settings.setValue(QStringLiteral("database/version"), onlineDBVersion);

    emit dbDownloadFinished();

}


void DownloadManager::downloadDBReadyRead()
{
    dbCacheFile.write(reply->readAll());
}

int DownloadManager::getOnlineDBVersion()
{
    int newVersion = 0;

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
        emit gotDBVersion(getLocalDBVersion(), newVersion, result.value(QStringLiteral("changelog")).toString(), result.value(QStringLiteral("cSize")).toString(), result.value(QStringLiteral("uSize")).toString());
    }
    reply->deleteLater();

    return newVersion;
}



int DownloadManager::getLocalDBVersion()
{
    return settings.value(QStringLiteral("database/version"), 0).toInt();
}
