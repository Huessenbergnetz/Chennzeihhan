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

#include "wikipedia.h"
#include <QNetworkReply>
#include <QLocale>
#include <QEventLoop>
#include <QDomDocument>
#include <QDomNodeList>
#include <QUrlQuery>
#include <QSettings>
#ifdef QT_DEBUG
#include <QDebug>
#endif

Wikipedia::Wikipedia(QObject *parent) :
    QObject(parent)
{
}


/*!
 * \property Wikipedia::langCode
 * \brief The language code.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>langCode() const</TD></TR><TR><TD>void</TD><TD>setLangCode(const QString &nLangCode)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>langCodeChanged(const QString &langCode)</TD></TR></TABLE>
 */


QString Wikipedia::langCode() const { return m_langCode; }

void Wikipedia::setLangCode(const QString &nLangCode)
{
    if (nLangCode != m_langCode) {
        m_langCode = nLangCode;
#ifdef QT_DEBUG
        qDebug() << "Changed langCode to" << m_langCode;
#endif
        emit langCodeChanged(langCode());
        getTranslation();
    }
}




/*!
 * \property Wikipedia::entry
 * \brief The entry name.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>entry() const</TD></TR><TR><TD>void</TD><TD>setEntry(const QString &nEntry)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>entryChanged(const QString &entry)</TD></TR></TABLE>
 */


QString Wikipedia::entry() const { return m_entry; }

void Wikipedia::setEntry(const QString &nEntry)
{
    if (nEntry != m_entry) {
        m_entry = nEntry;
#ifdef QT_DEBUG
        qDebug() << "Changed entry to" << m_entry;
#endif
        emit entryChanged(entry());
        getTranslation();
    }
}




/*!
 * \property Wikipedia::url
 * \brief The requested url.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QUrl</TD><TD>url() const</TD></TR><TR><TD>void</TD><TD>setUrl(const QUrl &nUrl)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>urlChanged(const QUrl &url)</TD></TR></TABLE>
 */


QUrl Wikipedia::url() const { return m_url; }

void Wikipedia::setUrl(const QUrl &nUrl)
{
    if (nUrl != m_url) {
        m_url = nUrl;
#ifdef QT_DEBUG
        qDebug() << "Changed url to" << m_url;
#endif
        emit urlChanged(url());
    }
}




void Wikipedia::getTranslation()
{
    if (langCode().isEmpty() || entry().isEmpty()) {
        return;
    }

    QSettings s;
    QString lang = s.value(QStringLiteral("display/language")).toString().left(2).toUpper();
    if (lang.isEmpty() || (lang == QLatin1String("C"))) {
        lang = QLocale::system().name().left(2);
    }

    QUrl wpURL;
    wpURL.setScheme(QStringLiteral("https"));


    if (lang == langCode()) {
        wpURL.setHost(QStringLiteral("%1.wikipedia.org").arg(langCode()));
        wpURL.setPath(QStringLiteral("/wiki/%1").arg(entry()));
    } else {

        QString enFallback;

        QMap<QString, QString> interWiki = reqTranslations(langCode(), entry());
        if (interWiki.contains(QStringLiteral("en"))) {
            enFallback = interWiki.value(QStringLiteral("en"));
        }

        while (!interWiki.contains(lang) && (interWiki[QStringLiteral("cont")] != QStringLiteral(""))) {

            interWiki = reqTranslations(langCode(), entry(), interWiki[QStringLiteral("cont")]);

            if (interWiki.contains(QStringLiteral("en"))) {
                enFallback = interWiki.value(QStringLiteral("en"));
            }
        }

        if (interWiki.contains(lang)) {
            wpURL.setHost(QStringLiteral("%1.wikipedia.org").arg(lang));
            wpURL.setPath(QStringLiteral("/wiki/%1").arg(interWiki[lang]));
        } else if (!enFallback.isEmpty()) {
            wpURL.setHost(QStringLiteral("en.wikipedia.org"));
            wpURL.setPath(QStringLiteral("/wiki/%1").arg(enFallback));
        } else {
            wpURL.setHost(QStringLiteral("%1.wikipedia.org").arg(langCode()));
            wpURL.setPath(QStringLiteral("/wiki/%1").arg(entry()));
        }

#ifdef QT_DEBUG
        qDebug() << "Wikipedia URL: " << wpURL;
#endif

    }

    setUrl(wpURL);
}




QMap<QString, QString> Wikipedia::reqTranslations(const QString &langCode, const QString &entry, const QString &cont)
{
    QMap<QString, QString> result;

    QUrlQuery uq;
    uq.addQueryItem(QStringLiteral("action"), QStringLiteral("query"));
    uq.addQueryItem(QStringLiteral("titles"), entry);
    uq.addQueryItem(QStringLiteral("prop"), QStringLiteral("langlinks"));
    uq.addQueryItem(QStringLiteral("format"), QStringLiteral("xml"));
    if (!cont.isEmpty()) {
        uq.addQueryItem(QStringLiteral("llcontinue"), cont);
    }

    QUrl url;
    url.setScheme(QStringLiteral("https"));
    url.setHost(QStringLiteral("%1.wikipedia.org").arg(langCode));
    url.setPath(QStringLiteral("/w/api.php"));
    url.setQuery(uq);


    QNetworkRequest request(url);
    reply = manager.get(request);

    QEventLoop dlLoop;
    connect(reply, &QNetworkReply::finished, &dlLoop, &QEventLoop::quit);
    dlLoop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        QDomDocument wpResult;
        wpResult.setContent(reply->readAll());

        QDomNodeList lls = wpResult.elementsByTagName(QStringLiteral("ll"));

        for (int i = 0; i < lls.length(); ++i) {
            result[lls.item(i).toElement().attribute(QStringLiteral("lang"))] = lls.item(i).toElement().text();
        }

        QDomNodeList cont = wpResult.elementsByTagName(QStringLiteral("query-continue"));

        if (!cont.isEmpty()) {
            result[QStringLiteral("cont")] = cont.item(0).firstChildElement().attribute(QStringLiteral("llcontinue"));
        } else {
            result[QStringLiteral("cont")] = QStringLiteral("");
        }
    }
    reply->deleteLater();

    return result;
}
