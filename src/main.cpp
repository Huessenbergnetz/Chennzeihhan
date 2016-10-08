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

#include <QtQml>
#include <QGuiApplication>
#include <QQuickView>
#include <QLocale>
#include <QTranslator>
#include <QDir>
#include <QSettings>
#include <QDebug>

#ifndef CLAZY
#include <sailfishapp.h>
#endif
#include "globals.h"
#include "dbmanager.h"
#include "downloadmanager.h"
#include "wikipedia.h"
#include "configuration.h"
#include "models/countrymodel.h"
#include "models/antecessormodel.h"
#include "models/itemmodel.h"
#include "models/countriesmodel.h"
#include "models/languagemodelfilter.h"


int main(int argc, char *argv[])
{
#ifndef CLAZY
    QGuiApplication* app = SailfishApp::application(argc, argv);
#else
    QGuiApplication* app = new QGuiApplication(argc, argv);
#endif

    app->setOrganizationName(QStringLiteral("harbour-chennzeihhan"));
    app->setOrganizationDomain(QStringLiteral("buschmann23.de"));
    app->setApplicationName(QStringLiteral("harbour-chennzeihhan"));
    app->setApplicationVersion(QStringLiteral(VERSION_STRING));

    QDir().mkpath(QDir::homePath().append(DATA_DIR));

    DbManager dbman;
    dbman.checkDB();

    DownloadManager dlManager;
    Wikipedia wikipedia;

    Configuration *config = new Configuration;

    QString locale = config->get(QStringLiteral("display/language"), QStringLiteral("C")).toString();

    if (locale == QLatin1String("C")) {
        locale = QLocale::system().name();
    }

#ifndef CLAZY
    QTranslator *translator = new QTranslator;
    if (translator->load("chennzeihhan_"+locale, SailfishApp::pathTo(QStringLiteral("translations")).toString(QUrl::RemoveScheme))) {
        app->installTranslator(translator);
    }
#endif


    QObject::connect(&dlManager, SIGNAL(dbDownloadStarted()), &dbman, SLOT(closeDB()));

    CountriesModel *countriesModel = new CountriesModel();
    CountriesModel *countriesSearch = new CountriesModel();
    CountriesModel *countriesFavourites = new CountriesModel();
    CountriesModel *abcModel = new CountriesModel();
    CountryModel *countryModel = new CountryModel();
    ItemModel *itemModel = new ItemModel();
    LanguageModelFilter *languageModel = new LanguageModelFilter;

    AntecessorModel *antecessorModel = new AntecessorModel();

#ifndef CLAZY
    QQuickView* view = SailfishApp::createView();
#else
    QQuickView* view = new QQuickView;
#endif

    view->rootContext()->setContextProperty(QStringLiteral("dbMan"), &dbman);
    view->rootContext()->setContextProperty(QStringLiteral("dlMan"), &dlManager);
    view->rootContext()->setContextProperty(QStringLiteral("wp"), &wikipedia);
    view->rootContext()->setContextProperty(QStringLiteral("config"), config);
    view->rootContext()->setContextProperty(QStringLiteral("countriesModel"), countriesModel);
    view->rootContext()->setContextProperty(QStringLiteral("countriesFavourites"), countriesFavourites);
    view->rootContext()->setContextProperty(QStringLiteral("countriesSearch"), countriesSearch);
    view->rootContext()->setContextProperty(QStringLiteral("countryModel"), countryModel);
    view->rootContext()->setContextProperty(QStringLiteral("abcModel"), abcModel);
    view->rootContext()->setContextProperty(QStringLiteral("itemModel"), itemModel);
    view->rootContext()->setContextProperty(QStringLiteral("antecessorModel"), antecessorModel);
    view->rootContext()->setContextProperty(QStringLiteral("languageModel"), languageModel);
    view->rootContext()->setContextProperty(QStringLiteral("versionString"), VERSION_STRING);
    view->rootContext()->setContextProperty(QStringLiteral("versionInt"), VERSION);

#ifndef CLAZY
    view->setSource(SailfishApp::pathTo(QStringLiteral("qml/harbour-chennzeihhan.qml")));
#endif

//    view->setSource(QUrl::fromLocalFile(QStringLiteral("/usr/share/harbour-chennzeihhan/qml/harbour-chennzeihhan.qml")));
    view->show();

    return app->exec();
}

