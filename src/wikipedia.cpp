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

#include "wikipedia.h"
#include <QDebug>

Wikipedia::Wikipedia(QObject *parent) :
    QObject(parent)
{
}


QString Wikipedia::getTranslation(const QString &langCode, const QString &entry)
{
    QString lang = QLocale::system().name().left(2);

    QString wpURL;

    if (lang == langCode) {
        wpURL = "http://" + langCode + ".wikipedia.org/wiki/" + entry;
    } else {

        QString enFallback;

        QMap<QString, QString> interWiki = reqTranslations(langCode, entry);
        if (interWiki.contains("en"))
            enFallback = interWiki.value("en");

        while (!interWiki.contains(lang) && interWiki["cont"] != "") {

            interWiki = reqTranslations(langCode, entry, interWiki["cont"]);

            if (interWiki.contains("en"))
                enFallback = interWiki.value("en");
        }

        if (interWiki.contains(lang)) {
            wpURL = "http://" + lang + ".wikipedia.org/wiki/" + interWiki[lang];
        } else if (!enFallback.isEmpty()) {
            wpURL = "http://en.wikipedia.org/wiki/" + enFallback;
        } else {
            wpURL = "http://" + langCode + ".wikipedia.org/wiki/" + entry;
        }

        qDebug() << "Wikipedia URL: " << wpURL;
    }

    return wpURL;
}




QMap<QString, QString> Wikipedia::reqTranslations(const QString &langCode, const QString &entry, const QString &cont)
{
    QMap<QString, QString> result;

    QString query = "http://" + langCode + ".wikipedia.org/w/api.php?action=query&titles=" + entry + "&prop=langlinks&format=xml";

    if (!cont.isEmpty())
        query.append("&llcontinue=").append(cont);

    QUrl url(query);

    QNetworkRequest request(url);
    reply = manager.get(request);

    QEventLoop dlLoop;
    connect(reply, SIGNAL(finished()), &dlLoop, SLOT(quit()));
    dlLoop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        QDomDocument wpResult;
        wpResult.setContent(reply->readAll());

        QDomNodeList lls = wpResult.elementsByTagName("ll");

        for (int i = 0; i < lls.length(); ++i) {
            result[lls.item(i).toElement().attribute("lang")] = lls.item(i).toElement().text();
        }

        QDomNodeList cont = wpResult.elementsByTagName("query-continue");

        if (!cont.isEmpty()) {
            result["cont"] = cont.item(0).firstChildElement().attribute("llcontinue");
        } else {
            result["cont"] = "";
        }
    }
    reply->deleteLater();

    return result;
}
