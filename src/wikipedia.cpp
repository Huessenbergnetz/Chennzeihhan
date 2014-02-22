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
