#ifndef WIKIPEDIA_H
#define WIKIPEDIA_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>

class QNetworkReply;

class Wikipedia : public QObject
{
    Q_OBJECT
public:
    explicit Wikipedia(QObject *parent = nullptr);

    Q_INVOKABLE QUrl getTranslation(const QString &langCode, const QString &entry);

private:
    QMap<QString, QString> reqTranslations(const QString &langCode, const QString &entry, const QString &cont = QString());
    QNetworkAccessManager manager;
    QNetworkReply *reply;

};

#endif // WIKIPEDIA_H
