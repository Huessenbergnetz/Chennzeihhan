#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>
#include <QProcess>
#include "globals.h"

class DownloadManager : public QObject
{
    Q_OBJECT
public:
    explicit DownloadManager(QObject *parent = 0);

    Q_INVOKABLE void downloadDB();
    Q_INVOKABLE int getOnlineDBVersion();
    Q_INVOKABLE int getLocalDBVersion();

signals:
    void finishedDbDownload();
    void gotDBVersion(int oldVersion, int newVersion, QString changelog, QString cSize, QString uSize);
    void failedDBVersion();
    void dbDownloadProgress(int rec, int tot);
    void dbDownloadFinished();
    void dbDownloadFailed();
    void dbDownloadStarted();

public slots:

private slots:
    void downloadDBProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadDBFinished();
    void downloadDBReadyRead();

private:
    QNetworkAccessManager manager;
    QNetworkReply *reply;
    QFile dbCacheFile;
    QString dbCacheFileName;
    QString dbFileName;
    QSettings settings;
    int onlineDBVersion;
    QProcess *m_process;
    QString dbUrl;

};

#endif // DOWNLOADMANAGER_H
