#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QObject>
#include <QFile>
#include <QNetworkAccessManager>
#include <QSettings>
#include "globals.h"

class QNetworkReply;
class QProcess;

class DownloadManager : public QObject
{
    Q_OBJECT
public:
    explicit DownloadManager(QObject *parent = nullptr);

    Q_INVOKABLE void downloadDB();
    Q_INVOKABLE int getOnlineDBVersion();
    Q_INVOKABLE int getLocalDBVersion();

signals:
    void finishedDbDownload();
    void gotDBVersion(int oldVersion, int newVersion, const QString &changelog, const QString &cSize, const QString &uSize);
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
    QString m_dbCacheFileName;
    QString m_dbFileName;
    QSettings settings;
    int onlineDBVersion;
    QProcess *m_process;
    QString dbUrl;

};

#endif // DOWNLOADMANAGER_H
