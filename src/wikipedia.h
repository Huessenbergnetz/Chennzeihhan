#ifndef WIKIPEDIA_H
#define WIKIPEDIA_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QLocale>
#include <QEventLoop>
#include <QDomDocument>
#include <QDomNodeList>

class Wikipedia : public QObject
{
    Q_OBJECT
public:
    explicit Wikipedia(QObject *parent = 0);

    Q_INVOKABLE QString getTranslation(const QString &langCode, const QString &entry);

signals:

public slots:

private:
    QMap<QString, QString> reqTranslations(const QString &langCode, const QString &entry, const QString &cont = "");
    QNetworkAccessManager manager;
    QNetworkReply *reply;

};

#endif // WIKIPEDIA_H
