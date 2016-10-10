#ifndef WIKIPEDIA_H
#define WIKIPEDIA_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>

class QNetworkReply;

class Wikipedia : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString langCode READ langCode WRITE setLangCode NOTIFY langCodeChanged)
    Q_PROPERTY(QString entry READ entry WRITE setEntry NOTIFY entryChanged)
    Q_PROPERTY(QUrl url READ url NOTIFY urlChanged)
public:
    explicit Wikipedia(QObject *parent = nullptr);

    QString langCode() const;
    QString entry() const;
    QUrl url() const;

    void setLangCode(const QString &nLangCode);
    void setEntry(const QString &nEntry);

signals:
    void langCodeChanged(const QString &langCode);
    void entryChanged(const QString &entry);
    void urlChanged(const QUrl &url);

private:
    Q_DISABLE_COPY(Wikipedia)
    QString m_langCode;
    QString m_entry;
    QUrl m_url;
    void getTranslation();
    QMap<QString, QString> reqTranslations(const QString &langCode, const QString &entry, const QString &cont = QString());
    QNetworkAccessManager manager;
    QNetworkReply *reply;
    void setUrl(const QUrl &nUrl);

};

#endif // WIKIPEDIA_H
