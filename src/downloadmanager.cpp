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
#include <QDebug>

DownloadManager::DownloadManager(QObject *parent) :
    QObject(parent), m_process(new QProcess(this))
{
    dbCacheFileName = QDir::homePath();
    dbCacheFileName.append(DATA_DIR).append("/carplates.sqlite.gz");
    dbFileName = QDir::homePath();
    dbFileName.append(DATA_DIR).append("/carplates.sqlite");
}


void DownloadManager::downloadDB()
{
    emit dbDownloadStarted();

    dbCacheFile.setFileName(dbCacheFileName);

    if (dbCacheFile.exists())
        dbCacheFile.remove();

    if (!dbCacheFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Can not open cache file.";
        emit dbDownloadFailed();
        return;
    }

    onlineDBVersion = getOnlineDBVersion();
    QUrl url(dbUrl);

    if (onlineDBVersion > 0) {
        qDebug() << "Start downloading database";
        QNetworkRequest request(url);
        reply = manager.get(request);
        connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadDBProgress(qint64,qint64)));
        connect(reply, SIGNAL(finished()), this, SLOT(downloadDBFinished()));
        connect(reply, SIGNAL(readyRead()), this, SLOT(downloadDBReadyRead()));
    } else {
        qDebug() << "Can not retrieve DB info file.";
        emit dbDownloadFailed();
    }

}


void DownloadManager::downloadDBProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    qDebug() << "Downloadprogress: " << bytesReceived << "/" << bytesTotal;
    emit dbDownloadProgress((int)bytesReceived, (int)bytesTotal);
}


void DownloadManager::downloadDBFinished()
{
    qDebug() << "Finished downloading DB.";

    dbCacheFile.close();
    reply->deleteLater();

    QFile dbFile;
    dbFile.setFileName(dbFileName);
    if (dbFile.exists())
    {
        qDebug() << "Removing existing DB file.";
        if (!dbFile.remove())
        {
            emit dbDownloadFailed();
            qDebug() << "Failed to remove current DB file.";
            return;
        }
    }

    qDebug() << "Decompressing downloaded DB.";
    QStringList args;
    args << "-d" << dbCacheFileName;
    m_process->start("gzip", args);

    if (m_process->exitCode() != 0) {
        emit dbDownloadFailed();
        qDebug() << "Failed to decompress DB.";
        settings.setValue("database/version", 0);
        return;
    }

    settings.setValue("database/version", onlineDBVersion);

    emit dbDownloadFinished();

}


void DownloadManager::downloadDBReadyRead()
{
    dbCacheFile.write(reply->readAll());
}

int DownloadManager::getOnlineDBVersion()
{
    QUrl url("http://www.buschmann23.de/chennzeihhan-data/database.json");
    int newVersion = 0;
    int oldVersion = getLocalDBVersion();
    QString changelog = "";
    QString cSize = "";
    QString uSize = "";

    QNetworkRequest request(url);
    reply = manager.get(request);

    QEventLoop dlLoop;
    connect(reply, SIGNAL(finished()), &dlLoop, SLOT(quit()));
    dlLoop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        QVariantMap result;
        result = QJsonDocument::fromJson(reply->readAll()).object().toVariantMap();

        qDebug() << "JSON-Result: " << result;

        newVersion = result["version"].toInt();
        dbUrl = result["url"].toString();
        changelog = result["changelog"].toString();
        cSize = result["cSize"].toString();
        uSize = result["uSize"].toString();
        emit gotDBVersion(oldVersion, newVersion, changelog, cSize, uSize);
    }
    reply->deleteLater();

    return newVersion;
}



int DownloadManager::getLocalDBVersion()
{
    return settings.value("database/version", 0).toInt();
}
