/*
    Chennzeihhan - Vehicle Registration Code Database for SailfishOS
    Copyright (C) 2014-2019 Hüssenbergnetz/Matthias Fehring

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
